#include <stdio.h>
#include <stdlib.h>

int main() {
    int frameSize, numPages, pageFaults = 0;
    int frames[100], pages[100], frequency[100];
    int i, j, k, found, leastFreqIndex;
    
    // Get frame size from user
    printf("Enter the number of page frames: ");
    scanf("%d", &frameSize);
    
    // Initialize all frames to -1 to indicate empty frames
    for(i = 0; i < frameSize; i++) {
        frames[i] = -1;
        frequency[i] = 0;  // Initialize frequency counter
    }
    
    // Get page reference string from user
    printf("Enter the number of pages in the reference string: ");
    scanf("%d", &numPages);
    
    printf("Enter the page reference string: ");
    for(i = 0; i < numPages; i++) {
        scanf("%d", &pages[i]);
    }
    
    // Process each page in the reference string
    for(i = 0; i < numPages; i++) {
        found = 0;
        
        // Check if page is already in a frame
        for(j = 0; j < frameSize; j++) {
            if(frames[j] == pages[i]) {
                found = 1;
                frequency[j]++;  // Increment frequency counter for this page
                break;
            }
        }
        
        // If page is not found in frames, replace the least frequently used page
        if(found == 0) {
            // Check if there's an empty frame
            int emptyFrameFound = 0;
            for(j = 0; j < frameSize; j++) {
                if(frames[j] == -1) {
                    frames[j] = pages[i];
                    frequency[j] = 1;  // Set initial frequency
                    emptyFrameFound = 1;
                    pageFaults++;
                    break;
                }
            }
            
            // If no empty frame, find the least frequently used page
            if(!emptyFrameFound) {
                leastFreqIndex = 0;
                for(j = 1; j < frameSize; j++) {
                    if(frequency[j] < frequency[leastFreqIndex]) {
                        leastFreqIndex = j;
                    }
                }
                
                // In case of tie, we could implement a tie-breaker here
                // For simplicity, we're just taking the first least frequent page
                
                // Replace the least frequently used page
                frames[leastFreqIndex] = pages[i];
                frequency[leastFreqIndex] = 1;  // Reset frequency for new page
                pageFaults++;
            }
            
            // Display current state of frames
            printf("Page %d -> ", pages[i]);
            for(k = 0; k < frameSize; k++) {
                if(frames[k] == -1) {
                    printf("Empty ");
                } else {
                    printf("%d ", frames[k]);
                }
            }
            printf("Page Fault!\n");
        } else {
            // Display current state of frames when page is found
            printf("Page %d -> ", pages[i]);
            for(k = 0; k < frameSize; k++) {
                if(frames[k] == -1) {
                    printf("Empty ");
                } else {
                    printf("%d ", frames[k]);
                }
            }
            printf("No Page Fault\n");
        }
    }
    
    // Display total number of page faults
    printf("\nTotal Page Faults: %d\n", pageFaults);
    
    return 0;
}