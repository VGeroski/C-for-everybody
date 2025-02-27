/*
 * Count characters in input.
 */

#include <stdio.h>

int main() {
    int c, nc = 0;

    while ((c = getchar()) != EOF) {
        ++nc;
    }
    printf("Number of characters: %d\n", nc);
}
