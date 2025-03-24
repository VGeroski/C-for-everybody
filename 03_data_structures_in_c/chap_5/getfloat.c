#include <stdio.h>
#include <ctype.h>

#define SIZE 10

/* getfloat: get next float from input into *pn */
int getfloat(double *pn) {
    int c;

    /* skip white space */
    while (isspace(c = getchar()))
        ;

    const int sign = c == '-' ? -1 : 1;
    if (c == '+' || c == '-')
        c = getchar();

    for (*pn = 0; isdigit(c); c = getchar())
        *pn = 10 * *pn + (c - '0');

    if (c == '.') c = getchar();

    double power;
    for (power = 1.0; isdigit(c); c = getchar()) {
      *pn = *pn * 10 + (c - '0');
      power *= 10;
    }

    *pn *= sign / power;
    return c;
}

int main() {
    double array[SIZE];

    for (int n = 0; n < SIZE && getfloat(&array[n]) != EOF; n++)
        ;

    for (int i = 0; i < SIZE; i++)
        printf("%g ", array[i]);
}