#include <stdio.h>

int main() {
    int n, i,j;
    float totalWaitingTime = 0, totalTurnAroundTime = 0;
    int burstTime[20], waitingTime[20], turnAroundTime[20], priority[20];

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    // Input burst time and priority for each process
    printf("Enter burst times and priorities:\n");
    for (i = 0; i < n; i++) {
        printf("Process %d burst time: ", i + 1);
        scanf("%d", &burstTime[i]);
        printf("Process %d priority: ", i + 1);
        scanf("%d", &priority[i]);
    }

    // Sort processes by priority using simple bubble sort
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (priority[j] > priority[j + 1]) {
                // Swap priority
                int tempP = priority[j];
                priority[j] = priority[j + 1];
                priority[j + 1] = tempP;
                // Swap burst time
                int tempBT = burstTime[j];
                burstTime[j] = burstTime[j + 1];
                burstTime[j + 1] = tempBT;
            }
        }
    }

    // Calculate waiting time and turn-around time
    waitingTime[0] = 0; // First process has no waiting time
    for (i = 1; i < n; i++) {
        waitingTime[i] = waitingTime[i - 1] + burstTime[i - 1];
    }

    for (i = 0; i < n; i++) {
        turnAroundTime[i] = waitingTime[i] + burstTime[i];
        totalWaitingTime += waitingTime[i];
        totalTurnAroundTime += turnAroundTime[i];
    }

    // Display process information
    printf("\nProcess\tBurst Time\tPriority\tWaiting Time\tTurn-Around Time\n");
    for (i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", i + 1, burstTime[i], priority[i], waitingTime[i], turnAroundTime[i]);
    }

    // Display average waiting time and turn-around time
    printf("\nAverage Waiting Time: %.2f\n", totalWaitingTime / n);
    printf("Average Turn-Around Time: %.2f\n", totalTurnAroundTime / n);

    return 0;
}

