#include <stdio.h>
/* maximum input line length */
#define MAXLINE 1000

int get_line(char line[], int max);

int strindex(const char source[], const char searchfor[]);

/* pattern to search for */
char pattern[] = "ould";

int main() {
    char line[MAXLINE];
    int found = 0;

    /* check for another line */
    while (get_line(line, MAXLINE) > 0) {
        /* check if line contains pattern for search */
        if (strindex(line, pattern) >= 0) {
            /* we want to present only line that has pattern */
            printf("%s\n", line);
            found++;
        }
    }
}

/* get_line: get line into line[], return length */
int get_line(char line[], int max) {
    int i = 0, c;

    /* read characters until we hit limit or new line char */
    while (--max > 0 && (c = getchar()) != EOF && c != '\n')
        line[i++] = c;

    if (c == '\n') line[i++] = c;

    line[i] = '\0';
    return i;
}

/* strindex: return index of searchfor array in source, -1 if none */
int strindex(const char source[], const char searchfor[]) {
    int i, j, k;
    /* iterate over each character */
    /* this outer index will remember start position of pattern if there is a hit */
    for (i = 0; source[i] != '\0'; i++) {
        for (j = i, k = 0; searchfor[k] != '\0' && source[j] == searchfor[k]; j++, k++);
        if (k > 0 && searchfor[k] == '\0')
            return i;
    }

    return -1;
}
