#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <arpa/inet.h>

int main() {
    char choice, hostname[100], ipstr[100];
    struct hostent *host;
    struct in_addr addr;

    printf("Choose an option:\n");
    printf("1. Get IP address from Domain Name\n");
    printf("2. Get Domain Name from IP address\n");
    printf("Enter your choice (1 or 2): ");
    scanf(" %c", &choice);

    if (choice == '1') {
        printf("\nEnter Domain Name: ");
        scanf("%s", hostname);

        host = gethostbyname(hostname);
        if (host == NULL) {
            perror("gethostbyname failed");
            exit(1);
        }

        printf("\nOfficial Name: %s\n", host->h_name);

        printf("IP addresses:\n");
        for (int i = 0; host->h_addr_list[i] != NULL; i++) {
            addr.s_addr = *(long *)host->h_addr_list[i];
            printf("  %s\n", inet_ntoa(addr));
        }

    } else if (choice == '2') {
        printf("\nEnter IP Address: ");
        scanf("%s", ipstr);

        inet_aton(ipstr, &addr);
        host = gethostbyaddr((const void *)&addr, sizeof(addr), AF_INET);
        if (host == NULL) {
            perror("gethostbyaddr failed");
            exit(1);
        }

        printf("\nOfficial Domain Name: %s\n", host->h_name);

        printf("Aliases:\n");
        for (int i = 0; host->h_aliases[i] != NULL; i++) {
            printf("  %s\n", host->h_aliases[i]);
        }

    } else {
        printf("\nInvalid choice!\n");
    }

    return 0;
}
