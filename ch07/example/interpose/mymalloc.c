#ifdef COMPILETIME
#include <stdio.h>
#include <malloc.h>

void *mymalloc(size_t size)
{
  void *ptr = malloc(size);
  printf("malloc(%d)=%p\n", (int)size, ptr);
  return ptr;
}

void myfree(void *ptr)
{
  free(ptr);
  printf("free(%p)\n", ptr);
}

#endif

#ifdef LINKTIME
#include <stdio.h>
void *__real_malloc(size_t size);
void *__real_free(void *ptr);

void *__wrap_malloc(size_t size)
{
  void *ptr = __real_malloc(size);
  printf("malloc(%d)=%p\n", (int)size, ptr);
  return ptr;
}

void __wrap_free(void *ptr)
{
  __real_free(ptr);
  printf("free(%p)\n", ptr);
}

#endif

#ifdef RUNTIME
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
// 这里经测试，执行后会报错，网上查了下原因是因为print自带malloc，导致栈报错
// 但是我实际去掉了printf函数，还是会报错，因此不太明白真正的原因到底是什么
// 可能需要花时间排查
void *malloc(size_t size)
{
  void *(*mallocp)(size_t size);
  char *error;

  mallocp = dlsym(RTLD_NEXT, "malloc");
  if ((error = dlerror()) != NULL)
  {
    fputs(error, stderr);
    exit(1);
  }

  char *ptr = mallocp(size);
  printf("malloc(%d)=%p\n", (int)size, ptr);
  return ptr;
}

void free(void *ptr)
{
  void (*freep)(void *) = NULL;
  char *error;

  if (!ptr)
    return;

  freep = dlsym(RTLD_NEXT, "free");
  if ((error = dlerror()) != NULL)
  {
    fputs(error, stderr);
    exit(1);
  }

  free(ptr);
  printf("free(%p)\n", ptr);
}

#endif