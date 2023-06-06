/*
    COP4610 Assignment 2 with Group [ Richard Tubbs - 6322262, Rosy, Aaron ]
    DATE
    Description
*/

/*
    COP4610 Assignment 2 with Group
    [ Richard Tubbs - 6322262, Rosy, Aaron ]
    DATE 	[6/5/2023]
    Description []
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Process {
    int burstTime;
    int arrivalTime;
    int waitingTime;
    int turnaroundTime;
};

void swap(struct Process *xp, struct Process *yp) {
    struct Process temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void sortProcessesBy(struct Process *processes, int n, int (*compare)(struct Process *, struct Process *)) {
    int i, j;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (compare(&processes[j], &processes[j + 1]) > 0) {
                swap(&processes[j], &processes[j + 1]);
            }
        }
    }
}

int compareByArrivalTime(struct Process *p1, struct Process *p2) {
    return p1->arrivalTime - p2->arrivalTime;
}

int compareByBurstTime(struct Process *p1, struct Process *p2) {
    return p1->burstTime - p2->burstTime;
}

void calculateWaitingTime(struct Process *processes, int n) {
    processes[0].waitingTime = 0;
    int i;
    for (i = 1; i < n; i++) {
        processes[i].waitingTime = processes[i - 1].waitingTime + processes[i - 1].burstTime;
    }
}

void calculateTurnaroundTime(struct Process *processes, int n) {
    int i;
    for (i = 0; i < n; i++) {
        processes[i].turnaroundTime = processes[i].waitingTime + processes[i].burstTime;
    }
}

void printOrderOfExecution(struct Process *processes, int n) {
    int i;
    printf("Order of Execution: ");
    for (i = 0; i < n; i++) {
        printf("P%d", i + 1);
        if (i != n - 1) {
            printf(" -> ");
        }
    }
    printf("\n");
}

void printAvgWaitingTime(struct Process *processes, int n) {
    int i;
    double avgWaitingTime = 0;
    for (i = 0; i < n; i++) {
        avgWaitingTime += processes[i].waitingTime;
    }
    avgWaitingTime /= n;
    printf("Average Waiting Time: %.2lf\n", avgWaitingTime);
}

void printAvgTurnaroundTime(struct Process *processes, int n) {
    int i;
    double avgTurnaroundTime = 0;
    for (i = 0; i < n; i++) {
        avgTurnaroundTime += processes[i].turnaroundTime;
    }
    avgTurnaroundTime /= n;
    printf("Average Turnaround Time: %.2lf\n", avgTurnaroundTime);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <filename> <algorithm>\n", argv[0]);
        return 1;
    }

    char *filename = argv[1];
    char *algorithm = argv[2];

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening the file.\n");
        return 1;
    }

    int numProcesses;
    fscanf(file, "%d", &numProcesses);

    struct Process *processes = (struct Process *)malloc(numProcesses * sizeof(struct Process));

    int i;
    for (i = 0; i < numProcesses; i++) {
        fscanf(file, "%d %d", &(processes[i].burstTime), &(processes[i].arrivalTime));
    }

    fclose(file);

    if (strcmp(algorithm, "FCFS") == 0) {
        sortProcessesBy(processes, numProcesses, compareByArrivalTime);
    } else if (strcmp(algorithm, "SJF") == 0) {
        sortProcessesBy(processes, numProcesses, compareByBurstTime);
    } else {
        printf("Invalid scheduling algorithm.\n");
        free(processes);
        return 1;
    }

    calculateWaitingTime(processes, numProcesses);
    calculateTurnaroundTime(processes, numProcesses);

    printOrderOfExecution(processes, numProcesses);
    printAvgWaitingTime(processes, numProcesses);
    printAvgTurnaroundTime(processes, numProcesses);

    free(processes);

    return 0;
}
