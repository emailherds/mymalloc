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
    char *current = heap;

    header head;
    head.size = 0;
    head.alloc = FREE;

    header firstHead;

    while(*heap < MEMLENGTH)
    {

        if(head.size == 0 && head.alloc == FREE){
            head.size = size;  
            head.alloc = ALLOCATED;

            //*((header*)start) = head;

            res = (*start+8);
            start += size+sizeof(header);

            header *next;
            next -> size = MEMLENGTH - size - sizeof(header);
            next -> alloc = FREE;
            //head = next;

            // header *next;
            // next->size = MEMLENGTH-size-8;
            // next->alloc = FREE;
            // head.next = next; //next;
            
            // firstHead = head;

            // head = *head.next;

            printf("%d", res);

            return res;
        }

        if(head.alloc == FREE && head.size >= size+8){
            head.size = size;
            head.alloc = ALLOCATED;
            res = (char*)(*start+8);
            start += size+8;

            header next;
            next.size = MEMLENGTH - size - 8;
            next.alloc = FREE;
            head = next;
            

            if (start)
            {
                    
            }

            
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

    
    arr[1] = 1;

    printf("%d", arr[1]);

    // printf("\nthis is malloc %d", mymalloc(24));

    //printf("%d BRUHHHH", *heap);

    return 0;
}
