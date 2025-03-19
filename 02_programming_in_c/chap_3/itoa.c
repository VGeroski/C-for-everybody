#include <stdio.h>
#include <string.h>

void itoa(int n, char s[]);

int main() {
    char s[1000];

    itoa(42, s);
    printf("42 as characters %s\n", s);
}

void reverse(char t[]) {
    int i, j, len;
    char tmp;
    len = strlen(t);
    for (i = 0, j = len - 1;; i++, j--) {
        if (j < i) break;
        tmp = t[i];
        t[i] = t[j];
        t[j] = tmp;
    }
}

/* itoa: convert n to characters in s */
void itoa(int n, char s[]) {
    int i = 0, sign;

    if ((sign = n) < 0) /* record sign */
        n = -n;         /* make n positive */

    do {
        s[i++] = n % 10 + '0';
    } while ((n /= 10) > 0);

    if (sign < 0) s[i++] = '-';
    s[i] = '\0';
    reverse(s);
}