//bankers algorithm
#include <stdio.h>
#include <stdbool.h>

#define P 5  // Number of processes
#define R 3  // Number of resource types

// Function to check if the system is in a safe state
bool isSafe(int available[], int max[][R], int allocation[][R], int need[][R]) {
    int work[R];
    bool finish[P] = {false};
    int safeSequence[P];
    int count = 0;
    
    // Copy available resources into work array
    for (int i = 0; i < R; i++)
        work[i] = available[i];
    
    while (count < P) {
        bool found = false;
        for (int i = 0; i < P; i++) {
            if (!finish[i]) {
                bool canProceed = true;
                for (int j = 0; j < R; j++) {
                    if (need[i][j] > work[j]) {
                        canProceed = false;
                        break;
                    }
                }
                if (canProceed) {
                    for (int j = 0; j < R; j++)
                        work[j] += allocation[i][j];
                    safeSequence[count++] = i;
                    finish[i] = true;
                    found = true;
                }
            }
        }
        if (!found) {
            printf("The system is in an unsafe state!\n");
            return false;
        }
    }
    printf("System is in a safe state. Safe sequence: ");
    for (int i = 0; i < P; i++)
        printf("P%d ", safeSequence[i]);
    printf("\n");
    return true;
}

int main() {
    int available[R] = {3, 3, 2};  // Available resources
    int max[P][R] = {
        {7, 5, 3},
        {3, 2, 2},
        {9, 0, 2},
        {2, 2, 2},
        {4, 3, 3}
    };
    int allocation[P][R] = {
        {0, 1, 0},
        {2, 0, 0},
        {3, 0, 2},
        {2, 1, 1},
        {0, 0, 2}
    };
    int need[P][R];
    
    // Calculate Need matrix
    for (int i = 0; i < P; i++)
        for (int j = 0; j < R; j++)
            need[i][j] = max[i][j] - allocation[i][j];
    
    // Check if the system is in a safe state
    isSafe(available, max, allocation, need);
    return 0;
}

