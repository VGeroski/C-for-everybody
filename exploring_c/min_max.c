#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 1000
#define TRUE 1

int main() {
    int first = 1;
    char input[MAXLINE];
    int val, maxval, minval;

    while (TRUE) {
        scanf("%s", input);
        if (strcmp(input, "done") == 0) break;

        val = atoi(input);
        if (first || val > maxval) maxval = val;
        if (first || val < minval) minval = val;
        first = 0;
    }

    printf("Maximum %d\n", maxval);
    printf("Minimum %d\n", minval);
}