#include <stdio.h>
#include <math.h>

int main() {
    double log2_keys = 0;

    for (int i = 1; i <= 25; i++) {
        log2_keys += log((double)i) / log(2.0);
    }

    printf("Total possible keys: 25!\n");
    printf("Approximate key space: 2^%.2f\n", log2_keys);

    return 0;
}