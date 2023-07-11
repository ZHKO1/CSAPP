#include "../../lib/csapp.h"
#include "memlib.h"
#include "mm.h"

static void *extend_heap(size_t words);
static void *coalesce(void *bp);
static void *find_fit(size_t asize);
static void place(void *bp, size_t asize);

#define WSIZE 4
#define DSIZE 8
#define CHUNKSIZE (1 << 4)

#define MAX(x, y) ((x) > (y) ? (x) : (y))

#define PACK(size, alloc) ((size) | (alloc))

#define GET(p) (*(unsigned int *)(p))
#define PUT(p, val) (*(unsigned int *)(p) = (val))

#define GET_SIZE(p) ((GET(p)) & (~(0x7)))
#define GET_ALLOC(p) ((GET(p)) & 0x1)

#define HDRP(bp) ((char *)(bp)-WSIZE)
#define FTRP(bp) ((char *)(bp) + GET_SIZE(HDRP(bp)) - DSIZE)

#define NEXT_BLKP(bp) ((char *)(bp) + GET_SIZE((char *)(bp)-WSIZE))
#define PREV_BLKP(bp) ((char *)(bp)-GET_SIZE((char *)(bp)-DSIZE))

#define IS_END(p) ((GET_SIZE(p) == 0) && (GET_ALLOC(p) == 1))
#define IS_BP_END(bp) (IS_END(HDRP(bp)))

static char *heap_list = NULL;

int mm_int()
{
  if ((heap_list = mem_sbrk(4 * WSIZE)) == (void *)-1)
  {
    return -1;
  }

  PUT(heap_list, 0);
  PUT(heap_list + WSIZE, PACK(DSIZE, 1));
  PUT(heap_list + 2 * WSIZE, PACK(DSIZE, 1));
  PUT(heap_list + 3 * WSIZE, PACK(0, 1));

  heap_list += DSIZE;
  if (extend_heap(CHUNKSIZE / WSIZE) == NULL)
    return -1;
  return 0;
}

static void *extend_heap(size_t words)
{

  size_t size;
  char *bp;

  size = ((words % 2) ? (words + 1) : words) * WSIZE;
  if ((long)(bp = mem_sbrk(size)) == -1)
  {
    return NULL;
  }

  PUT(HDRP(bp), PACK(size, 0));
  PUT(FTRP(bp), PACK(size, 0));
  PUT(HDRP(NEXT_BLKP(bp)), PACK(0, 1));

  return coalesce(bp);
}

void mm_free(void *bp)
{
  size_t size = GET_SIZE(HDRP(bp));
  PUT(HDRP(bp), PACK(size, 0));
  PUT(FTRP(bp), PACK(size, 0));

  coalesce(bp);
}

static void *coalesce(void *bp)
{
  int pre_alloc = GET_ALLOC(HDRP(PREV_BLKP(bp)));
  int next_alloc = GET_ALLOC(HDRP(NEXT_BLKP(bp)));

  size_t size = GET_SIZE(HDRP(bp));

  if ((pre_alloc == 1) && (next_alloc == 1))
  {
    return bp;
  }
  if ((pre_alloc == 1) && (next_alloc == 0))
  {
    size = size + GET_SIZE(HDRP(NEXT_BLKP(bp)));
    PUT(HDRP(bp), PACK(size, 0));
    // 注意前一行已经修改了当前块的size，所以不能通过FTRP(NEXT_BLKP(bp))来拿到下一块的尾部;
    PUT(FTRP(bp), PACK(size, 0));
  }

  if ((pre_alloc == 0) && (next_alloc == 1))
  {
    size = size + GET_SIZE(HDRP(PREV_BLKP(bp)));
    PUT(HDRP(PREV_BLKP(bp)), PACK(size, 0));
    PUT(FTRP(bp), PACK(size, 0));
    bp = PREV_BLKP(bp);
  }

  if ((pre_alloc == 0) && (next_alloc == 0))
  {
    size = size + GET_SIZE(HDRP(PREV_BLKP(bp))) + GET_SIZE(HDRP(NEXT_BLKP(bp)));
    PUT(HDRP(PREV_BLKP(bp)), PACK(size, 0));
    PUT(FTRP(NEXT_BLKP(bp)), PACK(size, 0));
    bp = PREV_BLKP(bp);
  }

  return bp;
}

void *mm_malloc(size_t size)
{
  size_t asize;
  size_t extendsize;
  char *bp;

  if (size == 0)
  {
    return NULL;
  }

  if (size <= DSIZE)
  {
    asize = 2 * DSIZE;
  }
  else
  {
    asize = DSIZE * ((size + (DSIZE) + (DSIZE - 1)) / DSIZE);
  }

  if ((bp = find_fit(asize)) != NULL)
  {
    place(bp, asize);
    return bp;
  }

  extendsize = MAX(asize, CHUNKSIZE);
  if ((bp = extend_heap(extendsize / WSIZE)) == NULL)
  {
    return NULL;
  }
  place(bp, asize);
  return bp;
}

static void *find_fit(size_t asize)
{
  char *current_bp = heap_list + DSIZE;
  char *result_bp = NULL;
  while (!IS_BP_END(current_bp))
  {
    unsigned int current_size = GET_SIZE(HDRP(current_bp));
    unsigned int current_alloc = GET_ALLOC(HDRP(current_bp));
    if (!current_alloc)
    {
      if (current_size >= asize)
      {
        if (result_bp == NULL)
        {
          result_bp = current_bp;
        }
        else
        {
          if (current_size < GET_SIZE(HDRP(result_bp)))
          {
            result_bp = current_bp;
          }
        }
      }
    }
    current_bp = NEXT_BLKP(current_bp);
  }
  return result_bp;
}

static void place(void *bp, size_t asize)
{
  unsigned int space_size = GET_SIZE(HDRP(bp));
  unsigned int rest_size = space_size - asize;
  if (rest_size < 2 * DSIZE)
  {
    PUT(HDRP(bp), PACK(space_size, 1));
    PUT(FTRP(bp), PACK(space_size, 1));
  }
  else
  {
    PUT(HDRP(bp), PACK(asize, 1));
    PUT(FTRP(bp), PACK(asize, 1));
    PUT(FTRP(bp) + WSIZE, PACK(rest_size, 0));
    PUT(FTRP(NEXT_BLKP(bp)), PACK(rest_size, 0));
  }
}

void mm_log()
{
  char *word = heap_list - WSIZE;
  int i = 0;
  printf("[null]");
  while (!IS_END(word))
  {
    word = mm_block_log(word);
  }
  printf("[%2d/%d]\n", 0, 1);
}

char *mm_block_log(char *head)
{
  unsigned int size = GET_SIZE(head);
  unsigned int alloc = GET_ALLOC(head);
  unsigned int word_size = size / WSIZE;
  for (size_t i = 0; i < word_size; i++)
  {
    char *block = head + i * WSIZE;
    if ((i == 0) || (i == word_size - 1))
    {
      unsigned int size = GET_SIZE(block);
      unsigned int alloc = GET_ALLOC(block);
      printf("[%2d/%d]", size, alloc);
    }
    else
    {
      mm_block_log_word_by_char(block);
    }
  }
  return head + size;
}

void mm_block_log_word_by_char(char *ptr)
{
  printf("[");
  for (size_t i = 0; i < WSIZE; i++)
  {
    char *c = ptr + i;
    printf("%c", ((*c == 0) ? '_' : *c));
  }
  printf("]");
}