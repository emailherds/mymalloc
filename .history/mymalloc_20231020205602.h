#include <stdio.h>
#include <stdlib.h>
#ifndef mymalloc.h
#define mymalloc.h


#define MEMLENGTH 512

#define FREE 0
#define ALLOCATED 1

static double memory[MEMLENGTH];

#define heap ((char *) memory)
#define ROUNDUP8(x) (((x) + 7) & (-8))

int heapsize = 0;

typedef struct header{
    int hSize;
    int alloc; 
} header;

int memCleared();
void *mymalloc(int size, char* file, int line);
void myfree(void *ptr, char* file, int line);

#define free(x) myfree(x, __FILE__, __LINE__)
#define malloc(x) mymalloc(x, __FILE__, __LINE__)

#endif