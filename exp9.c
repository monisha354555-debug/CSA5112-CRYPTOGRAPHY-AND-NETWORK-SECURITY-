#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {
    char key[100], c[500], m[25], used[26] = {0};
    int i, j, k = 0, a, b, r1, c1, r2, c2;

    printf("Enter keyword: ");
    scanf("%99s", key);
    printf("Enter ciphertext without spaces: ");
    scanf("%499s", c);

    for (i = 0; key[i]; i++) {
        char x = toupper(key[i]);
        if (x == 'J') x = 'I';
        if (x >= 'A' && x <= 'Z' && !used[x-'A']) {
            m[k++] = x;
            used[x-'A'] = 1;
        }
    }

    for (i = 0; i < 26; i++)
        if (i != ('J'-'A') && !used[i])
            m[k++] = 'A' + i;

    printf("Plaintext: ");
    for (i = 0; c[i] && c[i+1]; i += 2) {
        a = toupper(c[i]) - 'A';
        b = toupper(c[i+1]) - 'A';
        if (a == 9) a = 8;
        if (b == 9) b = 8;

        for (j = 0; j < 25; j++) {
            if (m[j] == 'A' + a) r1 = j/5, c1 = j%5;
            if (m[j] == 'A' + b) r2 = j/5, c2 = j%5;
        }

        if (r1 == r2) {
            putchar(m[r1*5+(c1+4)%5]);
            putchar(m[r2*5+(c2+4)%5]);
        } else if (c1 == c2) {
            putchar(m[((r1+4)%5)*5+c1]);
            putchar(m[((r2+4)%5)*5+c2]);
        } else {
            putchar(m[r1*5+c2]);
            putchar(m[r2*5+c1]);
        }
    }
    printf("\n");
    return 0;
}