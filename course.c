#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Process {
   int burstTime;         // Time required for process execution
   int arrivalTime;       // Time at which process arrives
   int waitingTime;       // Time spent waiting in the queue
   int turnaroundTime;    // Time from arrival to completion
};

// First-Come-First-Serve (FCFS) scheduling algorithm
void fcfs(struct Process processes[], int n) {
   int i, totalWaitingTime = 0, totalTurnaroundTime = 0;

   // Calculate waiting time and turnaround time for each process
   processes[0].waitingTime = 0;
   processes[0].turnaroundTime = processes[0].burstTime;

   for (i = 1; i < n; i++) {
       processes[i].waitingTime = processes[i - 1].waitingTime + processes[i - 1].burstTime;
       processes[i].turnaroundTime = processes[i].waitingTime + processes[i].burstTime;
   }

   // Print the order of execution
   printf("Order of execution: ");
   for (i = 0; i < n; i++) {
       printf("P%d", i + 1);
       if (i != n - 1)
           printf(" -> ");
   }
   printf("\n");

   // Calculate the total waiting time and turnaround time
   for (i = 0; i < n; i++) {
       totalWaitingTime += processes[i].waitingTime;
       totalTurnaroundTime += processes[i].turnaroundTime;
   }

   // Print the average waiting time and turnaround time
   printf("Average waiting time: %.2f\n", (float)totalWaitingTime / n);
   printf("Average turnaround time: %.2f\n", (float)totalTurnaroundTime / n);
}

// Shortest Job First (SJF) scheduling algorithm
void sjf(struct Process processes[], int n) {
   int i, j, totalWaitingTime = 0, totalTurnaroundTime = 0;
   struct Process temp;

   // Sort processes based on burst time using bubble sort
   for (i = 0; i < n - 1; i++) {
       for (j = 0; j < n - i - 1; j++) {
           if (processes[j].burstTime > processes[j + 1].burstTime) {
               temp = processes[j];
               processes[j] = processes[j + 1];
               processes[j + 1] = temp;
           }
       }
   }

   // Calculate waiting time and turnaround time for each process
   processes[0].waitingTime = 0;
   processes[0].turnaroundTime = processes[0].burstTime;

   for (i = 1; i < n; i++) {
       processes[i].waitingTime = processes[i - 1].waitingTime + processes[i - 1].burstTime;
       processes[i].turnaroundTime = processes[i].waitingTime + processes[i].burstTime;
   }

   // Print the order of execution
   printf("Order of execution: ");
   for (i = 0; i < n; i++) {
       printf("P%d", i + 1);
       if (i != n - 1)
           printf(" -> ");
   }
   printf("\n");

   // Calculate the total waiting time and turnaround time
   for (i = 0; i < n; i++) {
       totalWaitingTime += processes[i].waitingTime;
       totalTurnaroundTime += processes[i].turnaroundTime;
   }

   // Print the average waiting time and turnaround time
   printf("Average waiting time: %.2f\n", (float)totalWaitingTime / n);
   printf("Average turnaround time: %.2f\n", (float)totalTurnaroundTime / n);
}

int main(int argc, char *argv[]) {
   // Check command-line arguments
   if (argc != 3) {
       printf("Usage: %s <filename> <scheduling algorithm (FCFS/SJF)>\n", argv[0]);
       return 1;
   }

   // Open the input file
   FILE *file = fopen(argv[1], "r");
   if (file == NULL) {
       printf("Error opening the file.\n");
       return 1;
   }

   int n;
   fscanf(file, "%d", &n);

   // Allocate memory for the processes
   struct Process *processes = malloc(n * sizeof(struct Process));
   if (processes == NULL) {
       printf("Memory allocation failed.\n");
       return 1;
   }

   // Read process details from the file
   int i;
   for (i = 0; i < n; i++) {
       fscanf(file, "%d %d", &processes[i].burstTime, &processes[i].arrivalTime);
       processes[i].waitingTime = 0;
       processes[i].turnaroundTime = 0;
   }

   fclose(file);

   // Execute the chosen scheduling algorithm
   if (strcmp(argv[2], "FCFS") == 0) {
       fcfs(processes, n);
   } else if (strcmp(argv[2], "SJF") == 0) {
       sjf(processes, n);
   } else {
       printf("Invalid scheduling algorithm. Please choose FCFS or SJF.\n");
       free(processes);
       return 1;
   }

   // Free allocated memory and exit
   free(processes);
   return 0;
}
