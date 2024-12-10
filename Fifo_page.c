#include <stdio.h>

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
    int front = 0;           // Points to the oldest page in the frame
    int page_faults = 0;     // Count of page faults
    int page_hits = 0;       // Count of page hits
    int found;               // To check if the page is already in frame

    // Initialize all frame slots to -1 (indicating empty)
    for (int i = 0; i < frames; i++) {
        frame[i] = -1;
    }

    // FIFO algorithm to process page references
    for (int i = 0; i < n; i++) {
        found = 0;

        // Check if the page is already in a frame
        for (int j = 0; j < frames; j++) {
            if (frame[j] == pages[i]) {
                found = 1; // Page hit
                page_hits++;
                break;
            }
        }

        // If not found, replace the oldest page
        if (!found) {
            frame[front] = pages[i]; // Replace page at the front of the queue
            front = (front + 1) % frames; // Move the front pointer circularly
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

//-------------------------------------

// #include<stdio.h>
// int main(){
//     int n,frames;
//     printf("Enter the Number of pages :\n");
//     scanf("%d",&n);

//     int pages[n];
//     printf("Enter the referance string :\n");
//     for(int i=0;i<n;i++){
//         scanf("%d",&pages[i]);
//     }

//     printf("Enter the frame Size :\n");
//     scanf("%d",&frames);

//     int frame[frames];
//     int front=0;
//     int page_hit=0;
//     int page_failt=0;
//     int found;

//     for(int i=0;i<frames;i++){
//         frame[i]=-1;
//     }

//     for(int i=0;i<n;i++){
//         found=0;

//         for(int j=0;j<frames;j++){
//             if(frame[j]==pages[i]){
//                 found=1;
//                 page_hit++;
//                 break;
//             }
//         }
//         if(!found){
//             frame[front]=pages[i];
//             front =(front+1)%frames;
//             page_failt++;
//         }

//         printf("\nStep %d ",i+1);
//             for(int j=0;j<frames;j++){
//                 if(frame[j]!=-1){
//                     printf("%d ",frame[j]);

//            } else {
//                 printf("- ");
//             }
//     }
//     }

// float hit_ratio= (float)page_hit/n;
// float fault_ratio=(float)page_failt/n;

//     // Output the results
//     printf("\n\nTotal Pages: %d\n", n);
//     printf("Page Hits: %d\n", page_hit);
//     printf("Page Faults: %d\n", page_failt);
//     printf("Hit Ratio: %.2f\n", hit_ratio);
//     printf("Fault Ratio: %.2f\n", fault_ratio);



//     return 0;

// }