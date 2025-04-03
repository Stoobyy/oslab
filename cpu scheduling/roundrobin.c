#include <stdio.h>

struct Process {
    int id;
    int arrival;
    int burst;
    int rem;       // Remaining burst time
    int wait;
    int tat;
    int complete;
} process[10];

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

// Function to calculate waiting time, turnaround time, and completion time using Round Robin scheduling
void calculateTimesRR(struct Process proc[], int n, int quantum) {
    int time = 0;      // Current time
    int done = 0;      // Number of processes completed

    // Initialize remaining time for each process
    for (int i = 0; i < n; i++) {
        proc[i].rem = proc[i].burst;
    }

    // Continue until all processes are completed
    while (done < n) {
        int executed = 0;  // Flag to check if any process was executed in this cycle

        for (int i = 0; i < n; i++) {
            // Only process if it has arrived and is not yet completed
            if (proc[i].arrival <= time && proc[i].rem > 0) {
                executed = 1;
                if (proc[i].rem > quantum) {
                    time += quantum;
                    proc[i].rem -= quantum;
                } else {
                    time += proc[i].rem;
                    proc[i].rem = 0;
                    proc[i].complete = time;
                    proc[i].tat = proc[i].complete - proc[i].arrival;
                    proc[i].wait = proc[i].tat - proc[i].burst;
                    done++;
                }
            }
        }
        // If no process was executed (i.e., no process has arrived), increment time
        if (!executed) {
            time++;
        }
    }
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
}

void main() {
    int n, quantum;
    printf("Enter no. of processes: ");
    scanf("%d", &n);
    
    for (int i = 0; i < n; i++) {
        printf("Enter process id: ", i + 1);
        scanf("%d", &process[i].id);
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &process[i].burst);
        process[i].arrival = 0;
    }
    
    printf("Enter time quantum: ");
    scanf("%d", &quantum);
    
    sortByArrival(process, n);
    calculateTimesRR(process, n, quantum);
    display(process, n);
}
