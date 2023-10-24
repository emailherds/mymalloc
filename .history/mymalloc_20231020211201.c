#include <stdio.h>
#include <stdlib.h>
#include "mymalloc.h"

#define MEMLENGTH 512

#define FREE 0
#define ALLOCATED 1

static double memory[MEMLENGTH];

#define heap ((char *) memory)
#define ROUNDUP8(x) (((x) + 7) & (-8))

typedef struct header{
    int hSize;
    int alloc; 
} header;

void *myMalloc(int size, char* file, int line){
    if(size == 0){
        printf("Can't allocate 0 bytes");
        return NULL;
    }
    
    size = ROUNDUP8(size);
    
    void *res = NULL;
    header *current = (header *) heap;

    // if (size > sizeof(memory) - (sizeof(header) + current -> hSize))
    // {
    //     printf("Error: Not enough space\n");
    //     return NULL;
    // }


    //printf("%d\n", current -> hSize);

    int count = 0;

    if (current -> hSize == 0 && current -> alloc == FREE)
    {
        current -> hSize = sizeof(memory) - sizeof(header);
    }

    while (count < sizeof(memory)-8)
    {
        if (current -> hSize >= size + sizeof(header) && current -> alloc == FREE)
        {
            current -> hSize = size;
            current -> alloc = ALLOCATED;

            res = (char*)current + sizeof(header);
            header* next = (header*)((char*)current + sizeof(header) + size);
            // may need to check if next chunk is uninitialized before we do anything
            if(next -> alloc == FREE){
                current = next;
                current -> hSize = sizeof(memory) - size - sizeof(header) - count; 
                current -> alloc = FREE;
            }

            //printf("%d next chunk size\n", *current);
            return res;
        }

        if (current -> alloc == ALLOCATED || current -> hSize < size + 8)
        {
            count += current -> hSize;
            current = (header*)((char*)current + current -> hSize + sizeof(header)); 
        }
    }

    printf("NOT ENOUGH SPACE");

    return NULL;
}

int memCleared()
{
    header *current = (header *) heap;

    // if ((current -> hSize == 0 && current -> alloc == FREE) || (current -> hSize == sizeof(memory) * 8 && current -> alloc == FREE))
    //     return 1;

    // return 0;


    int count = 0;

    while (count < sizeof(memory))
    {
        if (current -> alloc == ALLOCATED)
            return 0;
        current = (header*)((char*)current + current -> hSize + sizeof(header));
        count += current->hSize;
    }
    return 1;
}

// void test1() {
//     for(int i = 0; i < 3; i++) {
//         char *ptr = mymalloc(1);  // Allocate 1 byte of memory
//         myfree(ptr);  // Release the memory
//     }
//     printf("MemClear?: %d\n", memCleared());  // Check if memory is cleared
// }

// void test2() {
//     char *ptrArray[3];  // Array to store 120 pointers

//     for(int i = 0; i < 3; i++) {
//         ptrArray[i] = mymalloc(1);  // Allocate 1 byte of memory and store the address
//     }

//     for(int i = 0; i < 3; i++) {
//         myfree(ptrArray[i]);  // Release the memory
//     }

//     printf("MemClear?: %d\n", memCleared());  // Check if memory is cleared
// }

// void test3() {
//     char *ptrArray[120];  // Array to store 120 pointers
//     int allocated[120] = {0};  // Initialize the memory allocation status array
//     int loc = 0;  // Current location

//     for(int i = 0; i < 120; i++) {
//         if(loc == 0 || (rand() % 2 == 0 && loc < 120)) {
//             // Allocate 1 byte of memory and store the address
//             printf("alloc loc=%d\n", loc);
//             ptrArray[loc] = mymalloc(1);
//             allocated[loc] = 1;
//             loc++;
//         } else {
//             // Release the memory
//             loc--;
//             printf("free loc=%d\n", loc);
//             myfree(ptrArray[loc]);
//             allocated[loc] = 0;
//         }
//     }

//     printf("Process is done.\n");

//     // Clean up any unreleased memory
//     for(int i = 0; i < 120; i++) {
//         if(allocated[i] == 1) {
//             myfree(ptrArray[i]);
//         }
//     }

//     printf("MemClear?: %d\n", memCleared());  // Check if memory is cleared
// }



