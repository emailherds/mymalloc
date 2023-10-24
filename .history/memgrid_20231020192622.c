#include <mymalloc.h>

int memCleared()
{
    header *current = (header *) heap;

    // if ((current -> hSize == 0 && current -> alloc == FREE) || (current -> hSize == MEMLENGTH * 8 && current -> alloc == FREE))
    //     return 1;

    // return 0;


    int count = 0;

    while (count < MEMLENGTH)
    {
        if (current -> alloc == ALLOCATED)
            return 0;
        current = (header*)((char*)current + current -> hSize + sizeof(header));
        count += current->hSize;
    }
    return 1;
}

void test1() {
    for(int i = 0; i < 120; i++) {
        char *ptr = mymalloc(1);  // Allocate 1 byte of memory
        myfree(ptr);  // Release the memory
    }
    printf("MemClear?: %d\n", memCleared());  // Check if memory is cleared
}

void test2() {
    char *ptrArray[120];  // Array to store 120 pointers

    for(int i = 0; i < 120; i++) {
        ptrArray[i] = mymalloc(1);  // Allocate 1 byte of memory and store the address
    }

    for(int i = 0; i < 120; i++) {
        myfree(ptrArray[i]);  // Release the memory
    }

    printf("MemClear?: %d\n", memCleared());  // Check if memory is cleared
}

void test3() {
    char *ptrArray[120];  // Array to store 120 pointers
    int allocated[120] = {0};  // Initialize the memory allocation status array
    int loc = 0;  // Current location

    for(int i = 0; i < 120; i++) {
        if(loc == 0 || (rand() % 2 == 0 && loc < 120)) {
            // Allocate 1 byte of memory and store the address
            printf("alloc loc=%d\n", loc);
            ptrArray[loc] = mymalloc(1);
            allocated[loc] = 1;
            loc++;
        } else {
            // Release the memory
            loc--;
            printf("free loc=%d\n", loc);
            myfree(ptrArray[loc]);
            allocated[loc] = 0;
        }
    }

    printf("Process is done.\n");

    // Clean up any unreleased memory
    for(int i = 0; i < 120; i++) {
        if(allocated[i] == 1) {
            myfree(ptrArray[i]);
        }
    }

    printf("MemClear?: %d\n", memCleared());  // Check if memory is cleared
}
