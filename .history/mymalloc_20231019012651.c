#include <stdlib.h>
#include <stdio.h>

#define MEMLENGTH 512

#define FREE 0
#define ALLOCATED 1

static double memory[MEMLENGTH];

#define heap ((char *) memory)
#define ROUNDUP8(x) (((x) + 7) & (-8))

int heapsize = 0;

typedef struct header{
    int size;
    int alloc; 

    //struct header *next;
} header;

// typedef struct
// {
//     header *curr;
//     node *prev;
//     node *next;
// } node;
//#include "mymalloc.h"

void *mymalloc(int size){
    if(size == 0){
        printf("Can't allocate 0 bytes");
        return NULL;
    }
    
    size = ROUNDUP8(size);
    
    void *res = NULL;
    char *start = heap;
    header* current = (header*)heap;

    current -> size = 0;
    current -> alloc = FREE;
    
            printf("%d current 1\n", *current);
    header firstHead;

    while(current < MEMLENGTH)
    {

        if(current -> size == 0 && current -> alloc == FREE){ // if memory hasn't been initialized
            current -> size = size;  
            current -> alloc = ALLOCATED;
            res = (char*)(*start+8);
            start += size+8;

            current = current + sizeof(header) + size;
            current -> size = MEMLENGTH - (size+sizeof(header));
            current -> alloc = FREE;

            printf("size %d", current->size)
            return res;
        }

        if(current -> alloc == FREE && current -> size >= size+8){ // if chunk is free
            int lastChunkSize = current->size;
            current -> size = size;
            current -> alloc = ALLOCATED;
            res = (char*)(current + sizeof(header));

            current = current + sizeof(header) + size;
            current -> size = 0;
            current -> alloc = FREE;

            return res;
        }

        if(current -> alloc == ALLOCATED){
            current = current + sizeof(header) + current->size;            
        }
        return res;
    }

    printf("NOT ENOUGH MEMORY");

    return NULL;
}

int main()
{
    printf("working\n");
    int* arr = (int *) mymalloc(sizeof(int) * 24);
    
    //arr[1] = 1;

    //printf("%d", arr[1]);

    // printf("\nthis is malloc %d", mymalloc(24));

    //printf("%d BRUHHHH", *heap);

    return 0;
}
