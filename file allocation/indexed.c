#include <stdio.h>
#define SIZE 10

// 0 means free, any other value means allocated
int disk[SIZE] = {0};
// To store block pointers for indexed allocation
int blockPointers[SIZE][SIZE] = {0};
int blockCount[SIZE] = {0}; // Number of blocks in each index

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
    
    // Mark index block as allocated
    disk[indexBlock] = 1;
    
    // Store references to data blocks in the index block
    blockCount[indexBlock] = length;
    for (int i = 0; i < length; i++) {
        blockPointers[indexBlock][i] = blocks[i];
        disk[blocks[i]] = 1; // Mark data blocks as allocated
    }
    
    printf("File allocated with index block %d\n", indexBlock);
    printf("Index block %d points to: ", indexBlock);
    for (int i = 0; i < length; i++) {
        printf("%d ", blockPointers[indexBlock][i]);
    }
    printf("\n");
}

// Function to read a file using indexed allocation
void readFile(int indexBlock) {
    if (indexBlock < 0 || indexBlock >= SIZE || disk[indexBlock] == 0) {
        printf("Invalid index block or not allocated!\n");
        return;
    }
    
    printf("Reading file with index block %d\n", indexBlock);
    printf("Accessing blocks: ");
    for (int i = 0; i < blockCount[indexBlock]; i++) {
        printf("%d ", blockPointers[indexBlock][i]);
    }
    printf("\n");
}

int main() {
    int file1Blocks[] = {2, 3, 4};
    indexedAllocation(1, file1Blocks, 3);
    readFile(1);

    int file2Blocks[] = {5, 6, 7};
    indexedAllocation(0, file2Blocks, 3);
    readFile(0);

    int file3Blocks[] = {3, 8, 9};
    indexedAllocation(2, file3Blocks, 3);  // This should fail because block 3 is already allocated
    
    return 0;
}