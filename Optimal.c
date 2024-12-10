#include <stdio.h>

int findOptimal(int frame[], int frames, int pages[], int n, int current) {
    int farthest = current;
    int index = -1;

    // Check which frame page will not be used for the longest time
    for (int i = 0; i < frames; i++) {
        int j;
        for (j = current + 1; j < n; j++) {
            if (frame[i] == pages[j]) {
                if (j > farthest) {
                    farthest = j;
                    index = i;
                }
                break;
            }
        }

        // If a page is not going to be used again, return its index
        if (j == n) {
            return i;
        }
    }

    // If no page is found, replace the one with the farthest usage
    return (index == -1) ? 0 : index;
}

int main() {
    int n, frames;

    // Input total pages and their references
    printf("Enter the total number of pages: ");
    scanf("%d", &n);

    int pages[n];
    printf("Enter the page reference string (space-separated): ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &pages[i]);
    }

    // Input number of page frames
    printf("Enter the number of page frames: ");
    scanf("%d", &frames);

    int frame[frames];       // To store pages in memory
    int page_faults = 0;     // Count of page faults
    int page_hits = 0;       // Count of page hits
    int found;               // To check if the page is already in frame

    // Initialize all frame slots to -1 (indicating empty)
    for (int i = 0; i < frames; i++) {
        frame[i] = -1;
    }

    // Process each page
    for (int i = 0; i < n; i++) {
        found = 0;

        // Check if the page is already in a frame (Page Hit)
        for (int j = 0; j < frames; j++) {
            if (frame[j] == pages[i]) {
                found = 1; // Page hit
                page_hits++;
                break;
            }
        }

        // If not found, replace a page (Page Fault)
        if (!found) {
            int replace_index;

            // If there are empty slots, use them first
            for (replace_index = 0; replace_index < frames; replace_index++) {
                if (frame[replace_index] == -1) {
                    break;
                }
            }

            // If no empty slot, find the optimal page to replace
            if (replace_index == frames) {
                replace_index = findOptimal(frame, frames, pages, n, i);
            }

            // Replace the page
            frame[replace_index] = pages[i];
            page_faults++;
        }

        // Print the current frame contents
        printf("\nStep %d: ", i + 1);
        for (int j = 0; j < frames; j++) {
            if (frame[j] != -1) {
                printf("%d ", frame[j]);
            } else {
                printf("- "); // Empty slot
            }
        }
    }

    // Calculate hit and fault ratios
    float hit_ratio = (float)page_hits / n;
    float fault_ratio = (float)page_faults / n;

    // Output the results
    printf("\n\nTotal Pages: %d\n", n);
    printf("Page Hits: %d\n", page_hits);
    printf("Page Faults: %d\n", page_faults);
    printf("Hit Ratio: %.2f\n", hit_ratio);
    printf("Fault Ratio: %.2f\n", fault_ratio);

    return 0;
}
