#include <stdio.h>
#include <stdlib.h>

// Function to calculate total head movement for FCFS
int fcfs(int requests[], int n, int head) {
    int total_movement = 0;
    int current_position = head;
    
    printf("\nFCFS Disk Scheduling Algorithm\n");
    printf("Sequence of head movement: %d", head);
    
    for (int i = 0; i < n; i++) {
        printf(" -> %d", requests[i]);
        total_movement += abs(requests[i] - current_position);
        current_position = requests[i];
    }
    
    printf("\nTotal head movement: %d\n", total_movement);
    return total_movement;
}

// Function to sort array
void sort(int arr[], int n) {
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (arr[j] > arr[j+1]) {
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

// Function to calculate total head movement for SCAN
int scan(int requests[], int n, int head, int max_cylinder) {
    int sorted_requests[n + 1];
    int total_movement = 0;
    int current_position = head;
    int head_index;
    
    // Copy requests and add head position
    for (int i = 0; i < n; i++) {
        sorted_requests[i] = requests[i];
    }
    sorted_requests[n] = head;
    
    // Sort all positions
    sort(sorted_requests, n + 1);
    
    // Find the index of head
    for (int i = 0; i < n + 1; i++) {
        if (sorted_requests[i] == head) {
            head_index = i;
            break;
        }
    }
    
    printf("\nSCAN Disk Scheduling Algorithm\n");
    printf("Sequence of head movement: %d", head);
    
    // Head moves towards higher cylinders first (right)
    for (int i = head_index + 1; i < n + 1; i++) {
        printf(" -> %d", sorted_requests[i]);
        total_movement += abs(sorted_requests[i] - current_position);
        current_position = sorted_requests[i];
    }
    
    // Then go to the maximum cylinder
    if (current_position < max_cylinder) {
        printf(" -> %d", max_cylinder);
        total_movement += abs(max_cylinder - current_position);
        current_position = max_cylinder;
    }
    
    // Then head changes direction and moves towards lower cylinders (left)
    for (int i = head_index - 1; i >= 0; i--) {
        printf(" -> %d", sorted_requests[i]);
        total_movement += abs(sorted_requests[i] - current_position);
        current_position = sorted_requests[i];
    }
    
    printf("\nTotal head movement: %d\n", total_movement);
    return total_movement;
}

// Function to calculate total head movement for C-SCAN
int cscan(int requests[], int n, int head, int max_cylinder) {
    int sorted_requests[n + 1];
    int total_movement = 0;
    int current_position = head;
    int head_index;
    
    // Copy requests and add head position
    for (int i = 0; i < n; i++) {
        sorted_requests[i] = requests[i];
    }
    sorted_requests[n] = head;
    
    // Sort all positions
    sort(sorted_requests, n + 1);
    
    // Find the index of head
    for (int i = 0; i < n + 1; i++) {
        if (sorted_requests[i] == head) {
            head_index = i;
            break;
        }
    }
    
    printf("\nC-SCAN Disk Scheduling Algorithm\n");
    printf("Sequence of head movement: %d", head);
    
    // Head moves towards higher cylinders first (right)
    for (int i = head_index + 1; i < n + 1; i++) {
        printf(" -> %d", sorted_requests[i]);
        total_movement += abs(sorted_requests[i] - current_position);
        current_position = sorted_requests[i];
    }
    
    // Go to the maximum cylinder
    if (current_position < max_cylinder) {
        printf(" -> %d", max_cylinder);
        total_movement += abs(max_cylinder - current_position);
        current_position = max_cylinder;
    }
    
    // Jump to the start (cylinder 0) with no movement cost in C-SCAN
    printf(" -> %d", 0);
    current_position = 0;
    
    // Continue servicing requests from the beginning to the head position
    for (int i = 0; i < head_index; i++) {
        printf(" -> %d", sorted_requests[i]);
        total_movement += abs(sorted_requests[i] - current_position);
        current_position = sorted_requests[i];
    }
    
    printf("\nTotal head movement: %d\n", total_movement);
    return total_movement;
}

int main() {
    int requests[] = {170, 60, 55, 182, 22, 58, 108};
    int n = sizeof(requests) / sizeof(requests[0]);
    int head = 101;
    int max_cylinder = 199;
    
    printf("Disk Parameters:\n");
    printf("Number of cylinders: 200 (0-199)\n");
    printf("Initial head position: %d\n", head);
    printf("Request queue: ");
    for (int i = 0; i < n; i++) {
        printf("%d", requests[i]);
        if (i < n - 1) {
            printf(", ");
        }
    }
    printf("\n");
    
    // Run the three algorithms
    fcfs(requests, n, head);
    scan(requests, n, head, max_cylinder);
    cscan(requests, n, head, max_cylinder);
    
    return 0;
}