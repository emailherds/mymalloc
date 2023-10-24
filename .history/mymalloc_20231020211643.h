#ifndef MYMALLOC_H
#define MYMALLOC_H
#include <stdio.h>
#include <stdlib.h>

#define ROUNDUP8(x) (((x) + 7) & (-8))

typedef struct header{
    int hSize;
    int alloc; 
} header;

int memCleared();
void *myMalloc(int size, char* file, int line);
void myFree(void *ptr, char* file, int line);

#define free(x) myFree(x, __FILE__, __LINE__)
#define malloc(x) myMalloc(x, __FILE__, __LINE__)

int main();

#endif