/*
 * Copy input to output.
 *
 * read one character
 * while (character is not indicator for end of file)
 *     print character that is read
 *     now read one more character
 */

#include <stdio.h>

int main() {
    int c;

    while ((c = getchar()) != EOF) {
        putchar(c);
    }
}
