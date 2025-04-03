#include <stdio.h>
#define SIZE 10

int disk[SIZE] = {0};

void indexedAllocation(int indexBlock, int blocks[], int length) {
    if (indexBlock < 0 || indexBlock >= SIZE) {
        printf("Invalid index block!\n");
        return;
    }
    
    if (disk[indexBlock] == 1) {
        printf("Index block %d already allocated. Allocation failed!\n", indexBlock);
        return;
    }
    
    for (int i = 0; i < length; i++) {
        if (blocks[i] < 0 || blocks[i] >= SIZE || disk[blocks[i]] == 1) {
            printf("Block %d already allocated or out of bounds. Allocation failed!\n", blocks[i]);
            return;
        }
    }
    
    disk[indexBlock] = 1;
    for (int i = 0; i < length; i++) {
        disk[blocks[i]] = 1;
    }
    
    printf("File allocated with index block %d\n", indexBlock);
    printf("Allocated blocks: ");
    for (int i = 0; i < length; i++) {
        printf("%d ", blocks[i]);
    }
    printf("\n");
}

void main() {
    int file1Blocks[] = {2, 3, 4};
    indexedAllocation(1, file1Blocks, 3);

    int file2Blocks[] = {5, 6, 7};
    indexedAllocation(0, file2Blocks, 3);

    int file3Blocks[] = {3, 8, 9};
    indexedAllocation(2, file3Blocks, 3);
}


