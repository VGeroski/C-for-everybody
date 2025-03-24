#include <stdio.h>

/* strlen: return length of string s */
int strlen(char *s) {
    int n;
    for (n = 0; *s != '\0'; s++, n++)
        ;

    return n;
}

int main() {
    char array[] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
    char *ptr = "demo string for testing";
    printf("%d\n", strlen("hello world"));
    printf("%d\n", strlen(array));
    printf("%d\n", strlen(ptr));

    return 0;
}