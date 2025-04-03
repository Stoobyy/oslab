#include <stdio.h>
#define SIZE 10

int disk[SIZE] = {0};
int pointers[SIZE];
void linkedAllocation(int blocks[], int length) {
    for (int i = 0; i < length; i++) {
        if (disk[blocks[i]] == 1) {
            printf("Block %d is already allocated. Allocation failed!\n", blocks[i]);
            return;
        }
    }
    for (int i = 0; i < length - 1; i++) {
        disk[blocks[i]] = 1;
        pointers[blocks[i]] = blocks[i + 1];
    }
    disk[blocks[length - 1]] = 1;
    pointers[blocks[length - 1]] = -1;
    printf("File allocated at blocks: ");
    for (int i = 0; i < length; i++) printf("%d -> ", blocks[i]);
    printf("END\n");
}
void main() {
    int file1[] = {1, 3, 5, 7};
    linkedAllocation(file1, 4);
}

