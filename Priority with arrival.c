#include <stdio.h>

int main() {
    int n, i, j, pos, temp;
    int burstTime[20], arrivalTime[20], priority[20], waitingTime[20], turnAroundTime[20];
    float totalWaitingTime = 0, totalTurnAroundTime = 0;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    // Input burst time, arrival time, and priority for each process
    printf("Enter burst time, arrival time, and priority for each process:\n");
    for (i = 0; i < n; i++) {
        printf("Process %d burst time: ", i + 1);
        scanf("%d", &burstTime[i]);
        printf("Process %d arrival time: ", i + 1);
        scanf("%d", &arrivalTime[i]);
        printf("Process %d priority: ", i + 1);
        scanf("%d", &priority[i]);
    }

    // Sort processes by arrival time and then by priority using a simple selection sort
    for (i = 0; i < n - 1; i++) {
        pos = i;
        for (j = i + 1; j < n; j++) {
            if (arrivalTime[j] < arrivalTime[pos] || (arrivalTime[j] == arrivalTime[pos] && priority[j] < priority[pos])) {
                pos = j;
            }
        }
        // Swap arrival time
        temp = arrivalTime[i];
        arrivalTime[i] = arrivalTime[pos];
        arrivalTime[pos] = temp;
        // Swap burst time
        temp = burstTime[i];
        burstTime[i] = burstTime[pos];
        burstTime[pos] = temp;
        // Swap priority
        temp = priority[i];
        priority[i] = priority[pos];
        priority[pos] = temp;
    }

    // Calculate waiting time
    waitingTime[0] = 0;
    for (i = 1; i < n; i++) {
        waitingTime[i] = waitingTime[i - 1] + burstTime[i - 1];
        if (waitingTime[i] < arrivalTime[i]) {
            waitingTime[i] = arrivalTime[i];
        }
        waitingTime[i] -= arrivalTime[i];
    }

    // Calculate turn-around time
    for (i = 0; i < n; i++) {
        turnAroundTime[i] = waitingTime[i] + burstTime[i];
        totalWaitingTime += waitingTime[i];
        totalTurnAroundTime += turnAroundTime[i];
    }

    // Display process information
    printf("\nProcess\tBurst Time\tArrival Time\tPriority\tWaiting Time\tTurn-Around Time\n");
    for (i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", i + 1, burstTime[i], arrivalTime[i], priority[i], waitingTime[i], turnAroundTime[i]);
    }

    // Display average waiting time and turn-around time
    printf("\nAverage Waiting Time: %.2f\n", totalWaitingTime / n);
    printf("Average Turn-Around Time: %.2f\n", totalTurnAroundTime / n);

    return 0;
}

