#include <stdlib.h>
#include <stdio.h>

#define MEMLENGTH 512

#define FREE 0
#define ALLOCATED 1

static char memory[MEMLENGTH];

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
    header* current = (header*)heap;

    while((char*)current < memory + MEMLENGTH)
    {
        if(current -> size == 0 && current -> alloc == FREE){ // case: if memory hasn't been initialized
            current -> size = size;  
            current -> alloc = ALLOCATED;
            res = current+sizeof(header);
            current += size+8;

            current = current + sizeof(header) + size;
            current -> size = MEMLENGTH - (size+sizeof(header));
            current -> alloc = FREE;

            printf("size %d BLAH \n", current->size);
            return res;
        }

        if(current -> alloc == FREE && current -> size >= size+8){ // case: if chunk is free but memory has been initalized
            int lastChunkSize = current->size;
            current -> size = size;
            current -> alloc = ALLOCATED;
            res = (char*)(current + sizeof(header));

            current = current + sizeof(header) + size;
            current -> size = 0;
            current -> alloc = FREE;

            return res;
        }

        if(current -> alloc == ALLOCATED){ // case: if current chunk is not free, then iterate to next
            current = current + sizeof(header) + current->size;            
        }
    }

    printf("NOT ENOUGH MEMORY");

    return NULL;
}

int main()
{
    printf("working\n");
    int* arr = (int *) mymalloc(sizeof(int) * 24);
    int* arr2 = (int *) mymalloc(sizeof(int) * 24);

    
    arr[1] = 1;
    arr[2] = 2;

    printf("%d BROOOO IT WORKDS \n", arr[1]);
    printf("%d BROOOO IT work kinda", arr2[2]);


    // printf("\nthis is malloc %d", mymalloc(24));

    //printf("%d BRUHHHH", *heap);

    return 0;
}
