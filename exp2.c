#include <stdio.h>
#include <ctype.h>

int main() {
    char text[100], key[27] = "QWERTYUIOPASDFGHJKLZXCVBNM";
    int i, x;

    printf("Enter message: ");
    fgets(text, sizeof(text), stdin);

    for(i = 0; text[i] != '\0'; i++) {
        if(isalpha(text[i])) {
            x = toupper(text[i]) - 'A';
            text[i] = key[x];
        }
    }

    printf("Ciphertext: %s", text);
    return 0;
}