#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Process {
    int burstTime;
    int arrivalTime;
    int waitingTime;
    int turnaroundTime;
};

void fcfs(struct Process *processes, int n) {
    int i;
    processes[0].waitingTime = 0;

    for (i = 1; i < n; i++) {
        processes[i].waitingTime = processes[i - 1].waitingTime + processes[i - 1].burstTime;
    }

    for (i = 0; i < n; i++) {
        processes[i].turnaroundTime = processes[i].waitingTime + processes[i].burstTime;
    }
}

void sjf(struct Process *processes, int n) {
    int i, j;
    struct Process temp;

    for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j < n; j++) {
            if (processes[i].burstTime > processes[j].burstTime) {
                temp = processes[i];
                processes[i] = processes[j];
                processes[j] = temp;
            }
        }
    }

    fcfs(processes, n);
}

void printExecutionOrder(struct Process *processes, int n) {
    int i;
    printf("Order of execution: ");
    for (i = 0; i < n; i++) {
        printf("P%d", i + 1);
        if (i != n - 1) {
            printf(" -> ");
        }
    }
    printf("\n");
}

float calculateAverageWaitingTime(struct Process *processes, int n) {
    int i;
    float totalWaitingTime = 0;

    for (i = 0; i < n; i++) {
        totalWaitingTime += processes[i].waitingTime;
    }

    return (float)totalWaitingTime / n;
}

float calculateAverageTurnaroundTime(struct Process *processes, int n) {
    int i;
    float totalTurnaroundTime = 0;

    for (i = 0; i < n; i++) {
        totalTurnaroundTime += processes[i].turnaroundTime;
    }

    return (float)totalTurnaroundTime / n;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: ./scheduler <filename> <algorithm>\n");
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    int n;
    fscanf(file, "%d", &n);

    struct Process *processes = malloc(n * sizeof(struct Process));

    int i;
    for (i = 0; i < n; i++) {
        fscanf(file, "%d %d", &(processes[i].burstTime), &(processes[i].arrivalTime));
    }
    for (i = 0; i < n; i++) {
    processes[i].waitingTime = 0;
    processes[i].turnaroundTime = 0;
    }   

    fclose(file);

    if (strcmp(argv[2], "FCFS") == 0) {
        fcfs(processes, n);
        printf("Selected Scheduling Algorithm: FCFS\n");
    } else if (strcmp(argv[2], "SJF") == 0) {
        sjf(processes, n);
        printf("Selected Scheduling Algorithm: SJF\n");
    } else {
        printf("Invalid scheduling algorithm. Available options: FCFS, SJF\n");
        return 1;
    }

    printExecutionOrder(processes, n);
    printf("Average Waiting Time: %.2f\n", calculateAverageWaitingTime(processes, n));
    printf("Average Turnaround Time: %.2f\n", calculateAverageTurnaroundTime(processes, n));

    free(processes);

    return 0;
}