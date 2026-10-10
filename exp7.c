#include <stdio.h>

int main() {
    char s[2000], ch[128];
    int f[128] = {0}, i, j, t;
    char x;

    printf("Enter ciphertext:\n");
    fgets(s, sizeof(s), stdin);

    for (i = 0; s[i]; i++)
        if ((unsigned char)s[i] < 128)
            f[(unsigned char)s[i]]++;

    for (i = 0; i < 128; i++)
        ch[i] = i;

    for (i = 0; i < 127; i++)
        for (j = i + 1; j < 128; j++)
            if (f[(unsigned char)ch[j]] >
                f[(unsigned char)ch[i]]) {
                x = ch[i];
                ch[i] = ch[j];
                ch[j] = x;
            }

    printf("Most frequent symbols:\n");
    for (i = 0; i < 128 && f[(unsigned char)ch[i]] > 0; i++)
        printf("%c : %d\n",
               ch[i] == '\n' ? ' ' : ch[i],
               f[(unsigned char)ch[i]]);

    return 0;
}