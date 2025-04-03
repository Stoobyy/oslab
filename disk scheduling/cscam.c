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

// Function to implement C-SCAN disk scheduling
void cscan(int requests[], int n, int head, int max_cylinder) {
    int total_seek = 0;
    int current_pos = head;
    int i;
    
    // Sort the request array
    sort(requests, n);
    
    printf("\nSequence of disk movements: %d", head);
    
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
    
    // Go to the beginning of the disk
    total_seek += max_cylinder; // This is the seek from end to beginning
    current_pos = 0;
    printf(" -> %d", current_pos);
    
    // Now serve requests less than head
    for (i = 0; i < n; i++) {
        if (requests[i] < head) {
            total_seek += abs(requests[i] - current_pos);
            current_pos = requests[i];
            printf(" -> %d", current_pos);
        }
    }
    
    printf("\nTotal seek distance: %d\n", total_seek);
}

int main() {
    int n, head, max_cylinder;
    
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
    
    // Call the C-SCAN function
    cscan(requests, n, head, max_cylinder);
    
    return 0;
}