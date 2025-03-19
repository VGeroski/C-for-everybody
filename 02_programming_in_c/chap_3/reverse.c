#include <stdio.h>
#include <string.h>

/* reverse: reverse string s in place */
void reverse(char s[]) {
    int i, j;
    char c;
    for (i = 0, j = strlen(s) - 1; i < j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

int main() {
    char s[] = "demo string";
    reverse(s);
    printf("%s\n", s);
}