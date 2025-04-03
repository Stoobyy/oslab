#include <stdio.h>

// Structure to represent a process
struct Process {
    int pid;      // Process ID
    int arrival;  // Arrival Time
    int burst;    // Burst Time
    int wait;     // Waiting Time
    int turn;     // Turnaround Time
    int complete; // Completion Time
};

// Function to calculate waiting time and turnaround time for each process
void calculateTimes(struct Process proc[], int n) {
    // First process has 0 waiting time
    proc[0].wait = 0;
    
    // Calculate completion time of first process
    proc[0].complete = proc[0].arrival + proc[0].burst;
    
    // Calculate turnaround time for first process
    proc[0].turn = proc[0].complete - proc[0].arrival;
    
    // Calculate for rest of the processes
    for (int i = 1; i < n; i++) {
        // Check if previous process completes before current process arrives
        if (proc[i-1].complete < proc[i].arrival) {
            proc[i].complete = proc[i].arrival + proc[i].burst;
        } else {
            // Calculate completion time
            proc[i].complete = proc[i-1].complete + proc[i].burst;
        }
        
        // Calculate turnaround time
        proc[i].turn = proc[i].complete - proc[i].arrival;
        
        // Calculate waiting time
        proc[i].wait = proc[i].turn - proc[i].burst;
    }
}

// Function to sort processes by arrival time
void sortByArrival(struct Process proc[], int n) {
    struct Process temp;
    
    // Using bubble sort for simplicity
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (proc[j].arrival > proc[j + 1].arrival) {
                temp = proc[j];
                proc[j] = proc[j + 1];
                proc[j + 1] = temp;
            }
        }
    }
}

// Function to display process details and average times
void display(struct Process proc[], int n) {
    int total_wait = 0, total_turn = 0;
    
    printf("\nProcess\tArrival\tBurst\tWaiting\tTurnaround\tCompletion\n");
    
    for (int i = 0; i < n; i++) {
        total_wait += proc[i].wait;
        total_turn += proc[i].turn;
        
        printf("%d\t%d\t%d\t%d\t%d\t\t%d\n", 
               proc[i].pid, proc[i].arrival, proc[i].burst, 
               proc[i].wait, proc[i].turn, proc[i].complete);
    }
    
    printf("\nAverage Waiting Time: %.2f", (float)total_wait / n);
    printf("\nAverage Turnaround Time: %.2f\n", (float)total_turn / n);
//     printf("Gantt Chart:\n|");
//     for(int i = 0; i<n; i++){
//         printf("\t P%d |", proc[i].pid);
//     }
//     printf("\n0\t");
//     for(int i = 0; i<n; i++){
//         printf("%d\t\t", proc[i].complete);
//     }
//     printf("\n");
// Simple Gantt Chart
    printf("\nGantt Chart:\n");
        
    // Print process boxes
    printf("|");
    for (int i = 0; i < n; i++) {
        printf(" P%d |\t", proc[i].pid);
    }

    // Print time markers
    printf("\n");
    printf("%d", proc[0].arrival);  // First process arrival time

    for (int i = 0; i < n; i++) {
        printf("     %d", proc[i].complete);
    }
    printf("\n");

}

int main() {
    int n;  // Number of processes
    
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    
    struct Process proc[n];
    
    // Input process details
    for (int i = 0; i < n; i++) {
        proc[i].pid = i + 1;
        
        printf("Enter arrival time for Process %d: ", i + 1);
        scanf("%d", &proc[i].arrival);
        
        printf("Enter burst time for Process %d: ", i + 1);
        scanf("%d", &proc[i].burst);
    }
    
    // Sort processes by arrival time
    sortByArrival(proc, n);
    
    // Calculate waiting and turnaround times
    calculateTimes(proc, n);
    
    // Display results
    display(proc, n);
    
    return 0;
}