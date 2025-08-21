/* Exercise RS-11: Write a C function called py_rstrip() that removes spaces
 * from the end of a string. This function modifies its parameter and should
 * never be called with a constant value. */

#include <stdio.h>
#include <string.h>

void py_rstrip(char inp[])
{
    int len = strlen(inp);
    if (len == 0)
        return;

    int i = len - 1;
    while (i >= 0 && inp[i] == ' ')
        i--;

    inp[i + 1] = '\0';
}

void py_lstrip(char inp[])
{
    int p = 0;
    int n = strlen(inp);
    while (inp[p] == ' ' && p < n)
        p++;

    /* no leading whitespace */
    if (p == 0) return;
    
    for (int i = 0; i <= n - p; i++)
        inp[i] = inp[i + p];
}

int main()
{
    char s1[] = "   Hello   World    ";
    void py_rstrip();
    py_rstrip(s1);
    printf("-%s-\n", s1);

    char s2[] = "   Hello   World    ";
    void py_lstrip();
    py_lstrip(s2);
    printf("-%s-\n", s2);
}