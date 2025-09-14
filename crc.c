#include <stdio.h>
#include <string.h>

int main() {
    char data[50], divisor[10], codeword[60];
    int datalen, divlen, i, j;

    printf("Enter Data (binary): ");
    scanf("%s", data);
    printf("Enter Generator Polynomial (binary): ");
    scanf("%s", divisor);

    datalen = strlen(data);
    divlen = strlen(divisor);

    strcpy(codeword, data);
    for (i = 0; i < divlen - 1; i++) strcat(codeword, "0");

    for (i = 0; i < datalen; i++) {
        if (codeword[i] == '1') {
            for (j = 0; j < divlen; j++) {
                codeword[i + j] = (codeword[i + j] == divisor[j]) ? '0' : '1';
            }
        }
    }

    printf("\nCRC Remainder: ");
    for (i = datalen; i < datalen + divlen - 1; i++) printf("%c", codeword[i]);

    strcpy(codeword, data);
    for (i = datalen; i < datalen + divlen - 1; i++) strncat(codeword, &codeword[i], 1);

    printf("\nTransmitted Codeword: %s\n", codeword);

    return 0;
}
