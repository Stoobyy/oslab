#include <stdio.h>

struct Process {
    int id;
    int arrival;
    int burst;
    int priority;
    int wait;
    int tat;
    int complete;
    int remaining;
    int processed;
} process[10];

struct GanttEntry {
    int pid;
    int start;
    int end;
} gantt[100];

int ganttCount = 0;

// Function to find the highest priority job that has arrived but not processed yet
int findHighestPriorityJob(struct Process proc[], int n, int currentTime) {
    int highest = -1;
    int highestPriority = 10000;

    for (int i = 0; i < n; i++) {
        if (proc[i].arrival <= currentTime && proc[i].processed == 0) {
            if (proc[i].priority < highestPriority) {
                highestPriority = proc[i].priority;
                highest = i;
            }
        }
    }

    return highest;
}

void calculatePriorityScheduling(struct Process proc[], int n) {
    int currentTime = 0;
    int completed = 0;
    int prev = -1; // To track context switch

    for (int i = 0; i < n; i++) {
        proc[i].processed = 0;
        proc[i].remaining = proc[i].burst;
    }

    while (completed < n) {
        int highest = findHighestPriorityJob(proc, n, currentTime);

        if (highest == -1) {
            currentTime++;
        } else {
            if (prev != highest) {
                // Context switch: start a new Gantt entry
                gantt[ganttCount].pid = proc[highest].id;
                gantt[ganttCount].start = currentTime;
                gantt[ganttCount].end = currentTime + 1;
                ganttCount++;
            } else {
                // Continue running same process: extend current Gantt entry
                gantt[ganttCount - 1].end++;
            }

            proc[highest].remaining--;
            currentTime++;

            if (proc[highest].remaining == 0) {
                proc[highest].complete = currentTime;
                proc[highest].tat = proc[highest].complete - proc[highest].arrival;
                proc[highest].wait = proc[highest].tat - proc[highest].burst;
                proc[highest].processed = 1;
                completed++;
            }

            prev = highest;
        }
    }
}

void sortByArrival(struct Process proc[], int n) {
    struct Process temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (proc[j].arrival > proc[j + 1].arrival ||
                (proc[j].arrival == proc[j + 1].arrival && proc[j].priority > proc[j + 1].priority)) {
                temp = proc[j];
                proc[j] = proc[j + 1];
                proc[j + 1] = temp;
            }
        }
    }
}

void display(struct Process proc[], int n) {
    printf("\nProcess\tArrival\tBurst\tPriority\tWait\tTAT\tComplete\n");
    int totalwait = 0, totaltat = 0;
    for (int i = 0; i < n; i++) {
        totalwait += proc[i].wait;
        totaltat += proc[i].tat;
        printf("%d\t%d\t%d\t%d\t\t%d\t%d\t%d\n", proc[i].id, proc[i].arrival, proc[i].burst, proc[i].priority, proc[i].wait, proc[i].tat, proc[i].complete);
    }

    printf("\nAverage Waiting Time: %.2f", (float)totalwait / n);
    printf("\nAverage Turnaround Time: %.2f\n", (float)totaltat / n);

    // Gantt Chart Output
    printf("\nGantt Chart:\n|");
    for (int i = 0; i < ganttCount; i++) {
        printf(" P%d |", gantt[i].pid);
    }

    printf("\n%d", gantt[0].start);
    for (int i = 0; i < ganttCount; i++) {
        printf("    %d", gantt[i].end);
    }
    printf("\n");
}

void main() {
    int n;
    printf("Enter no. of processes: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        process[i].id = i + 1;
        printf("Enter arrival time for process %d: ", i + 1);
        scanf("%d", &process[i].arrival);
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &process[i].burst);
        printf("Enter priority for process %d: ", i + 1);
        scanf("%d", &process[i].priority);
    }

    sortByArrival(process, n);
    calculatePriorityScheduling(process, n);
    display(process, n);
}
