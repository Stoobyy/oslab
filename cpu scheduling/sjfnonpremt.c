#include <stdio.h>

struct Process{
    int id;
    int arrival;
    int burst;
    int wait;
    int tat;
    int complete;
    int processed;  // Flag to mark if process has been executed
}process[10];

// Function to find the shortest job that has arrived but not processed yet
int findShortestJob(struct Process proc[], int n, int currentTime) {
    int shortest = -1;
    int minBurst = 9999;
    
    for(int i = 0; i < n; i++) {
        if(proc[i].arrival <= currentTime && proc[i].processed == 0) {
            if(proc[i].burst < minBurst) {
                minBurst = proc[i].burst;
                shortest = i;
            }
        }
    }
    
    return shortest;
}

void calculateTimesSJF(struct Process proc[], int n) {
    int currentTime = 0;
    int completed = 0;
    
    // Initialize processed flag for all processes
    for(int i = 0; i < n; i++) {
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
            // Execute the process
            proc[shortest].wait = currentTime - proc[shortest].arrival;
            if(proc[shortest].wait < 0) proc[shortest].wait = 0;
            
            proc[shortest].complete = currentTime + proc[shortest].burst;
            proc[shortest].tat = proc[shortest].complete - proc[shortest].arrival;
            
            // Update current time
            currentTime = proc[shortest].complete;
            
            // Mark process as processed
            proc[shortest].processed = 1;
            completed++;
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

void display(struct Process proc[], int n){
    printf("\nProcess\tArrival\tBurst\tWait\tTAT\tComplete\n");
    int totalwait = 0;
    int totaltat = 0;
    for(int i = 0; i<n; i++)
    {
        totalwait += proc[i].wait;
        totaltat += proc[i].tat;
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", proc[i].id, proc[i].arrival, proc[i].burst, proc[i].wait, proc[i].tat, proc[i].complete);
    }
    printf("\nAverage Waiting Time: %.2f", (float)totalwait/n);
    printf("\nAverage Turnaround Time: %.2f\n", (float)totaltat/n);
    printf("\nGantt Chart:\n");
        
    // Print process boxes
    printf("|");
    for (int i = 0; i < n; i++) {
        printf(" P%d |\t", proc[i].id);
    }

    // Print time markers
    printf("\n");
    printf("%d", proc[0].arrival);  // First process arrival time

    for (int i = 0; i < n; i++) {
        printf("     %d", proc[i].complete);
    }
    printf("\n");

}

void main()
{
    int n;
    printf("Enter no. of processes: ");
    scanf("%d", &n);
    for(int i = 0; i<n; i++)
    {
        process[i].id = i+1;
        printf("Enter arrival time for process %d: ", i+1);
        scanf("%d", &process[i].arrival);
        printf("Enter burst time for process %d: ", i+1);
        scanf("%d", &process[i].burst);
    }
    sortByArrival(process, n);
    calculateTimesSJF(process, n);
    display(process, n);
}