#include <stdlib.h>
#include <stdio.h>

#define MEMLENGTH 512
static double memory[MEMLENGTH];

#define heap ((char *) memory)
int heapsize = 0;

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