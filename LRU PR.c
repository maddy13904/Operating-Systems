#include <stdio.h>
#include <stdlib.h>

#define FRAME_COUNT 3  // Number of frames in memory
#define PAGE_COUNT 10  // Total number of pages to simulate

// Structure to store page information
typedef struct {
    int pageNumber;
    int lastUsed; // Counter to track the last used time
} Page;

// Function to simulate LRU Paging
void lruPaging(int pages[], int pageCount, int frameCount) {
	int i,j;
    Page frames[frameCount];
    int pageFaults = 0;
    int time = 0; // Time counter to simulate the order of access

    // Initialize frames
    for (i = 0; i < frameCount; i++) {
        frames[i].pageNumber = -1;
        frames[i].lastUsed = -1;
    }

    printf("LRU Paging Simulation:\n");
    printf("Page Sequence: ");
    for (i = 0; i < pageCount; i++) {
        printf("%d ", pages[i]);
    }
    printf("\n");

    for (i = 0; i < pageCount; i++) {
        int page = pages[i];
        int isPageFault = 1;
        int lruIndex = 0;
        int lruTime = time;

        // Check if the page is already in one of the frames (page hit)
        for (j = 0; j < frameCount; j++) {
            if (frames[j].pageNumber == page) {
                isPageFault = 0; // Page hit
                frames[j].lastUsed = time; // Update last used time
                break;
            }
        }

        if (isPageFault) {
            // Find the least recently used page
            for (j = 0; j < frameCount; j++) {
                if (frames[j].lastUsed < lruTime) {
                    lruTime = frames[j].lastUsed;
                    lruIndex = j;
                }
            }

            // Replace the LRU page with the new page
            frames[lruIndex].pageNumber = page;
            frames[lruIndex].lastUsed = time;
            pageFaults++;

            printf("Page %d caused a page fault. Frames: ", page);
            for (j = 0; j < frameCount; j++) {
                printf("%d ", frames[j].pageNumber);
            }
            printf("\n");
        } else {
            printf("Page %d was a page hit. Frames: ", page);
            for (j = 0; j < frameCount; j++) {
                printf("%d ", frames[j].pageNumber);
            }
            printf("\n");
        }

        time++; // Increment time counter
    }

    printf("Total Page Faults: %d\n", pageFaults);
}

int main() {
    // Example page reference string
    int pages[PAGE_COUNT] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3};

    lruPaging(pages, PAGE_COUNT, FRAME_COUNT);

    return 0;
}

