#include "../../lib/csapp.h"
#include "memlib.h"

int mm_int();
void mm_free(void *bp);
void *mm_malloc(size_t size);
void mm_log();
char *mm_block_log(char *head);
void mm_block_log_word_by_char(char *ptr);