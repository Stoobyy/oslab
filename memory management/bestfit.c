#include <stdio.h>
#include <limits.h>

void bestFit(int blocks[], int m, int processes[], int n) {
    // Array to keep track of allocated blocks
    int allocation[n];
    
    // Copy of original blocks to keep track of remaining space
    int remainingBlocks[m];
    for(int i = 0; i < m; i++) {
        remainingBlocks[i] = blocks[i];
    }
    
    // Initialize allocation array with -1 to indicate no allocation
    for(int i = 0; i < n; i++) {
        allocation[i] = -1;
    }
    
    // For each process
    for(int i = 0; i < n; i++) {
        printf("\nIteration %d:\n", i+1);
        printf("Trying to allocate %d KB for process %d\n", processes[i], i+1);
        
        // Find the best fit block for current process
        int bestIdx = -1;
        int bestSize = INT_MAX;
        
        for(int j = 0; j < m; j++) {
            // If block size is sufficient
            if(remainingBlocks[j] >= processes[i]) {
                // Find the best fit (smallest sufficient block)
                if(remainingBlocks[j] < bestSize) {
                    bestIdx = j;
                    bestSize = remainingBlocks[j];
                }
            }
        }
        
        // If we found a block for the process
        if(bestIdx != -1) {
            // Allocate the best fit block to process
            allocation[i] = bestIdx;
            
            // Reduce available memory in the block
            remainingBlocks[bestIdx] -= processes[i];
            
            printf("Success! Process %d allocated to Block %d\n", i+1, bestIdx+1);
            printf("Remaining space in Block %d: %d KB\n", bestIdx+1, remainingBlocks[bestIdx]);
            
            // Display current state of all blocks
            printf("Current state of all blocks: ");
            for(int k = 0; k < m; k++) {
                printf("Block %d: %d KB | ", k+1, remainingBlocks[k]);
            }
            printf("\n");
        }
        else {
            // If no block could accommodate the process
            printf("Failed! No block could accommodate Process %d\n", i+1);
        }
    }
    
    // Display final allocation results
    printf("\nFinal Allocation Result:\n");
    printf("Process No.\tProcess Size\tBlock No.\tFragment\n");
    for(int i = 0; i < n; i++) {
        printf("%d\t\t%d KB\t\t", i+1, processes[i]);
        if(allocation[i] != -1) {
            printf("%d\t\t%d KB\n", allocation[i] + 1, remainingBlocks[allocation[i]]);
        } else {
            printf("Not Allocated\tN/A\n");
        }
    }
}

int main() {
    int m, n; // m: number of blocks, n: number of processes
    
    // Get number of memory blocks
    printf("Enter the number of memory blocks: ");
    scanf("%d", &m);
    
    int blocks[m]; // Array to store memory block sizes
    
    // Get sizes of memory blocks
    printf("Enter the sizes of memory blocks (in KB):\n");
    for(int i = 0; i < m; i++) {
        printf("Block %d: ", i+1);
        scanf("%d", &blocks[i]);
    }
    
    // Get number of processes
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    
    int processes[n]; // Array to store process sizes
    
    // Get sizes of processes
    printf("Enter the sizes of processes (in KB):\n");
    for(int i = 0; i < n; i++) {
        printf("Process %d: ", i+1);
        scanf("%d", &processes[i]);
    }
    
    // Call Best Fit algorithm
    bestFit(blocks, m, processes, n);
    
    return 0;
}