#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "cachelab.h"

#define MAX_LINE_LEN 100

int hit_count = 0;
int miss_count = 0;
int eviction_count = 0;
long time = 0;

typedef struct
{
  unsigned long flag;
  int valid;
  unsigned long time;
} cacheSetLine;

typedef struct
{
  int lineLength;
  cacheSetLine *lines;
} cacheSet;

typedef struct
{
  int s;
  int b;
  int setLength;
  cacheSet *sets;
} cache;

cache createCache(int s, int E, int b)
{
  cache c;
  size_t setCount = 1 << ((unsigned)s);
  c.s = s;
  c.b = b;
  c.setLength = setCount;

  cacheSet *p = (cacheSet *)malloc(sizeof(cacheSet) * setCount);
  c.sets = p;

  for (unsigned i = 0; i < setCount; i++)
  {
    cacheSet set;
    set.lineLength = E;
    cacheSetLine *p = (cacheSetLine *)malloc(sizeof(cacheSetLine) * E);
    set.lines = p;
    c.sets[i] = set;
    for (unsigned j = 0; j < E; j++)
    {
      cacheSetLine line;
      line.flag = 0;
      line.valid = 0;
      line.time = 0;
      set.lines[j] = line;
    }
  }
  return c;
}

void destoryCache(cache *c)
{
  int setLength = c->setLength;
  for (size_t i = 0; i < setLength; i++)
  {
    cacheSet *s = &c->sets[i];
    free(s->lines);
  }
  free(c->sets);
}

void printfCache(cache *c)
{
  int setLength = c->setLength;
  for (size_t i = 0; i < setLength; i++)
  {
    cacheSet *s = &c->sets[i];
    int lineLength = s->lineLength;
    printf("第%ld组\n", i);
    for (size_t j = 0; j < lineLength; j++)
    {
      cacheSetLine *l = &s->lines[j];
      printf("  第%ld行 flag=%ld valid=%d\n", j, l->flag, l->valid);
    }
  }
}

void getSetAndFlagFromAddress(cache *c, unsigned long address, unsigned long *setIndex, unsigned long *flag)
{
  int b = c->b;
  int s = c->s;
  int sMark = ~(-1 << s);
  *setIndex = (address >> b) & sMark;
  *flag = (address >> (b + s));
}

void readCache(cache *c, unsigned long address, int v)
{
  unsigned long setIndex = 0;
  unsigned long flag = 0;
  getSetAndFlagFromAddress(c, address, &setIndex, &flag);
  cacheSet set = c->sets[setIndex];
  for (int i = 0; i < set.lineLength; i++)
  {
    cacheSetLine *line = &set.lines[i];
    int lineValid = line->valid;
    unsigned long lineFlag = line->flag;
    if ((lineValid == 1) && (flag == lineFlag))
    {
      line->time = time++;
      hit_count++;
      if (v)
        printf("address=%lx set=%ld, flag=%lx hit\n", address, setIndex, flag);
      return;
    }
  }
  for (int i = 0; i < set.lineLength; i++)
  {
    cacheSetLine *line = &set.lines[i];
    int lineValid = line->valid;
    if (lineValid == 0)
    {
      line->valid = 1;
      line->flag = flag;
      line->time = time++;
      miss_count++;
      if (v)
        printf("address=%lx set=%ld, flag=%lx miss\n", address, setIndex, flag);
      return;
    }
  }
  int indexLRU = 0;
  for (int i = 0; i < set.lineLength; i++)
  {
    cacheSetLine *line = &set.lines[i];
    cacheSetLine *lineLRU = &set.lines[indexLRU];
    if (line->time < lineLRU->time)
    {
      indexLRU = i;
    }
  }
  cacheSetLine *lineLRU = &set.lines[indexLRU];
  lineLRU->valid = 1;
  lineLRU->flag = flag;
  lineLRU->time = time++;
  miss_count++;
  eviction_count++;
  if (v)
    printf("address=%lx set=%ld, flag=%lx miss eviction\n", address, setIndex, flag);
  return;
}

void stepCache(cache *c, char operation, unsigned long address, int size, int v)
{
  switch (operation)
  {
  case 'L':
    readCache(c, address, v);
    break;
  case 'S':
    readCache(c, address, v);
    break;
  case 'M':
    readCache(c, address, v);
    readCache(c, address, v);
    break;
  default:
    break;
  }
}

void getArg(int argc, char *argv[], int *v, int *s, int *E, int *b, char *t)
{
  int para;
  char template[20] = "vs:E:b:t:";
  *v = 0;
  while ((para = getopt(argc, argv, template)) != -1)
  {
    switch (para)
    {
    case 'v':
      *v = 1;
      break;
    case 's':
      *s = atoi(optarg);
      break;
    case 'E':
      *E = atoi(optarg);
      break;
    case 'b':
      *b = atoi(optarg);
      break;
    case 't':
      strcpy(t, optarg);
      break;
    default:
      printf("error opterr: %d\n", opterr);
      break;
    }
  }
}

void readTraceLine(char *line, cache *c, int v)
{
  char operation = 0;
  unsigned long address;
  int size;
  sscanf(line, " %c %lx,%d\n", &operation, &address, &size);

  // printf("%s", line);
  // printf("%c\n", operation);
  // printf("%lx\n", address);
  // printf("%d\n", size);

  stepCache(c, operation, address, size, v);
}

void readTrace(char *tracePath, cache *c, int v)
{
  char line[MAX_LINE_LEN];
  FILE *fp = fopen(tracePath, "r");

  if (fp == NULL)
  {
    printf("Failed to open the file.\n");
    return;
  }
  while (fgets(line, MAX_LINE_LEN, fp) != NULL)
  {
    if (v)
      printf("%s", line);
    readTraceLine(line, c, v);
  }
  fclose(fp);
}

int main(int argc, char *argv[])
{
  int verbose, s, E, b;
  char tracePath[100] = "";
  getArg(argc, argv, &verbose, &s, &E, &b, tracePath);
  printf("v=%d, s=%d, E=%d, b=%d, path=%s\n", verbose, s, E, b, tracePath);

  cache c = createCache(s, E, b);
  // printfCache(&c);

  readTrace(tracePath, &c, verbose);

  printSummary(hit_count, miss_count, eviction_count);
  destoryCache(&c);
  return 0;
}
