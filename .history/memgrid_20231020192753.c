#include <mymalloc.h>

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

int main()
{
    //  int* arr = mymalloc(sizeof(int) * 100);
    //  int* arr3 = mymalloc(sizeof(int)*24);
     //myfree(arr3);
    //  printf("Clear: %d", memCleared());
    // int x = 2;
    // myfree(&x);

    //  //
    test1();
    test2();
    //  myfree(arr);
    //  int* arr2 = mymalloc(sizeof(int)*10);
    //  arr2[1] = 69;
    //  printf("%d When", arr2[1]);

     //int x;
     //myfree (&x);
    // arr[31] = 1;

    //printf("RES: %d\n", mymalloc(sizeof(int) * 32));

    //printf("%d\n", arr[31]);
    
    return 0;
}
