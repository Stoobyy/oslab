#include <stdio.h>
#define SIZE 10
int disk[SIZE] = {0};
void sequentialAllocation(int start, int length) {
    if (start + length > SIZE) {
        printf("Not enough space for allocation!\n");
        return;
    }
    for (int i = start; i < start + length; i++) {
        if (disk[i] == 1) {
            printf("Block %d already allocated. Allocation failed!\n", i);
            return;
        }
    }
    for (int i = start; i < start + length; i++) {
        disk[i] = 1;
    }
    printf("File allocated from block %d to %d\n", start, start + length - 1);
}
void main() {
    sequentialAllocation(2, 4);
    sequentialAllocation(6, 3);
    sequentialAllocation(3,7);
}

