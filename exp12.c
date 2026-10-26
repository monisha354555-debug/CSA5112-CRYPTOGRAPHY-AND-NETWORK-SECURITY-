#include <stdio.h>
#include <string.h>
#include <ctype.h>

int mod26(int x) {
    return (x % 26 + 26) % 26;
}

int inverse(int a) {
    for (int i = 1; i < 26; i++)
        if (mod26(a * i) == 1)
            return i;
    return -1;
}

int main() {
    char input[500], p[500], c[500], d[500];
    int k[2][2] = {{9, 4}, {5, 7}};
    int inv[2][2], n = 0;

    printf("Enter plaintext: ");
    fgets(input, sizeof(input), stdin);

    for (int i = 0; input[i]; i++)
        if (isalpha((unsigned char)input[i]))
            p[n++] = toupper((unsigned char)input[i]);

    if (n % 2)
        p[n++] = 'X';
    p[n] = '\0';

    int det = mod26(k[0][0] * k[1][1] -
                    k[0][1] * k[1][0]);
    int id = inverse(det);

    if (id == -1) {
        printf("Key matrix has no inverse.\n");
        return 1;
    }

    for (int i = 0; i < n; i += 2) {
        int a = p[i] - 'A';
        int b = p[i + 1] - 'A';

        c[i] = 'A' + mod26(k[0][0] * a + k[0][1] * b);
        c[i + 1] = 'A' + mod26(k[1][0] * a + k[1][1] * b);
    }
    c[n] = '\0';

    inv[0][0] = mod26(id * k[1][1]);
    inv[0][1] = mod26(-id * k[0][1]);
    inv[1][0] = mod26(-id * k[1][0]);
    inv[1][1] = mod26(id * k[0][0]);

    for (int i = 0; i < n; i += 2) {
        int a = c[i] - 'A';
        int b = c[i + 1] - 'A';

        d[i] = 'A' + mod26(inv[0][0] * a + inv[0][1] * b);
        d[i + 1] = 'A' + mod26(inv[1][0] * a + inv[1][1] * b);
    }
    d[n] = '\0';

    printf("Ciphertext: %s\n", c);
    printf("Decrypted text: %s\n", d);

    return 0;
}