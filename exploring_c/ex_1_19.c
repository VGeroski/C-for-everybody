/**
 * Write function to reverse string
 */

#include <stdio.h>

char *copy(char s1[], char s2[]);
void reverse(char t[]);

int main() {
    char t[1000];

    copy("Hello world", t);
    printf("%s\n", t);
    reverse(t);
    printf("%s\n", t);
    reverse(copy("XY", t));
    printf("%s\n", t);
    reverse(copy("Even", t));
    printf("%s\n", t);
    reverse(copy("Odd", t));
    printf("%s\n", t);
    reverse(copy("civic", t));
    printf("%s\n", t);
}

/* copy s1 to s2; assume s2 big enough */
char *copy(char s1[], char s2[])
{
    for(int i = 0;(s2[i] = s1[i]);i++)
        ;
    return s2;
}

void reverse(char t[]) {
    /* find last index of string */
    int j;
    for (j = 0; t[j] != '\0'; j++)
        ;
    const int len = j--;

    for (int i = 0; i < len / 2; i++, j--) {
        const char temp = t[i];
        t[i] = t[j];
        t[j] = temp;
    }
}