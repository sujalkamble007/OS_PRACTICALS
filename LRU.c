#include <stdio.h>

#define MAX 100

int findLRU(int time[], int n) {
    int i, minimum = time[0], pos = 0;
    for (i = 1; i < n; ++i) {
        if (time[i] < minimum) {
            minimum = time[i];
            pos = i;
        }
    }
    return pos;
}

int main() {
    int no_of_frames = 3, no_of_pages, frames[3], pages[MAX], time[3], flag1, flag2, i, j, pos, page_faults = 0, page_hits = 0;
    float fault_ratio, hit_ratio;

    printf("Enter number of pages: ");
    scanf("%d", &no_of_pages);

    printf("Enter reference string (space-separated): ");
    for (i = 0; i < no_of_pages; ++i) {
        scanf("%d", &pages[i]);
    }

    for (i = 0; i < no_of_frames; ++i) {
        frames[i] = -1;
    }

    for (i = 0; i < no_of_pages; ++i) {
        flag1 = flag2 = 0;
        for (j = 0; j < no_of_frames; ++j) {
            if (frames[j] == pages[i]) {
                flag1 = flag2 = 1;
                page_hits++;
                time[j] = i + 1; // Update the time of reference
                break;
            }
        }

        if (flag1 == 0) {
            for (j = 0; j < no_of_frames; ++j) {
                if (frames[j] == -1) {
                    page_faults++;
                    frames[j] = pages[i];
                    time[j] = i + 1; // Store the time of reference
                    flag2 = 1;
                    break;
                }
            }
        }

        if (flag2 == 0) {
            pos = findLRU(time, no_of_frames);
            frames[pos] = pages[i];
            time[pos] = i + 1; // Update the time of replacement
            page_faults++;
        }

        printf("\nFrames: ");
        for (j = 0; j < no_of_frames; ++j) {
            if (frames[j] != -1) {
                printf("%d ", frames[j]);
            } else {
                printf("- ");
            }
        }
    }

    fault_ratio = (float) page_faults / no_of_pages;
    hit_ratio = (float) page_hits / no_of_pages;

    printf("\n\nPage Faults: %d", page_faults);
    printf("\nPage Hits: %d", page_hits);
    printf("\nFault Ratio: %.2f", fault_ratio);
    printf("\nHit Ratio: %.2f\n", hit_ratio);

    return 0;
}
