#include <stdlib.h>
#include <stdio.h>

#define MEMLENGTH 512

#define FREE 0
#define ALLOCATED 1

static double memory[MEMLENGTH];

#define heap ((char *)memory)
#define ROUNDUP8(x) (((x) + 7) & (-8))

int heapsize = 0;

typedef struct header {
    int size;
    int alloc;
    struct header *next;
} header;

void *mymalloc(int size) {
    if (size == 0) {
        printf("Error: cannot allocate 0 bytes\n");
        return NULL;
    }

    size = ROUNDUP8(size);

    void *res = NULL;
    char *start = heap;

    while (start < heap + MEMLENGTH) {
        int chunkSize = *((int *)start);
        int isFree = *((int *)(start + 4));

        if (chunkSize == 0 && isFree == 0) {
            *((int *)start) = size + 8;
            *((int *)(start + 4)) = ALLOCATED;
            res = start + 8;
            *((int *)(start + size + 8)) = MEMLENGTH - (size + 8 - chunkSize);
            return res;
        }

        if (isFree == 0 && chunkSize >= size + 8) {
            *((int *)start) = size + 8;
            *((int *)(start + 4)) = ALLOCATED;
            res = start + 8;
            if (*((int *)(start + size + 8)) == 0) {
                *((int *)(start + size + 8)) = chunkSize - (size + 8);
            }
            return res;
        }

        start = start + chunkSize + 8;
    }

    printf("Error: not enough memory\n");
    return NULL;
}

int main() {
    printf("working\n");
    int *arr = (int *)mymalloc(sizeof(int) * 24);
    int *arr2 = (int *)mymalloc(sizeof(int) * 24);
    int *arr3 = (int *)mymalloc(sizeof(int) * 512);

    if (arr) {
        arr[0] = 1;
        printf("\nthis is malloc: %d", arr[0]);
    }

    
    if (arr2) {
        arr2[0] = 2;
        printf("\nthis is malloc: %d", arr2[0]);
    }

arr3[1] = 5;
        printf("\nthis is malloc: %d", arr3[1]);

    

    return 0;
}