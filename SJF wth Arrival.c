#include <stdio.h>

int main() {
    int n, i, j, time = 0, smallest;
    int burstTime[20], waitingTime[20], turnAroundTime[20], arrivalTime[20];
    int remainingBurstTime[20], completed = 0;
    float totalWaitingTime = 0, totalTurnAroundTime = 0;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    // Input arrival time and burst time for each process
    printf("Enter arrival times and burst times:\n");
    for (i = 0; i < n; i++) {
        printf("Process %d arrival time: ", i + 1);
        scanf("%d", &arrivalTime[i]);
        printf("Process %d burst time: ", i + 1);
        scanf("%d", &burstTime[i]);
        remainingBurstTime[i] = burstTime[i];
    }

    while (completed < n) {
        smallest = -1;
        for (i = 0; i < n; i++) {
            if (arrivalTime[i] <= time && remainingBurstTime[i] > 0) {
                if (smallest == -1 || remainingBurstTime[i] < remainingBurstTime[smallest]) {
                    smallest = i;
                }
            }
        }

        if (smallest != -1) {
            time += remainingBurstTime[smallest];
            waitingTime[smallest] = time - arrivalTime[smallest] - burstTime[smallest];
            turnAroundTime[smallest] = time - arrivalTime[smallest];
            remainingBurstTime[smallest] = 0;
            completed++;
            totalWaitingTime += waitingTime[smallest];
            totalTurnAroundTime += turnAroundTime[smallest];
        } else {
            time++;
        }
    }

    printf("\nProcess\tArrival Time\tBurst Time\tWaiting Time\tTurn-Around Time\n");
    for (i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", i + 1, arrivalTime[i], burstTime[i], waitingTime[i], turnAroundTime[i]);
    }

    printf("\nAverage Waiting Time: %.2f\n", totalWaitingTime / n);
    printf("Average Turn-Around Time: %.2f\n", totalTurnAroundTime / n);

    return 0;
}

