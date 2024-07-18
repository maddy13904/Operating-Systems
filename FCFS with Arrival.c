#include <stdio.h>
int main() {
    int n, i;
    int burstTime[20], waitingTime[20], turnAroundTime[20], arrivalTime[20];
    int totalWaitingTime = 0, totalTurnAroundTime = 0;
    
    // Input the number of processes
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    
    // Input arrival time and burst time for each process
    printf("Enter arrival times and burst times:\n");
    for (i = 0; i < n; i++) {
        printf("Process %d arrival time: ", i + 1);
        scanf("%d", &arrivalTime[i]);
        printf("Process %d burst time: ", i + 1);
        scanf("%d", &burstTime[i]);
    }
    
    // Calculate waiting time for each process
    waitingTime[0] = 0; // First process has no waiting time
    for (i = 1; i < n; i++) {
        waitingTime[i] = burstTime[i - 1] + waitingTime[i - 1] - arrivalTime[i] + arrivalTime[i - 1];
        if (waitingTime[i] < 0) {
            waitingTime[i] = 0;
        }
    }
    
    // Calculate turn-around time for each process
    for (i = 0; i < n; i++) {
        turnAroundTime[i] = burstTime[i] + waitingTime[i];
    }
    
    // Calculate total waiting time and total turn-around time
    for (i = 0; i < n; i++) {
        totalWaitingTime += waitingTime[i];
        totalTurnAroundTime += turnAroundTime[i];
    }
    
    // Display process information
    printf("\nProcess\tArrival Time\tBurst Time\tWaiting Time\tTurn-Around Time\n");
    for (i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", i + 1, arrivalTime[i], burstTime[i], waitingTime[i], turnAroundTime[i]);
    }
    
    // Display average waiting time and turn-around time
    printf("\nAverage Waiting Time: %.2f\n", (float)totalWaitingTime / n);
    printf("Average Turn-Around Time: %.2f\n", (float)totalTurnAroundTime / n);
    
    return 0;
}
