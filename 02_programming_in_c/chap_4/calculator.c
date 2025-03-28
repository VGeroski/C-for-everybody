#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFSIZE 100
#define MAXVAL 100 /* maximum depth of val stack */
#define MAXOP 100
#define NUMBER '0' /* signal that a number was found */

int sp = 0;         /* next free stack position */
double val[MAXVAL]; /* value stack */

int bufp = 0;
char buf[BUFSIZE];

int getch() {
    return bufp > 0 ? buf[--bufp] : getchar();
}

void ungetch(int c) {
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    buf[bufp++] = c;
}

/* getop: get next character or numeric operand */
int getop(char s[]) {
    int i, c;

    while ((s[0] = c = getch()) == ' ' || c == '\t')
        ;
    s[1] = '\0';

    /* not a number */
    if (!isdigit(c) && c != '.') return c;

    i = 0;
    /* collect integer part */
    if (isdigit(c))
        while (isdigit(s[++i] = c = getch()))
            ;

    /* collect fraction part */
    if (c == '.')
        while (isdigit(s[++i] = c = getch()))
            ;
    s[i] = '\0';

    if (c != EOF) ungetch(c);

    return NUMBER;
}

/* push: push f onto value stack */
void push(double f) {
    if (sp < MAXVAL)
        val[sp++] = f;
    else
        printf("error: stack full, can't push %g\n", f);
}

/* pop: pop and return top value from stack */
double pop() {
    if (sp > 0)
        return val[--sp];

    printf("error: stack empty\n");
    return 0.0;
}

/* reverse Polish calculator */
int main() {
    int type;
    double op2;
    char s[MAXOP];

    /* while there is operator or operand - do */
    while ((type = getop(s)) != EOF) {

        switch (type) {
            /* in case of number push number on stack */
            case NUMBER:
                push(atof(s));
                break;
            /* in case of operator remove operands from stack
             * do the operation and push back result on stack */
            case '+':
                push(pop() + pop());
                break;
            case '*':
                push(pop() * pop());
                break;
            case '-':
                op2 = pop();
                push(pop() - op2);
                break;
            case '/':
                op2 = pop();
                if (op2 != 0.0)
                    push(pop() / op2);
                else
                    printf("error: division by zero\n");
                break;
            /* in case of new line - remove from stack and present value */
            case '\n':
                printf("%.8g\n", pop());
                break;
            default:
                printf("error: unknown command %s\n", s);
                break;
        }
    }
    return 0;
}
