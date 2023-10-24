#include <stdlib.h>
#include <stdio.h>

#define MEMLENGTH 512

#define FREE 0
#define ALLOCATED 1

static double memory[MEMLENGTH];

#define heap ((char *) memory)
int heapsize = 0;

typedef struct {
    int size;
    int alloc;
} header;

//#include "mymalloc.h"

void *mymalloc(int size){
    if(size > 0 && size+heapsize <= MEMLENGTH){
        void *result = heap+heapsize;
        heapsize += size;
    }
}

int main()
{
    printf("Hello world");

    return 0;
}