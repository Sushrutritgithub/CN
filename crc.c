#include <stdio.h>
#include <string.h>

int main() {
    char data[50], divisor[10], temp[50], remainder[10];
    int i, j, datalen, divlen;

    printf("Enter Data (binary): ");
    scanf("%s", data);
    printf("Enter Generator Polynomial (binary): ");
    scanf("%s", divisor);

    datalen = strlen(data);
    divlen = strlen(divisor);

    // Append (divlen-1) zeros to data
    strcpy(temp, data);
    for (i = 0; i < divlen - 1; i++) {
        strcat(temp, "0");
    }

    // Copy to remainder
    strncpy(remainder, temp, divlen);
    remainder[divlen] = '\0';

    // Division process
    for (i = 0; i < datalen; i++) {
        if (remainder[0] == '1') {
            for (j = 1; j < divlen; j++) {
                remainder[j] = (remainder[j] == divisor[j]) ? '0' : '1';
            }
        }
        // Shift left and bring next bit down
        for (j = 0; j < divlen - 1; j++) {
            remainder[j] = remainder[j + 1];
        }
        remainder[divlen - 1] = temp[i + divlen];
    }

    printf("\nCRC Remainder: %s\n", remainder);

    // Append remainder to original data (codeword)
    strcat(data, remainder);
    printf("Transmitted Codeword: %s\n", data);

    return 0;
}
