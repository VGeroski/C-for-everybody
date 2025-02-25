#include <stdio.h>

int main() {
    char line[1000];
    FILE *handle;
    /* with file handle we will open file for reading */
    handle = fopen("romeo.txt", "r");

    /* read line by line, place it in buffer and print out on console */
    while (fgets(line, 1000, handle) != NULL) {
        printf("%s", line);
    }

    return 0;
}