#include <stdio.h>

int htoi(char s[]);

int main() {
    int htoi();
    printf("htoi('9dafc') = %d\n", htoi("9dafc"));
    printf("htoi('f') = %d\n", htoi("f"));
    printf("htoi('F0') = %d\n", htoi("F0"));
    printf("htoi('12fab') = %d\n", htoi("12fab"));
}

int htoi(char s[]) {
    int hexdigit, i, isvalidhex, n;

    i = 0;
    /* skip optional 0x or 0X */
    if (s[i] == '0') {
        ++i;
        if (s[i] == 'x' || s[i] == 'X')
            ++i;
    }

    n = 0;
    /* assume that is valid hexadecimal digit */
    isvalidhex = 1;
    while (isvalidhex) {
        if (s[i] >= '0' && s[i] <= '9')
            hexdigit = s[i] - '0';
        else if (s[i] >= 'a' && s[i] <= 'f')
            hexdigit = s[i] - 'a' + 10;
        else if (s[i] >= 'A' && s[i] <= 'F')
            hexdigit = s[i] - 'A' + 10;
        else
            isvalidhex = 0; /* if code reach here, it is not valid hex digit */

        if (isvalidhex)
            n = 16 * n + hexdigit;

        i++;
    }

    return n;
}