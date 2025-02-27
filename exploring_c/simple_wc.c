/*
 * Count lines, words and characters in input.
 * Simple UNIX wc program
 */

#include <stdio.h>

/* markers for in/out word */
const int IN = 1;  /* inside word */
const int OUT = 0; /* outside word */

int main() {
    int c, nc, nw, nl;

    int state = OUT;
    nc = nl = nw = 0;

    while ((c = getchar()) != EOF) {
        ++nc; /* count characters */

        /* count new lines */
        if (c == '\n')
            ++nl;

        /* change marker for outside of word */
        if (c == ' ' || c == '\n' || c == '\t')
            state = OUT;
        else if (state == OUT) {
            state = IN; /* indicator that we are in word */
            ++nw;       /* update word count */
        }
    }

    printf("%d %d %d\n", nl, nw, nc);
}