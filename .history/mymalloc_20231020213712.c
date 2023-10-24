#include "mymalloc.h"

#define MEMLENGTH 512

#define FREE 0
#define ALLOCATED 1

static double memory[MEMLENGTH];

#define heap ((char *) memory)


void *myMalloc(int size, char* file, int line){
    if(size == 0){
        printf("Can't allocate 0 bytes");
        return NULL;
    }
    
    size = ROUNDUP8(size);
    
    void *res = NULL;
    header *current = (header *) heap;

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
//         char *ptr = myMalloc(1, 0, 0);  // Allocate 1 byte of memory
//         myFree(ptr, 0, 0);  // Release the memory
//     }
//     printf("MemClear?: %d\n", memCleared());  // Check if memory is cleared
// }

// void test2() {
//     char *ptrArray[3];  // Array to store 120 pointers

//     for(int i = 0; i < 3; i++) {
//         ptrArray[i] = myMalloc(1, 0 ,0 );  // Allocate 1 byte of memory and store the address
//     }

//     for(int i = 0; i < 3; i++) {
//         myFree(ptrArray[i],0 ,0);  // Release the memory
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
//             ptrArray[loc] = myMalloc(1, 0 ,0 );
//             allocated[loc] = 1;
//             loc++;
//         } else {
//             // Release the memory
//             loc--;
//             printf("free loc=%d\n", loc);
//             myFree(ptrArray[loc], 0, 0);
//             allocated[loc] = 0;
//         }
//     }

//     printf("Process is done.\n");

//     // Clean up any unreleased memory
//     for(int i = 0; i < 120; i++) {
//         if(allocated[i] == 1) {
//             myFree(ptrArray[i], 0 , 0);
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
    test1();
    test2();
    test3();
    //correct1();

    return 0;
}
// Correctness Testing

/*
    Correctness Requirements:
        1. malloc() reserves unallocated memory
            a. We can check this by checking if malloc() returns an object to a header with metadata that does not overlap with other allocated objects
            b. We can test this by writing a program that allocates several large objects. Once allocation is complete, it fills each
               object with a distinct byte pattern (e.g., the first object is filled with 1, the second with 2, etc.). 
               Finally, it checks whether each object still contains the written pattern. 
        2. free() deallocates memory
            a. We can check this by using malloc() to allocate memory, and then freeing that memory
            b. We can test this by using malloc() to allocate memory and then checking the allocation status of the header of the memory that was just allocated
               After calling malloc(), the header's allocation status will be set to 1 to show that the chunk is allocated
               We can then call free() on this chunk of memory that was allocated and then check the allocation status of the same header
               If free() works properly, the header's allocation status will now be set to 0 to show that the chunk is free

*/

// Program to test if malloc reserves unallocated memory
void correct1()
{
    double *a = (double *) myMalloc(sizeof(double), 0, 0);
    double *b = (double *) myMalloc(sizeof(double), 0, 0);
    double *c = (double *) myMalloc(sizeof(double), 0, 0);

    *a = 1;
    *b = 2;
    *c = 3;

    printf("Value of a: %d\n", *a);
    printf("Value of b: %d\n", *b);
    printf("Value of c: %d\n", *c);
}

// Program to check if free() deallocates memory
void correct2()
{
    int *arr = (int *) myMalloc(sizeof(int) * 5, 0, 0);
    printf("ALLOCATION VALE")
       
}

