#include <stdio.h>
#include <ctype.h>

#define SIZE 10

/* getint: get next integer from input into *pn */
int getint(int *pn) {
    int c;

    /* skip white space */
    while (isspace(c = getchar()))
        ;

    const int sign = c == '-' ? -1 : 1;
    if (c == '+' || c == '-')
        c = getchar();

    for (*pn = 0; isdigit(c); c = getchar())
        *pn = 10 * *pn + (c - '0');


    *pn *= sign;
    return c;
}

int main() {
    int n, array[SIZE];

    for (n = 0; n < SIZE && getint(&array[n]) != EOF; n++)
        ;

    for (int i = 0; i < n; i++)
        printf("%d ", array[i]);
}