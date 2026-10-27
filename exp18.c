#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

int PC1[56] = {
57,49,41,33,25,17,9,1,58,50,42,34,26,18,10,2,
59,51,43,35,27,19,11,3,60,52,44,36,63,55,47,39,
31,23,15,7,62,54,46,38,30,22,14,6,61,53,45,37,
29,21,13,5,28,20,12,4
};

int PC2[48] = {
14,17,11,24,1,5,3,28,15,6,21,10,23,19,12,4,
26,8,16,7,27,20,13,2,41,52,31,37,47,55,30,40,
51,45,33,48,44,49,39,56,34,53,46,42,50,36,29,32
};

int shifts[16] = {
1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1
};

uint64_t permute(uint64_t x, int table[], int n, int bits) {
    uint64_t result = 0;

    for (int i = 0; i < n; i++)
        result = (result << 1) |
                 ((x >> (bits - table[i])) & 1ULL);

    return result;
}

int main() {
    char input[30];
    uint64_t key, subkey[16];

    printf("Enter 16-digit hexadecimal DES key: ");
    scanf("%29s", input);
    key = strtoull(input, NULL, 16);

    uint64_t k = permute(key, PC1, 56, 64);
    uint32_t c = (k >> 28) & 0x0FFFFFFF;
    uint32_t d = k & 0x0FFFFFFF;

    for (int i = 0; i < 16; i++) {
        int s = shifts[i];

        c = ((c << s) | (c >> (28 - s))) & 0x0FFFFFFF;
        d = ((d << s) | (d >> (28 - s))) & 0x0FFFFFFF;

        uint64_t combined = ((uint64_t)c << 28) | d;
        subkey[i] = permute(combined, PC2, 48, 56);
    }

    printf("DES round subkeys:\n");

    for (int i = 0; i < 16; i++)
        printf("K%d = %012llX\n",
               i + 1, (unsigned long long)subkey[i]);

    return 0;
}