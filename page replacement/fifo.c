#include <stdio.h>

int main() {
    int frameSize, numPages, pageFaults = 0;
    int frames[50], pages[50];
    int i, j, k, found, oldest;
    
    // Get frame size from user
    printf("Enter the number of page frames: ");
    scanf("%d", &frameSize);
    
    // Initialize all frames to -1 to indicate empty frames
    for(i = 0; i < frameSize; i++) {
        frames[i] = -1;
    }
    
    // Get page reference string from user
    printf("Enter the number of pages in the reference string: ");
    scanf("%d", &numPages);
    
    printf("Enter the page reference string: ");
    for(i = 0; i < numPages; i++) {
        scanf("%d", &pages[i]);
    }
    
    // Index to track the oldest page in frames
    oldest = 0;
    
    // Process each page in the reference string
    for(i = 0; i < numPages; i++) {
        found = 0;
        
        // Check if page is already in a frame
        for(j = 0; j < frameSize; j++) {
            if(frames[j] == pages[i]) {
                found = 1;
                break;
            }
        }
        
        // If page is not found in frames, replace the oldest page
        if(found == 0) {
            frames[oldest] = pages[i];
            oldest = (oldest + 1) % frameSize;
            pageFaults++;
            
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