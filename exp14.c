#include <stdio.h>

int main() {
    char plain[] = "sendmoremoney";
    char target[] = "cashnotneeded";
    int key[] = {9, 0, 1, 7, 23, 15, 21,
                 14, 11, 11, 2, 8, 9};
    char cipher[14];
    int i;

    for (i = 0; i < 13; i++)
        cipher[i] = 'A' + (plain[i] - 'a' + key[i]) % 26;

    cipher[13] = '\0';

    printf("Plaintext: %s\n", plain);
    printf("Ciphertext: %s\n", cipher);

    printf("Key for target plaintext: ");
    for (i = 0; i < 13; i++) {
        int c = cipher[i] - 'A';
        int p = target[i] - 'a';
        printf("%d ", (c - p + 26) % 26);
    }

    printf("\n");
    return 0;
}