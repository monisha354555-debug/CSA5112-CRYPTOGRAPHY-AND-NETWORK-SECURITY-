#include <stdio.h>
#include <ctype.h>

int main() {
    char text[100], key[100];
    int i, j = 0, k;

    printf("Enter plaintext: ");
    fgets(text, sizeof(text), stdin);

    printf("Enter key: ");
    scanf("%s", key);

    for(i = 0; text[i] != '\0'; i++) {
        if(isalpha(text[i])) {
            k = toupper(key[j %  strlen(key)]) - 'A';

            if(isupper(text[i]))
                text[i] = (text[i]-'A'+k)%26+'A';
            else
                text[i] = (text[i]-'a'+k)%26+'a';

            j++;
        }
    }

    printf("Ciphertext: %s", text);
    return 0;
}