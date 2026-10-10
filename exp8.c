#include <stdio.h>
#include <ctype.h>

int main() {
    char p[100], key[] = "CIPHERABDFGJKLMNOQSTUVWXYZ";
    int i, x;

    printf("Enter plaintext: ");
    fgets(p, sizeof(p), stdin);

    printf("Ciphertext: ");
    for (i = 0; p[i]; i++) {
        if (isalpha((unsigned char)p[i])) {
            x = toupper((unsigned char)p[i]) - 'A';
            putchar(key[x]);
        } else {
            putchar(p[i]);
        }
    }

    return 0;
}