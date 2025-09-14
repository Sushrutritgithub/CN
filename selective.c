#include <stdio.h>
#include <stdlib.h>

#define TOTAL_FRAMES 10
#define WINDOW_SIZE 4

int main() {
    int frame = 0;
    int ack, i, received[WINDOW_SIZE];

    while (frame < TOTAL_FRAMES) {
        // Send a window of frames
        printf("\nSender: Sending frames: ");
        for (i = 0; i < WINDOW_SIZE && (frame + i) < TOTAL_FRAMES; i++) {
            printf("%d ", frame + i);
            received[i] = 0;  // initially unacknowledged
        }
        printf("\n");

        // Simulate ACK for each frame in the window
        for (i = 0; i < WINDOW_SIZE && (frame + i) < TOTAL_FRAMES; i++) {
            printf("Receiver: ACK for frame %d? (1=Yes,0=No): ", frame + i);
            scanf("%d", &ack);
            if (ack == 1) {
                received[i] = 1;
                printf("Sender: Frame %d acknowledged.\n", frame + i);
            } else {
                printf("Sender: Frame %d lost! Will resend later.\n", frame + i);
            }
        }

        // Slide window past acknowledged frames
        i = 0;
        while (i < WINDOW_SIZE && received[i] == 1) {
            frame++;
            i++;
        }
    }
    printf("\nAll frames sent successfully using Selective Repeat ARQ!\n");
    return 0;
}
