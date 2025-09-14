#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int TOTAL_FRAMES, WINDOW_SIZE;
    int frame = 0, i, received[50];

    printf("Enter number of frames to send: ");
    scanf("%d", &TOTAL_FRAMES);

    printf("Enter window size: ");
    scanf("%d", &WINDOW_SIZE);

    srand(time(NULL));

    while (frame < TOTAL_FRAMES) {
        printf("\nSender: Sending frames: ");
        for (i = 0; i < WINDOW_SIZE && (frame + i) < TOTAL_FRAMES; i++) {
            printf("%d ", frame + i);
            received[i] = 0;
        }
        printf("\n");

        for (i = 0; i < WINDOW_SIZE && (frame + i) < TOTAL_FRAMES; i++) {
            int ack = rand() % 2;
            if (ack == 1) {
                received[i] = 1;
                printf("Receiver: Frame %d received. ACK sent.\n", frame + i);
            } else {
                printf("Receiver: Frame %d lost! No ACK.\n", frame + i);
            }
        }

        i = 0;
        while (i < WINDOW_SIZE && received[i] == 1) {
            frame++;
            i++;
        }
    }

    printf("\nAll frames sent successfully using Selective Repeat ARQ!\n");
    return 0;
}
