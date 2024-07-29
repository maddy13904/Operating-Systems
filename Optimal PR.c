#include <stdio.h>
#include <stdlib.h>

int findFarthestFuture(int pages[], int frames[], int currentPageIndex, int frameCount, int totalPageCount) {
    int farthest = currentPageIndex;
    int frameIndex = -1;
    int i;
    for (i = 0; i < frameCount; i++) {
        int j;
        for (j = currentPageIndex; j < totalPageCount; j++) {
            if (frames[i] == pages[j]) {
                if (j > farthest) {
                    farthest = j;
                    frameIndex = i;
                }
                break;
            }
        }
        if (j == totalPageCount) {
            return i;
        }
    }
    return (frameIndex == -1) ? 0 : frameIndex;
}

int isPageInFrames(int page, int frames[], int frameCount) {
	int i;
    for (i = 0; i < frameCount; i++) {
        if (frames[i] == page) {
            return 1;
        }
    }
    return 0;
}

void optimalPageReplacement(int pages[], int totalPageCount, int frameCount) {
	int i,j;
    int frames[frameCount];
    int pageFaults = 0;
    int currentFrameIndex = 0;

    for (i = 0; i < frameCount; i++) {
        frames[i] = -1;
    }

    for (i = 0; i < totalPageCount; i++) {
        if (!isPageInFrames(pages[i], frames, frameCount)) {
            if (frames[currentFrameIndex] == -1) {
                frames[currentFrameIndex] = pages[i];
                currentFrameIndex = (currentFrameIndex + 1) % frameCount;
            } else {
                int farthestIndex = findFarthestFuture(pages, frames, i, frameCount, totalPageCount);
                frames[farthestIndex] = pages[i];
            }
            pageFaults++;
        }

        printf("Frames after page %d: ", pages[i]);
        for (j = 0; j < frameCount; j++) {
            if (frames[j] == -1) {
                printf("- ");
            } else {
                printf("%d ", frames[j]);
            }
        }
        printf("\n");
    }

    printf("Total page faults: %d\n", pageFaults);
}

int main() {
    int pages[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2};
    int totalPageCount = sizeof(pages) / sizeof(pages[0]);
    int frameCount = 4;

    optimalPageReplacement(pages, totalPageCount, frameCount);

    return 0;
}

