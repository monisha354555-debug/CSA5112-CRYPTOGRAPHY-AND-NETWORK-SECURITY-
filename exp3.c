#include <stdio.h>
#include <string.h>
#include <ctype.h>

char mat[5][5];

void create(char key[]) {
    int used[26] = {0}, i, j = 0, k;
    char c;

    for(i = 0; key[i]; i++) {
        c = toupper(key[i]);
        if(c == 'J') c = 'I';
        if(c >= 'A' && c <= 'Z' && !used[c-'A']) {
            mat[j/5][j%5] = c;
            used[c-'A'] = 1;
            j++;
        }
    }

    for(k = 0; k < 26; k++) {
        if(k == 9) continue;   // Skip J
        if(!used[k]) {
            mat[j/5][j%5] = 'A' + k;
            j++;
        }
    }
}

void find(char c, int *r, int *col) {
    int i, j;
    if(c == 'J') c = 'I';

    for(i = 0; i < 5; i++)
        for(j = 0; j < 5; j++)
            if(mat[i][j] == c) {
                *r = i;
                *col = j;
            }
}

int main() {
    char key[50], text[100], out[200];
    int i, n = 0, r1, c1, r2, c2;

    printf("Enter key: ");
    scanf("%s", key);

    printf("Enter plaintext: ");
    scanf(" %[^\n]", text);

    create(key);

    for(i = 0; text[i]; i++)
        if(isalpha(text[i])) {
            text[n++] = toupper(text[i]);
        }
    text[n] = '\0';

    if(n % 2) text[n++] = 'X';
    text[n] = '\0';

    for(i = 0; i < n; i += 2) {
        find(text[i], &r1, &c1);
        find(text[i+1], &r2, &c2);

        if(r1 == r2) {
            out[i]   = mat[r1][(c1+1)%5];
            out[i+1] = mat[r2][(c2+1)%5];
        }
        else if(c1 == c2) {
            out[i]   = mat[(r1+1)%5][c1];
            out[i+1] = mat[(r2+1)%5][c2];
        }
        else {
            out[i]   = mat[r1][c2];
            out[i+1] = mat[r2][c1];
        }
    }

    out[n] = '\0';
    printf("Ciphertext: %s\n", out);

    return 0;
}