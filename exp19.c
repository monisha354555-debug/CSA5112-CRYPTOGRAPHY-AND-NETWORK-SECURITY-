#include <stdio.h>
#include <string.h>
#include <openssl/evp.h>

int main() {
    unsigned char key[24] = "0123456789abcdefghijklmn";
    unsigned char iv[8] = "12345678";
    unsigned char plain[] = "CBC mode demonstration";
    unsigned char cipher[128], recovered[128];

    int len, total = 0, n, m;
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();

    if (ctx == NULL) {
        printf("Context creation failed.\n");
        return 1;
    }

    if (EVP_EncryptInit_ex(ctx, EVP_des_ede3_cbc(),
                           NULL, key, iv) != 1 ||
        EVP_EncryptUpdate(ctx, cipher, &len, plain,
                          strlen((char *)plain)) != 1) {
        printf("Encryption failed. Check OpenSSL support.\n");
        EVP_CIPHER_CTX_free(ctx);
        return 1;
    }

    total = len;

    if (EVP_EncryptFinal_ex(ctx, cipher + total, &len) != 1) {
        printf("Encryption finalization failed.\n");
        EVP_CIPHER_CTX_free(ctx);
        return 1;
    }

    total += len;
    EVP_CIPHER_CTX_free(ctx);

    ctx = EVP_CIPHER_CTX_new();

    if (EVP_DecryptInit_ex(ctx, EVP_des_ede3_cbc(),
                           NULL, key, iv) != 1 ||
        EVP_DecryptUpdate(ctx, recovered, &n, cipher, total) != 1 ||
        EVP_DecryptFinal_ex(ctx, recovered + n, &m) != 1) {
        printf("Decryption failed.\n");
        EVP_CIPHER_CTX_free(ctx);
        return 1;
    }

    recovered[n + m] = '\0';

    printf("Original text: %s\n", plain);
    printf("Ciphertext: ");

    for (int i = 0; i < total; i++)
        printf("%02X", cipher[i]);

    printf("\nDecrypted text: %s\n", recovered);

    EVP_CIPHER_CTX_free(ctx);
    return 0;
}