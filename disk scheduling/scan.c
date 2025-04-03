#include <stdio.h>
#include <stdlib.h>

// Function to sort an array
void sort(int arr[], int n) {
    int i, j, temp;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// Function to implement SCAN disk scheduling
void scan(int requests[], int n, int head, int max_cylinder, int direction) {
    int total_seek = 0;
    int current_pos = head;
    int i;
    
    // Sort the request array
    sort(requests, n);
    
    printf("\nSequence of disk movements: %d", head);
    
    // If direction is 1, move toward higher cylinder numbers first
    if (direction == 1) {
        // Serve requests greater than head
        for (i = 0; i < n; i++) {
            if (requests[i] >= head) {
                total_seek += abs(requests[i] - current_pos);
                current_pos = requests[i];
                printf(" -> %d", current_pos);
            }
        }
        
        // Go to the end of the disk
        if (current_pos != max_cylinder) {
            total_seek += abs(max_cylinder - current_pos);
            current_pos = max_cylinder;
            printf(" -> %d", current_pos);
        }
        
        // Now serve requests less than head
        for (i = n - 1; i >= 0; i--) {
            if (requests[i] < head) {
                total_seek += abs(requests[i] - current_pos);
                current_pos = requests[i];
                printf(" -> %d", current_pos);
            }
        }
    }
    // If direction is 0, move toward lower cylinder numbers first
    else {
        // Serve requests less than head
        for (i = n - 1; i >= 0; i--) {
            if (requests[i] < head) {
                total_seek += abs(requests[i] - current_pos);
                current_pos = requests[i];
                printf(" -> %d", current_pos);
            }
        }
        
        // Go to the beginning of the disk
        if (current_pos != 0) {
            total_seek += abs(current_pos - 0);
            current_pos = 0;
            printf(" -> %d", current_pos);
        }
        
        // Now serve requests greater than head
        for (i = 0; i < n; i++) {
            if (requests[i] >= head) {
                total_seek += abs(requests[i] - current_pos);
                current_pos = requests[i];
                printf(" -> %d", current_pos);
            }
        }
    }
    
    printf("\nTotal seek distance: %d\n", total_seek);
}

int main() {
    int n, head, max_cylinder, direction;
    
    // Get input values
    printf("Enter the number of requests: ");
    scanf("%d", &n);
    
    int requests[n];
    printf("Enter the request sequence: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &requests[i]);
    }
    
    printf("Enter the initial position of read/write head: ");
    scanf("%d", &head);
    
    printf("Enter the maximum cylinder number: ");
    scanf("%d", &max_cylinder);
    
    printf("Enter the direction (1 for moving toward higher cylinder, 0 for lower): ");
    scanf("%d", &direction);
    
    // Call the SCAN function
    scan(requests, n, head, max_cylinder, direction);
    
    return 0;
}