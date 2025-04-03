#include <stdio.h>
#include <stdlib.h>

void fcfs_disk_scheduling(int requests[], int n, int initial_head) {
    int total_seek_time = 0;
    int current_head = initial_head;
    
    printf("\nSequence of head movements:\n");
    printf("%d", current_head);
    
    // Process all requests in the order they arrive
    for (int i = 0; i < n; i++) {
        // Calculate seek time for current request
        int seek = abs(requests[i] - current_head);
        total_seek_time += seek;
        
        // Move head to the current request
        current_head = requests[i];
        printf(" -> %d", current_head);
    }
    
    printf("\n\nTotal seek time: %d", total_seek_time);
    printf("\nAverage seek time: %.2f\n", (float)total_seek_time / n);
}

int main() {
    int n, initial_head, max_cylinder;
    
    // Accept read head position
    printf("Enter the initial position of read head: ");
    scanf("%d", &initial_head);
    
    // Accept number of cylinders
    printf("Enter the maximum cylinder number: ");
    scanf("%d", &max_cylinder);
    
    // Accept number of requests
    printf("Enter the number of requests: ");
    scanf("%d", &n);
    
    int requests[n];
    
    // Accept order of arrival of requests
    printf("Enter the cylinder requests in order of arrival:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &requests[i]);
        
        // Validate that the request is within cylinder range
        if (requests[i] < 0 || requests[i] >= max_cylinder) {
            printf("Error: Request %d is outside the valid cylinder range (0-%d)\n", requests[i], max_cylinder-1);
            return 1;
        }
    }
    
    // Call FCFS function
    fcfs_disk_scheduling(requests, n, initial_head);
    
    return 0;
}