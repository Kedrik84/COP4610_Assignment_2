#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int burstTime;
    int arrivalTime;
    int waitingTime;
    int turnaroundTime;
} Process;

void fcfsScheduling(Process processes[], int n) {
    int currentTime = 0;
    int i;

    for (i = 0; i < n; i++) {
        if (currentTime < processes[i].arrivalTime)
            currentTime = processes[i].arrivalTime;

        processes[i].waitingTime = currentTime - processes[i].arrivalTime;
        currentTime += processes[i].burstTime;
        processes[i].turnaroundTime = currentTime - processes[i].arrivalTime;
    }
}

void sjfScheduling(Process processes[], int n) {
    int completedProcesses = 0;
    int currentTime = 0;
    int i, shortestJob;

    while (completedProcesses < n) {
        shortestJob = -1;

        for (i = 0; i < n; i++) {
            if (processes[i].arrivalTime <= currentTime && processes[i].burstTime > 0) {
                if (shortestJob == -1 || processes[i].burstTime < processes[shortestJob].burstTime) {
                    shortestJob = i;
                }
            }
        }

        if (shortestJob == -1) {
            currentTime++;
        } else {
            processes[shortestJob].waitingTime = currentTime - processes[shortestJob].arrivalTime;
            currentTime += processes[shortestJob].burstTime;
            processes[shortestJob].turnaroundTime = currentTime - processes[shortestJob].arrivalTime;
            processes[shortestJob].burstTime = 0;
            completedProcesses++;
        }
    }
}

void calculateAverageTimes(Process processes[], int n, float *avgWaitingTime, float *avgTurnaroundTime) {
    int totalWaitingTime = 0;
    int totalTurnaroundTime = 0;
    int i;

    for (i = 0; i < n; i++) {
        totalWaitingTime += processes[i].waitingTime;
        totalTurnaroundTime += processes[i].turnaroundTime;
    }

    *avgWaitingTime = (float)totalWaitingTime / n;
    *avgTurnaroundTime = (float)totalTurnaroundTime / n;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <filename> <scheduling algorithm>\n", argv[0]);
        return 1;
    }

    char *filename = argv[1];
    char *algorithm = argv[2];
    FILE *file = fopen(filename, "r");
    int n;

    if (file == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    fscanf(file, "%d", &n);
    Process *processes = (Process *)malloc(n * sizeof(Process));

    int i;
    for (i = 0; i < n; i++) {
        fscanf(file, "%d %d", &processes[i].burstTime, &processes[i].arrivalTime);
        processes[i].waitingTime = 0;
        processes[i].turnaroundTime = 0;
    }

    fclose(file);

    if (strcmp(algorithm, "FCFS") == 0) {
        fcfsScheduling(processes, n);
    } else if (strcmp(algorithm, "SJF") == 0) {
        sjfScheduling(processes, n);
    } else {
        printf("Invalid scheduling algorithm.\n");
        free(processes);
        return 1;
    }

    float avgWaitingTime, avgTurnaroundTime;
    calculateAverageTimes(processes, n, &avgWaitingTime, &avgTurnaroundTime);

    printf("Process execution order: ");
    for (i = 0; i < n; i++) {
        printf("P%d", i + 1);
        if (i != n - 1) {
            printf(" -> ");
        }
    }
    printf("\n");
    printf("Average waiting time: %.2f\n", avgWaitingTime);
    printf("Average turnaround time: %.2f\n", avgTurnaroundTime);

    free(processes);

    return 0;
}
