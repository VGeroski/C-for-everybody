#include <stdio.h>
#include <string.h>

int main() {
    char line[1000];
    char keep[1000];
    int first = 1;

    while(fgets(line, 1000, stdin) != NULL ) {
        if (first || strcmp(keep, line) != 0) {
            printf("%s\n",line);
            first = 0;
        }
        strcpy(keep, line);
    }
}