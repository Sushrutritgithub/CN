#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int sendFrame(int frame);
int receiveACK();

int main() {
    int totalFrames, frame = 0;
    srand(time(NULL)); // Seed for random ACK loss simulation

    printf("Enter total number of frames to send: ");
    scanf("%d", &totalFrames);

    printf("\n--- Stop and Wait Protocol Simulation ---\n");

    while (frame < totalFrames) {
        printf("\nSender: Sending frame %d...", frame);
        if (sendFrame(frame)) {
            printf("\nReceiver: Frame %d received successfully.", frame);
            printf("\nReceiver: Sending ACK for frame %d.", frame);

            if (receiveACK()) {
                printf("\nSender: ACK for frame %d received.\n", frame);
                frame++; // move to next frame
            } else {
                printf("\nSender: ACK lost. Resending frame %d...\n", frame);
                // retransmit same frame
            }
        } else {
            printf("\nReceiver: Frame %d lost. Sender will retransmit...\n", frame);
            // retransmit same frame
        }
    }

    printf("\nAll frames sent successfully!\n");
    return 0;
}

// Simulate frame sending: returns 1 if frame is received, 0 if lost
int sendFrame(int frame) {
    // 80% chance of successful transmission
    int success = rand() % 10 < 8;
    return success;
}

// Simulate ACK receiving: returns 1 if ACK received, 0 if lost
int receiveACK() {
    // 80% chance of ACK success
    int ack = rand() % 10 < 8;
    return ack;
}
