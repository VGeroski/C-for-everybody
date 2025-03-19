#include <ctype.h>
#include <stdio.h>

/* atoi: convert s to integer */
int atoi(const char s[]) {
    int i, n;

    /* skip white space */
    for (i = 0; isspace(s[i]); i++)
        ;

    /* determine sign */
    const int sign = s[i] == '-' ? -1 : 1;

    /* skip sign */
    if (s[i] == '+' || s[i] == '-') i++;

    for (n = 0; isdigit(s[i]); i++)
        n = 10 * n + (s[i] - '0');

    return sign * n;
}

int main() {
    const char s[] = "123";
    const int n = atoi(s);

    printf("%d\n", n);
}