#include <stdio.h>
#include <stdlib.h>

#define FRAME_COUNT 3  // Number of frames in memory
#define PAGE_COUNT 10  // Total number of pages to simulate

void fifoPaging(int pages[], int pageCount, int frameCount) {
	int i,j;
    int frames[frameCount];
    int pageFaults = 0;
    int front = 0; // Pointer to the front of the queue
    int rear = -1; // Pointer to the rear of the queue

    // Initialize frames to -1 (empty)
    for (i = 0; i < frameCount; i++) {
        frames[i] = -1;
    }

    printf("FIFO Paging Simulation:\n");
    printf("Page Sequence: ");
    for (i = 0; i < pageCount; i++) {
        printf("%d ", pages[i]);
    }
    printf("\n");

    for (i = 0; i < pageCount; i++) {
        int page = pages[i];
        int isPageFault = 1;

        // Check if the page is already in one of the frames
        for (j = 0; j < frameCount; j++) {
            if (frames[j] == page) {
                isPageFault = 0; // Page hit
                break;
            }
        }

        if (isPageFault) {
            // Page fault occurred, replace a page using FIFO
            front = (front + 1) % frameCount; // Move front pointer
            frames[front] = page; // Replace the page

            pageFaults++;
            printf("Page %d caused a page fault. Frames: ", page);
            for (j = 0; j < frameCount; j++) {
                printf("%d ", frames[j]);
            }
            printf("\n");
        } else {
            printf("Page %d was a page hit. Frames: ", page);
            for (j = 0; j < frameCount; j++) {
                printf("%d ", frames[j]);
            }
            printf("\n");
        }
    }

    printf("Total Page Faults: %d\n", pageFaults);
}

int main() {
    // Example page reference string
    int pages[PAGE_COUNT] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3};

    fifoPaging(pages, PAGE_COUNT, FRAME_COUNT);

    return 0;
}

