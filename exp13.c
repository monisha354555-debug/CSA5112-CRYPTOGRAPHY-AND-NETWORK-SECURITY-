#include <stdio.h>

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
    int p00, p10, p01, p11;
    int c00, c10, c01, c11;

    printf("Enter plaintext pair 1 (two numbers): ");
    scanf("%d%d", &p00, &p10);

    printf("Enter plaintext pair 2 (two numbers): ");
    scanf("%d%d", &p01, &p11);

    printf("Enter ciphertext pair 1: ");
    scanf("%d%d", &c00, &c10);

    printf("Enter ciphertext pair 2: ");
    scanf("%d%d", &c01, &c11);

    int det = mod26(p00 * p11 - p01 * p10);
    int id = inverse(det);

    if (id == -1) {
        printf("Cannot recover key: matrix has no inverse.\n");
        return 0;
    }

    int a = mod26(id * p11);
    int b = mod26(-id * p01);
    int c = mod26(-id * p10);
    int d = mod26(id * p00);

    int k00 = mod26(c00 * a + c01 * c);
    int k01 = mod26(c00 * b + c01 * d);
    int k10 = mod26(c10 * a + c11 * c);
    int k11 = mod26(c10 * b + c11 * d);

    printf("Recovered key matrix:\n");
    printf("%d %d\n%d %d\n", k00, k01, k10, k11);

    return 0;
}