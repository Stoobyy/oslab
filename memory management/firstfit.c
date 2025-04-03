#include <stdio.h>

void fcfs(int blocks[], int m, int processes[], int n) {
    // Array to keep track of allocated blocks
    int allocation[n];
    
    // Initialize allocation array with -1 to indicate no allocation
    for(int i = 0; i < n; i++) {
        allocation[i] = -1;
    }
    
    // For each process
    for(int i = 0; i < n; i++) {
        printf("\nIteration %d:\n", i+1);
        printf("Trying to allocate %d KB for process %d\n", processes[i], i+1);
        
        // For each block
        for(int j = 0; j < m; j++) {
            // If block size is sufficient
            if(blocks[j] >= processes[i]) {
                // Allocate the block j to process i
                allocation[i] = j;
                
                // Reduce available memory in the block
                blocks[j] -= processes[i];
                
                printf("Success! Process %d allocated to Block %d\n", i+1, j+1);
                printf("Remaining space in Block %d: %d KB\n", j+1, blocks[j]);
                
                // Display current state of all blocks
                printf("Current state of all blocks: ");
                for(int k = 0; k < m; k++) {
                    printf("Block %d: %d KB | ", k+1, blocks[k]);
                }
                printf("\n");
                
                break; // Move to the next process
            }
        }
        
        // If no block could accommodate the process
        if(allocation[i] == -1) {
            printf("Failed! No block could accommodate Process %d\n", i+1);
        }
    }
    
    // Display final allocation results
    printf("\nFinal Allocation Result:\n");
    printf("Process No.\tProcess Size\tBlock No.\n");
    for(int i = 0; i < n; i++) {
        printf("%d\t\t%d KB\t\t", i+1, processes[i]);
        if(allocation[i] != -1) {
            printf("%d\n", allocation[i] + 1);
        } else {
            printf("Not Allocated\n");
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
    
    // Call FCFS algorithm
    fcfs(blocks, m, processes, n);
    
    return 0;
}