void myFree(void *ptr, char* file, int line)
{
    header *current = (header *) heap;
    header *ptrData = (header *) ((char*)ptr - sizeof(header));
    //printf("%d\n", ((header *)ptr) -> hSize);   

    int count = 0;

    // while loop to coalesce adjacent free chunks
    // ptr we are looking for will be allocated, so we don't need to worry about coalescing it
    while (count < sizeof(memory))
    {
        if ((current) == ptr && current -> alloc == FREE)
        {
            int oldSize = current -> hSize;
        
            // coalesce adjacent free chunks
            current -> hSize = current -> hSize + ((header*)((char*)current + sizeof(header) + current -> hSize)) -> hSize;

            if (((header*)((char*)ptrData + ptrData -> hSize + sizeof(header))) -> alloc == FREE)
            {
                int oldSize2 = current -> hSize;
                // coalesce adjacent free chunks
                current -> hSize = (int)(current -> hSize /*8*/ + (char*)(current /*0*/+ sizeof(header)/*8*/ + current -> hSize/*8*/) -> hSize);
                
                // clear next header
                ((header*)((char*)current + sizeof(header) + oldSize2)) -> alloc = FREE;
                ((header*)((char*)current + sizeof(header) + oldSize2)) -> hSize = 0;
            }
            
            // clear next header
            ((header*)(char*)current + sizeof(header) + oldSize) -> alloc = FREE;
            ((header*)(char*)current + sizeof(header) + oldSize) -> hSize = 0;
            ptr = NULL;

            return;
        }

        if ((char*)current+sizeof(header) == ptr) //if pointer on payload
        {
            if(current -> alloc == FREE){
                printf("Error: pointer already freed");
                return;
            }
            //printf("Next to Ptr: %d\n", (ptrData + ptrData -> hSize + sizeof(header)) -> alloc);
            if (((header*)((char*)ptrData + ptrData -> hSize + sizeof(header))) -> alloc == FREE)
            {
                int oldSize = current -> hSize;
                // coalesce adjacent free chunks
                current -> hSize = current -> hSize + ((header*) ((char*)current + sizeof(header) + current -> hSize)) -> hSize;
                //printf("SIZE: %d\n", current -> hSize);                
                // clear next header
                ((header*)((char*)current + sizeof(header) + oldSize)) -> alloc = FREE;
                ((header*)((char*)current + sizeof(header) + oldSize)) -> hSize = 0;
            }

            current -> alloc = FREE;
            ptr = NULL;

            return;
        }

        current = (header*) ((char*)current + current -> hSize + sizeof(header));
        count = count + current -> hSize + sizeof(header);
        //if ()
    }

    printf("Error: pointer not in heap\n");
    
    return;
}

int main()
{
    correct1();
    
    return 0;
}

// int main()
// {
//     //  printf("Clear: %d", memCleared());
//     // int x = 2;
//     // myfree(&x);


//     //  //
//     test1();
//     test2();
//     test3();
    

//     //  int* arr2 = mymalloc(sizeof(int)*10);
//     //  arr2[1] = 69;
//     //  printf("%d When", arr2[1]);
//     // test3();
//      //int x;
//      //myfree (&x);
//     // arr[31] = 1;

//     //printf("RES: %d\n", mymalloc(sizeof(int) * 32));

//     //printf("%d\n", arr[31]);
    
//     return 0;
// }

// Correctness Testing

/*
    Correctness Requirements:
        1. malloc() reserves unallocated memory
            a. We can check this by checking if malloc() returns an object to a header with metadata that does not overlap with other allocated objects
            b. We can test by writing a program that allocates several large objects. Once allocation is complete, it fills each
               object with a distinct byte pattern (e.g., the first object is filled with 1, the second with 2, etc.). 
               Finally, it checks whether each object still contains the written pattern. 
        2. 

*/

// Program to test if malloc reserves unallocated memory
void correct1()
{
    double* a = (double *) myMalloc(sizeof(double), 0, 0);
    double* b = (double *) myMalloc(sizeof(double), 0, 0);
    double* c = (double *) myMalloc(sizeof(double), 0, 0);

    *a = 1;
    *b = 2;
    *c = 3;

    printf("Value of a: %d\n", *a);
    printf("Value of b: %d\n", *b);
    printf("Value of c: %d\n", *c);
}

