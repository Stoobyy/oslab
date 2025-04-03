#include <stdio.h>

struct Process {
    int id;
    int arrival;
    int burst;
    int wait;
    int tat;
    int complete;
    int remaining;  // Renamed from 'rem' to match attached code
    int processed;  // Added to match attached code (used as a flag for completion)
} process[10];

// Structure to track execution sequence for Gantt chart
struct GanttEntry {
    int processId;
    int startTime;
    int endTime;
} gantt[100]; // Assuming maximum 100 context switches

int ganttSize = 0; // Number of entries in the Gantt chart

// Function to sort processes by arrival time (bubble sort)
void sortByArrival(struct Process proc[], int n) {
    struct Process temp;
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

// Function to sort Gantt entries by start time
void sortByCompletion(struct GanttEntry gantt[], int n) {
    struct GanttEntry temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (gantt[j].startTime > gantt[j + 1].startTime) {
                temp = gantt[j];
                gantt[j] = gantt[j + 1];
                gantt[j + 1] = temp;
            }
        }
    }
}

// Function to calculate waiting time, turnaround time, and completion time using Round Robin scheduling
void calculateTimesRR(struct Process proc[], int n, int quantum) {
    int currentTime = 0;  // Renamed from 'time' to match attached code
    int completed = 0;    // Renamed from 'done' to match attached code
    ganttSize = 0;        // Reset Gantt chart entries

    // Initialize remaining time for each process
    for (int i = 0; i < n; i++) {
        proc[i].remaining = proc[i].burst;
        proc[i].processed = 0;  // Initialize processed flag
    }

    // Continue until all processes are completed
    while (completed < n) {
        int executed = 0;  // Flag to check if any process was executed in this cycle

        for (int i = 0; i < n; i++) {
            // Only process if it has arrived and is not yet completed
            if (proc[i].arrival <= currentTime && proc[i].remaining > 0) {
                executed = 1;
                int startTime = currentTime;
                
                if (proc[i].remaining > quantum) {
                    currentTime += quantum;
                    proc[i].remaining -= quantum;
                } else {
                    currentTime += proc[i].remaining;
                    proc[i].remaining = 0;
                    proc[i].complete = currentTime;
                    proc[i].tat = proc[i].complete - proc[i].arrival;
                    proc[i].wait = proc[i].tat - proc[i].burst;
                    proc[i].processed = 1;  // Mark as processed
                    completed++;
                }
                
                // Add entry to Gantt chart
                gantt[ganttSize].processId = proc[i].id;
                gantt[ganttSize].startTime = startTime;
                gantt[ganttSize].endTime = currentTime;
                ganttSize++;
            }
        }
        // If no process was executed (i.e., no process has arrived), increment time
        if (!executed) {
            currentTime++;
        }
    }
    
    // Merge consecutive entries of the same process
    for (int i = 0; i < ganttSize - 1; i++) {
        if (gantt[i].processId == gantt[i + 1].processId) {
            gantt[i + 1].startTime = gantt[i].startTime;
            gantt[i].processId = -1; // Mark for removal
        }
    }
    
    // Compact the array by removing marked entries
    int newSize = 0;
    for (int i = 0; i < ganttSize; i++) {
        if (gantt[i].processId != -1) {
            gantt[newSize] = gantt[i];
            newSize++;
        }
    }
    ganttSize = newSize;
    
    // Sort the Gantt chart by start time
    sortByCompletion(gantt, ganttSize);
}

// Function to display process details and average times
void display(struct Process proc[], int n) {
    int totalwait = 0;
    int totaltat = 0;
    
    printf("\nProcess\tArrival\tBurst\tWait\tTAT\tComplete\n");
    for (int i = 0; i < n; i++) {
        totalwait += proc[i].wait;
        totaltat += proc[i].tat;
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", 
               proc[i].id, proc[i].arrival, proc[i].burst, 
               proc[i].wait, proc[i].tat, proc[i].complete);
    }
    
    printf("\nAverage Waiting Time: %.2f", (float)totalwait / n);
    printf("\nAverage Turnaround Time: %.2f\n", (float)totaltat / n);
    
    // Display Gantt chart
    printf("\nGantt Chart:\n");
        
    // Print process boxes
    printf("|");
    for (int i = 0; i < ganttSize; i++) {
        printf(" P%d |", gantt[i].processId);
    }

    // Print time markers
    printf("\n");
    printf("%d", gantt[0].startTime);  // First process start time

    for (int i = 0; i < ganttSize; i++) {
        
        printf("     %d", gantt[i].endTime);
    }
    printf("\n");
}

void main() {
    int n, quantum;
    printf("Enter no. of processes: ");
    scanf("%d", &n);
    
    for (int i = 0; i < n; i++) {
        process[i].id = i + 1;
        printf("Enter arrival time for process %d: ", i + 1);
        scanf("%d", &process[i].arrival);
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &process[i].burst);
    }
    
    printf("Enter time quantum: ");
    scanf("%d", &quantum);
    
    sortByArrival(process, n);
    calculateTimesRR(process, n, quantum);
    display(process, n);
}