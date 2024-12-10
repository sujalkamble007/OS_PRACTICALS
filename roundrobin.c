#include <stdio.h>

#define MAX 10

int main() {
    int arrival_time[MAX], burst_time[MAX], remaining_time[MAX];
    int completion_time[MAX], waiting_time[MAX], turnaround_time[MAX];
    int n, i, time = 0, count = 0;
    float avg_waiting_time, avg_turnaround_time;
    int time_quantum;

    printf("Enter the total number of processes (max %d): ", MAX);
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        printf("Enter Arrival Time of Process %d: ", i + 1);
        scanf("%d", &arrival_time[i]);
        printf("Enter Burst Time of Process %d: ", i + 1);
        scanf("%d", &burst_time[i]);
        remaining_time[i] = burst_time[i];
    }

    printf("Enter Time Quantum: ");
    scanf("%d", &time_quantum);

    int queue[100];
    int front = 0, rear = 0;
    int completed[MAX] = {0};

    // Initial population of the queue
    for (i = 0; i < n; i++) {
        if (arrival_time[i] <= time && !completed[i]) {
            queue[rear++] = i;
        }
    }

    while (count < n) {
        int process_executed = 0;

        // Process each item in the queue
        for (int k = front; k < rear; k++) {
            int current_process = queue[k];

            if (remaining_time[current_process] > 0 && arrival_time[current_process] <= time) {
                process_executed = 1;

                // Execute current process for time quantum or remaining time, whichever is smaller
                int execution_time = (remaining_time[current_process] > time_quantum) ? time_quantum : remaining_time[current_process];
                remaining_time[current_process] -= execution_time;
                time += execution_time;

                // If process completes, update its completion, turnaround, and waiting times
                if (remaining_time[current_process] == 0) {
                    completed[current_process] = 1;
                    count++;
                    completion_time[current_process] = time;
                    turnaround_time[current_process] = completion_time[current_process] - arrival_time[current_process];
                    waiting_time[current_process] = turnaround_time[current_process] - burst_time[current_process];
                }
            }
        }

        // Check if any process arrived during execution and add to queue
        for (i = 0; i < n; i++) {
            if (arrival_time[i] <= time && !completed[i] && i != queue[rear-1]) {
                queue[rear++] = i;
            }
        }

        // If no process was executed, increase time until next process arrives
        if (!process_executed) {
            time++;
            for (i = 0; i < n; i++) {
                if (arrival_time[i] <= time && !completed[i]) {
                    queue[rear++] = i;
                }
            }
        }
    }

    int total_waiting_time = 0;
    int total_turnaround_time = 0;

    printf("\nProcess\tArrival Time\tBurst Time\tCompletion Time\tWaiting Time\tTurnaround Time\n");
    for (i = 0; i < n; i++) {
        total_waiting_time += waiting_time[i];
        total_turnaround_time += turnaround_time[i];
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
               i + 1,
               arrival_time[i],
               burst_time[i],
               completion_time[i],
               waiting_time[i],
               turnaround_time[i]);
    }

    avg_waiting_time = (float)total_waiting_time / n;
    avg_turnaround_time = (float)total_turnaround_time / n;

    printf("\nAverage Waiting Time: %.2f\n", avg_waiting_time);
    printf("Average Turnaround Time: %.2f\n", avg_turnaround_time);

    return 0;
}
