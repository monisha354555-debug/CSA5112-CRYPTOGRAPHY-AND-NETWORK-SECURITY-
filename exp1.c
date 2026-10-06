#include <stdio.h>
#include <string.h>

int main() {
    char text[100];
    int k, i;

    printf("Enter the message: ");
    fgets(text, sizeof(text), stdin);

    printf("Enter key (1-25): ");
    scanf("%d", &k);

    for(i = 0; text[i] != '\0'; i++) {
        if(text[i] >= 'A' && text[i] <= 'Z')
            text[i] = (text[i] - 'A' + k) % 26 + 'A';
        else if(text[i] >= 'a' && text[i] <= 'z')
            text[i] = (text[i] - 'a' + k) % 26 + 'a';
    }

    printf("Ciphertext: %s", text);
    return 0;
}