#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {
    char c[1000];
    int a[] = {1,3,5,7,9,11,15,17,19,21,23,25};
    int i, j, k, b, p;

    printf("Enter ciphertext: ");
    fgets(c, sizeof(c), stdin);

    for (k = 0; k < 12; k++) {
        for (b = 0; b < 26; b++) {
            printf("\na=%d, b=%d: ", a[k], b);

            for (i = 0; c[i] != '\0'; i++) {
                if (isalpha((unsigned char)c[i])) {
                    j = toupper((unsigned char)c[i]) - 'A';

                    for (p = 0; p < 26; p++)
                        if ((a[k] * p + b) % 26 == j)
                            break;

                    putchar(p + 'A');
                } else {
                    putchar(c[i]);
                }
            }
        }
    }
    return 0;
}