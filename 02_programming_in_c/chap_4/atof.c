#include <ctype.h>
#include <stdio.h>

#define MAXLINE 100

/* atof: convert string s to double */
double atof(const char s[]) {
    double val, power;
    int i;

    for (i = 0; isspace(s[i]); i++)
        ;

    const int sign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '+' || s[i] == '-')
        i++;

    for (val = 0.0; isdigit(s[i]); i++)
        val = 10.0 * val + (s[i] - '0');

    if (s[i] == '.')
        i++;

    for (power = 1.0; isdigit(s[i]); i++) {
        val = 10.0 * val + (s[i] - '0');
        power *= 10;
    }

    return sign * val / power;

}

/* simple calculator */
int main() {
    char s[MAXLINE];

    double sum = 0;
    while (fgets(s, MAXLINE, stdin))
        printf("\t%g\n", sum += atof(s));

    return 0;
}
