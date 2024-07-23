#include <stdio.h>
#include <stdbool.h>

#define P 5 // Number of processes
#define R 3 // Number of resources

int available[R] = {3, 3, 2}; // Total available instances of each resource
int max[P][R] = {
    {7, 5, 3},
    {3, 2, 2},
    {9, 0, 2},
    {2, 2, 2},
    {4, 3, 3}
};
int allocation[P][R] = {
    {0, 1, 0},
    {2, 0, 0},
    {3, 0, 2},
    {2, 1, 1},
    {0, 0, 2}
};
int need[P][R];

void calculateNeed() {
	int i,j;
    for (i = 0; i < P; i++) {
        for ( j = 0; j < R; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }
}

bool isSafe() {
	int k,p,i,count,j;
    int work[R];
    bool finish[P] = {0};

    for (i = 0; i < R; i++) {
        work[i] = available[i];
    }

    for (count = 0; count < P; count++) {
        bool found = false;
        for (p = 0; p < P; p++) {
            if (!finish[p]) {
                bool possible = true;
                for (j = 0; j < R; j++) {
                    if (need[p][j] > work[j]) {
                        possible = false;
                        break;
                    }
                }
                if (possible) {
                    for ( k = 0; k < R; k++) {
                        work[k] += allocation[p][k];
                    }
                    finish[p] = true;
                    found = true;
                }
            }
        }
        if (!found) {
            return false;
        }
    }
    return true;
}

bool requestResources(int process, int request[R]) {
	int i;
    for ( i = 0; i < R; i++) {
        if (request[i] > need[process][i]) {
            printf("Request exceeds maximum claim.\n");
            return false;
        }
        if (request[i] > available[i]) {
            printf("Request exceeds available resources.\n");
            return false;
        }
    }

    for ( i = 0; i < R; i++) {
        available[i] -= request[i];
        allocation[process][i] += request[i];
        need[process][i] -= request[i];
    }

    if (isSafe()) {
        return true;
    } else {
        for (i = 0; i < R; i++) {
            available[i] += request[i];
            allocation[process][i] -= request[i];
            need[process][i] += request[i];
        }
        printf("Request leads to unsafe state, denied.\n");
        return false;
    }
}

int main() {
    calculateNeed();

    int process = 1;
    int request[R] = {1, 0, 2};

    if (requestResources(process, request)) {
        printf("Request granted.\n");
    } else {
        printf("Request denied.\n");
    }

    return 0;
}
