#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {
    char text[1000], result[1000];
    int freq[26] = {0}, used[26] = {0};
    char order[26], map[26];
    char english[] = "ETAOINSHRDLCUMWFGYPBVKJXQZ";

    printf("Enter ciphertext: ");
    fgets(text, sizeof(text), stdin);

    for (int i = 0; text[i]; i++)
        if (isalpha((unsigned char)text[i]))
            freq[toupper((unsigned char)text[i]) - 'A']++;

    for (int i = 0; i < 26; i++) {
        int max = -1, pos = -1;

        for (int j = 0; j < 26; j++)
            if (!used[j] && freq[j] > max) {
                max = freq[j];
                pos = j;
            }

        order[i] = 'A' + pos;
        used[pos] = 1;
    }

    for (int i = 0; i < 26; i++)
        map[order[i] - 'A'] = english[i];

    int i;
    for (i = 0; text[i]; i++) {
        if (isalpha((unsigned char)text[i])) {
            char ch = map[toupper((unsigned char)text[i]) - 'A'];
            result[i] = islower((unsigned char)text[i])
                        ? tolower((unsigned char)ch) : ch;
        } else {
            result[i] = text[i];
        }
    }

    result[i] = '\0';

    printf("Possible plaintext:\n%s", result);
    printf("\nNote: Frequency analysis gives an estimate.\n");

    return 0;
}