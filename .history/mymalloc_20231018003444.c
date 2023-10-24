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

    struct header *next;
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
    char *current = heap;

    header head;
    head.size = 0;
    head.alloc = FREE;

    while(*heap < MEMLENGTH)
    {
        if(head.size == 0 && head.alloc == FREE){
            head.size = size;  
            head.alloc = ALLOCATED;
            res = *start+8;
            start += size+8;

            header *next;
            next->size = MEMLENGTH-size-8;
            next->alloc = FREE;
            head.next = &next; //next;

            head = *head.next;
        }

        if(head.alloc == FREE && head.size >= size+8){
            head.size = size;
            head.alloc = ALLOCATED;
            res = *start+8;
            start += size+8;          
        }
    }
    
    // if(size > 0 && size+heapsize <= MEMLENGTH){
    //     void *result = heap+heapsize;
    //     heapsize += size;
    // }
}

int main()
{
    printf("%d", *heap);
    printf("working");

    return 0;
}