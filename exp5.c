#include <stdio.h>
#include <ctype.h>

int main() {
    char text[100];
    int a, b, i, p;

    printf("Enter plaintext: ");
    fgets(text, sizeof(text), stdin);

    printf("Enter a and b: ");
    scanf("%d%d", &a, &b);

    for(i = 0; text[i] != '\0'; i++) {
        if(isalpha(text[i])) {
            p = toupper(text[i]) - 'A';
            text[i] = (a * p + b) % 26 + 'A';
        }
    }

    printf("Ciphertext: %s", text);
    return 0;
}