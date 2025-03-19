#include <stdio.h>

/* convert c to lower case; ASCII only */
int lower(int c) {
    return c >= 'A' && c <= 'Z' ? c + 'a' - 'A' : c;
}

int main() {
    int lower();
    printf("Lower M is %c\n", lower('M'));
    printf("Lower x is %c\n", lower('x'));
    printf("Lower @ is %c\n", lower('@'));
    printf("Lower g is %c\n", lower('g'));
}

