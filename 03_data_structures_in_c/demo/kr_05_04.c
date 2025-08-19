/* Buffer overflow:
 * ./a.out
 * Hello                        World
 * s: Hello                        World
 * *** stack smashing detected ***: terminated
 * Aborted (core dumped)
 */

#include <stdio.h>

int main()
{
    char s[15];

    /* unsafe function */
    gets(s);
    printf("s: %s\n", s);
}
