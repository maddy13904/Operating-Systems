#include <stdio.h>
#include <stdlib.h>

#define MAX_BLOCKS 10
#define MAX_PROCESSES 5

void worstFit(int blockSize[], int m, int processSize[], int n) {
	int i,j;
    int allocation[MAX_PROCESSES];
    
    // Initially no block is assigned to any process
    for (i = 0; i < n; i++) {
        allocation[i] = -1;
    }
    
    // Pick each process and find a suitable block
    for (i = 0; i < n; i++) {
        int worstIdx = -1;
        for (j = 0; j < m; j++) {
            if (blockSize[j] >= processSize[i]) {
                if (worstIdx == -1 || blockSize[j] > blockSize[worstIdx]) {
                    worstIdx = j;
                }
            }
        }
        
        // If a suitable block was found
        if (worstIdx != -1) {
            // Allocate block j to p[i] process
            allocation[i] = worstIdx;
            // Reduce available memory in this block.
            blockSize[worstIdx] -= processSize[i];
        }
    }

    printf("\nProcess No.\tProcess Size\tBlock no.\n");
    for (i = 0; i < n; i++) {
        printf("   %d\t\t%d\t\t", i + 1, processSize[i]);
        if (allocation[i] != -1) {
            printf("%d\n", allocation[i] + 1);
        } else {
            printf("Not Allocated\n");
        }
    }
}

int main() {
    int blockSize[MAX_BLOCKS], processSize[MAX_PROCESSES];
    int m, n, i;

    printf("Enter the number of memory blocks: ");
    scanf("%d", &m);

    printf("Enter the sizes of the memory blocks:\n");
    for (i = 0; i < m; i++) {
        printf("Block %d: ", i + 1);
        scanf("%d", &blockSize[i]);
    }

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    printf("Enter the sizes of the processes:\n");
    for (i = 0; i < n; i++) {
        printf("Process %d: ", i + 1);
        scanf("%d", &processSize[i]);
    }

    worstFit(blockSize, m, processSize, n);

    return 0;
}

