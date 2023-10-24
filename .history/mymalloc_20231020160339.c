#include <stdio.h>
#include <stdlib.h>

#define MEMLENGTH 512

#define FREE 0
#define ALLOCATED 1

static char memory[MEMLENGTH];

#define heap ((char *) memory)
#define ROUNDUP8(x) (((x) + 7) & (-8))

int heapsize = 0;

typedef struct header{
    int hSize;
    int alloc; 

    //struct header *next;
} header;

void *mymalloc(int size){
    if(size == 0){
        printf("Can't allocate 0 bytes");
        return NULL;
    }
    
    size = ROUNDUP8(size);

    void *res = NULL;
    header *current = (header *) heap;

    //printf("%d\n", current -> hSize);

    int count = 0;

    while (count < MEMLENGTH)
    {
        if (current -> hSize == 0 && current -> alloc == FREE)
        {
            current -> hSize = size;
            current -> alloc = ALLOCATED;

            res = (char*)current + sizeof(header);

            // Shifts current over to the next free chunk of memory
            current = current + sizeof(header) + size;
            current -> hSize = MEMLENGTH - size - sizeof(header);
            current -> alloc = FREE;

            return res;
        }

        if (current -> hSize >= size + 8 && current -> alloc == FREE)
        {
            int prevChunkSize = current -> hSize;

            current -> hSize = size;
            current -> alloc = ALLOCATED;

            res = current + sizeof(header);

            // may need to check if next chunk is uninitialized before we do anything
            current = current + sizeof(header) + size;
            current -> hSize = MEMLENGTH - current -> hSize - sizeof(header) - count;
            current -> alloc = FREE;

            return res;
        }

        if (current -> alloc == ALLOCATED || current -> hSize < size + 8)
        {
            count = count + current -> hSize;
            current = current + current -> hSize + sizeof(header); 
        }
    }
}

int memCleared()
{
    header *current = (header *) heap;

    if ((current -> hSize == 0 && current -> alloc ==    FREE) || (current -> hSize == 8 && current -> alloc == FREE))
        return 1;

    return 0;
}

void test1() {
    for(int i = 0; i < 120; i++) {
        char *ptr = mymalloc(1);  // Allocate 1 byte of memory
        myfree(ptr);  // Release the memory
    }
    printf("MemClear?: %d\n", memCleared());  // Check if memory is cleared
}

void myfree(void *ptr)
{
    header *current = (header *) heap;
    header *ptrData = (header *) ((char*)ptr - sizeof(header));
    //printf("%d\n", ((header *)ptr) -> hSize);   

    int count = 0;

    // while loop to coalesce adjacent free chunks
    // ptr we are looking for will be allocated, so we don't need to worry about coalescing it
    while (count < MEMLENGTH)
    {
        //printf("%d\n", current -> alloc);
        // if (current -> alloc == FREE && (current + sizeof(header) + current -> hSize) -> alloc == FREE)
        // {
        //     int oldSize = current -> hSize;
        //     // coalesce adjacent free chunks
        //     current -> hSize = current -> hSize + (current + sizeof(header) + current -> hSize) -> hSize;
            
        //     // clear next header
        //     (current + sizeof(header) + oldSize) -> alloc = FREE;
        //     (current + sizeof(header) + oldSize) -> hSize = 0;

        //     // if ((current + sizeof(header) + current -> hSize) -> alloc == FREE)
        //     // {

        //     // }
        // }

        if (((char*)current + current -> hSize + sizeof(header) + 8) == ptr && current -> alloc == FREE)
        {
            int oldSize = current -> hSize;
        
            // coalesce adjacent free chunks
            current -> hSize = current -> hSize + (current + sizeof(header) + current -> hSize) -> hSize;

            if ((ptrData + ptrData -> hSize + sizeof(header)) -> alloc == FREE)
            {
                int oldSize2 = current -> hSize;
                // coalesce adjacent free chunks
                current -> hSize = current -> hSize + (current + sizeof(header) + current -> hSize) -> hSize;
                
                // clear next header
                (current + sizeof(header) + oldSize2) -> alloc = FREE;
                (current + sizeof(header) + oldSize2) -> hSize = 0;
            }
            
            // clear next header
            (current + sizeof(header) + oldSize) -> alloc = FREE;
            (current + sizeof(header) + oldSize) -> hSize = 0;
            ptr = NULL;

            return;
        }

        if ((char*)current + sizeof(header) == ptr)    
        {
            printf("FOUND THE PTR");

            if ((ptrData + ptrData -> hSize + sizeof(header)) -> alloc == FREE)
            {
                int oldSize = current -> hSize;
                // coalesce adjacent free chunks
                current -> hSize = current -> hSize + (current + sizeof(header) + current -> hSize) -> hSize;
                
                // clear next header
                (current + sizeof(header) + oldSize) -> alloc = FREE;
                (current + sizeof(header) + oldSize) -> hSize = 0;
            }

            current -> alloc = FREE;
            ptr = NULL;

            return;
        }

        current = (header*) (char*)current + current -> hSize + sizeof(header);
        count = count + current -> hSize + sizeof(header);
        //if ()
    }

    printf("Error: Pointer not in heap");
    
    return;
}

int main()
{
     int* arr = mymalloc(sizeof(int) * 64);
     //
     //test1();
     myfree(arr);

     //int x;
     //myfree (&x);
    // arr[31] = 1;

    //printf("RES: %d\n", mymalloc(sizeof(int) * 32));

    //printf("%d\n", arr[31]);
    
    return 0;
}