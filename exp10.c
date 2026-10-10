#include <stdio.h>
#include <ctype.h>
#include <string.h>

char m[5][5] = {
    {'M','F','H','I','K'},
    {'U','N','O','P','Q'},
    {'Z','V','W','X','Y'},
    {'E','L','A','R','G'},
    {'D','S','T','B','C'}
};

void find(char x, int *r, int *c) {
    int i, j;
    if (x == 'J') x = 'I';
    for (i = 0; i < 5; i++)
        for (j = 0; j < 5; j++)
            if (m[i][j] == x) {
                *r = i;
                *c = j;
                return;
            }
}

int main() {
    char s[200], p[200], a, b;
    int i, n = 0, r1, c1, r2, c2;

    printf("Enter message: ");
    fgets(s, sizeof(s), stdin);

    for (i = 0; s[i]; i++)
        if (isalpha((unsigned char)s[i])) {
            a = toupper(s[i]);
            if (a == 'J') a = 'I';
            p[n++] = a;
        }
    p[n] = '\0';

    printf("Ciphertext: ");
    for (i = 0; i < n; i += 2) {
        a = p[i];
        if (i + 1 == n || a == p[i+1]) {
            b = 'X';
            i--;
        } else {
            b = p[i+1];
        }

        find(a, &r1, &c1);
        find(b, &r2, &c2);

        if (r1 == r2) {
            putchar(m[r1][(c1+1)%5]);
            putchar(m[r2][(c2+1)%5]);
        } else if (c1 == c2) {
            putchar(m[(r1+1)%5][c1]);
            putchar(m[(r2+1)%5][c2]);
        } else {
            putchar(m[r1][c2]);
            putchar(m[r2][c1]);
        }
    }

    printf("\n");
    return 0;
}