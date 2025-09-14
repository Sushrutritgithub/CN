#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<time.h>

int main() {
    // Implementation of Go-Back-N ARQ protocol
    int tframes, windsize;
    int frame_acked, i;

    printf("Total number of frames to send: ");
    scanf("%d", &tframes);
    printf("Enter window Size: ");
    scanf("%d", &windsize);

    srand(time(0));
    i = 1;
    while(i <= tframes) {
        int j;
        printf("\nSender: Sending frame %d to %d\n", i,(i + windsize - 1 <= tframes) ? (i + windsize - 1) : tframes);
        frame_acked = i;
        for(j = frame_acked; j < i && j <= tframes; j++) {
            sleep(1);

            if(rand() % 4 == 0) {
                printf("Sender: Frame %d lost\n", j);
                break;
            }
            else {
                printf("Receiver: Frame %d recieved succesfully. Sending ACK%d\n", j, j);
                frame_acked = j;
            }
        }
        if(frame_acked == i + windsize - 1 || frame_acked == tframes) {
            i = frame_acked + 1;
        }
        else {
            printf("Sender: Timeout occurred. Resending frames from %d\n", frame_acked + 1);
            i = frame_acked + 1;
        }
    }
    printf("Sender: All frames sent successfully.\n");
    return 0;
}