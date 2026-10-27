#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define N 4

void display(char name[], uint8_t data[]) {
    printf("%s", name);

    for (int i = 0; i < N; i++)
        printf(" %02X", data[i]);

    printf("\n");
}

int main() {
    uint8_t plain[N] = {0x10, 0x22, 0x34, 0x46};
    uint8_t key = 0xA5, iv = 0x5A;

    uint8_t ecb[N], ecb_error[N], ecb_dec[N];
    uint8_t cbc[N], cbc_error[N], cbc_dec[N];

    for (int i = 0; i < N; i++)
        ecb[i] = plain[i] ^ key;

    memcpy(ecb_error, ecb, sizeof(ecb));
    ecb_error[1] ^= 0x04;

    for (int i = 0; i < N; i++)
        ecb_dec[i] = ecb_error[i] ^ key;

    uint8_t previous = iv;

    for (int i = 0; i < N; i++) {
        cbc[i] = (plain[i] ^ previous) ^ key;
        previous = cbc[i];
    }

    memcpy(cbc_error, cbc, sizeof(cbc));
    cbc_error[1] ^= 0x04;

    previous = iv;

    for (int i = 0; i < N; i++) {
        cbc_dec[i] = (cbc_error[i] ^ key) ^ previous;
        previous = cbc_error[i];
    }

    display("Original plaintext:", plain);
    display("ECB ciphertext:", ecb);
    display("ECB with error:", ecb_error);
    display("ECB decrypted:", ecb_dec);

    display("CBC ciphertext:", cbc);
    display("CBC with error:", cbc_error);
    display("CBC decrypted:", cbc_dec);

    return 0;
}