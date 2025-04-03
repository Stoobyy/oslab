#include <stdio.h>

struct Process{
    int id;
    int arrival;
    int burst;
    int wait;
    int tat;
    int complete;
    int remaining;  // Remaining burst time
    int processed;  // Flag to mark if process has been completed
}process[10];

// Function to find the shortest job that has arrived but not processed yet
int findShortestJob(struct Process proc[], int n, int currentTime) {
    int shortest = -1;
    int minRemaining = 9999;
    
    for(int i = 0; i < n; i++) {
        if(proc[i].arrival <= currentTime && proc[i].processed == 0) {
            if(proc[i].remaining < minRemaining) {
                minRemaining = proc[i].remaining;
                shortest = i;
            }
        }
    }
    
    return shortest;
}

void calculatePreemptiveSJF(struct Process proc[], int n) {
    int currentTime = 0;
    int completed = 0;
    
    // Initialize remaining time and processed flag for all processes
    for(int i = 0; i < n; i++) {
        proc[i].remaining = proc[i].burst;
        proc[i].processed = 0;
    }
    
    // Continue until all processes are completed
    while(completed < n) {
        // Find the shortest job available at current time
        int shortest = findShortestJob(proc, n, currentTime);
        
        if(shortest == -1) {
            // No process available, increment time
            currentTime++;
        } else {
            // Decrement remaining time of the process
            proc[shortest].remaining--;
            currentTime++;
            
            // Check if process has completed
            if(proc[shortest].remaining == 0) {
                // Process completed
                proc[shortest].complete = currentTime;
                proc[shortest].tat = proc[shortest].complete - proc[shortest].arrival;
                proc[shortest].wait = proc[shortest].tat - proc[shortest].burst;
                
                // Mark process as processed
                proc[shortest].processed = 1;
                completed++;
            }
        }
    }
}

void sortByArrival(struct Process proc[], int n){
    struct Process temp;
    for(int i = 0; i < n-1; i++){
        for(int j = 0; j < n-i-1; j++)
        {
            if(proc[j].arrival > proc[j+1].arrival)
            {
                temp = proc[j];
                proc[j] = proc[j+1];
                proc[j+1] = temp;
            }
        }
    }
}

void sortByCompletion(struct Process proc[], int n) {
    struct Process temp;
    for(int i = 0; i < n-1; i++){
        for(int j = 0; j < n-i-1; j++)
        {
            if(proc[j].complete > proc[j+1].complete)
            {
                temp = proc[j];
                proc[j] = proc[j+1];
                proc[j+1] = temp;
            }
        }
    }
}

void display(struct Process proc[], int n){
    printf("\nProcess\tArrival\tBurst\tWait\tTAT\tComplete\n");
    int totalwait = 0;
    int totaltat = 0;
    for(int i = 0; i < n; i++)
    {
        totalwait += proc[i].wait;
        totaltat += proc[i].tat;
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", proc[i].id, proc[i].arrival, proc[i].burst, proc[i].wait, proc[i].tat, proc[i].complete);
    }
    printf("\nAverage Waiting Time: %.2f", (float)totalwait/n);
    printf("\nAverage Turnaround Time: %.2f\n", (float)totaltat/n);
    
    // Sort by completion time for Gantt chart
    struct Process sortedProc[10];
    for(int i = 0; i < n; i++) {
        sortedProc[i] = proc[i];
    }
    sortByCompletion(sortedProc, n);
    
    printf("\nGantt Chart:\n");
        
    // Print process boxes
    printf("|");
    for (int i = 0; i < n; i++) {
        printf(" P%d |\t", sortedProc[i].id);
    }

    // Print time markers
    printf("\n");
    printf("%d", sortedProc[0].arrival);  // First process arrival time

    for (int i = 0; i < n; i++) {
        printf("     %d", sortedProc[i].complete);
    }
    printf("\n");
}

void main()
{
    int n;
    printf("Enter no. of processes: ");
    scanf("%d", &n);
    for(int i = 0; i < n; i++)
    {
        process[i].id = i+1;
        printf("Enter arrival time for process %d: ", i+1);
        scanf("%d", &process[i].arrival);
        printf("Enter burst time for process %d: ", i+1);
        scanf("%d", &process[i].burst);
    }
    sortByArrival(process, n);
    calculatePreemptiveSJF(process, n);
    display(process, n);
}