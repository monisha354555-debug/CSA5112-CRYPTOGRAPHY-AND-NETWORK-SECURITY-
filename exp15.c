#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {
    char text[500], result[500];

    printf("Enter ciphertext: ");
    fgets(text, sizeof(text), stdin);

    for (int shift = 0; shift < 26; shift++) {
        int i;

        for (i = 0; text[i]; i++) {
            if (isupper((unsigned char)text[i]))
                result[i] = 'A' +
                    (text[i] - 'A' - shift + 26) % 26;
            else if (islower((unsigned char)text[i]))
                result[i] = 'a' +
                    (text[i] - 'a' - shift + 26) % 26;
            else
                result[i] = text[i];
        }

        result[i] = '\0';
        printf("Shift %2d: %s", shift, result);
    }

    return 0;
}