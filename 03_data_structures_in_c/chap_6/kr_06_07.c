#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 1000

/* list node */
struct lnode
{
    char *text;
    struct lnode *next;
};

int main()
{
    /* head, tail and current pointer in list */
    struct lnode *head = NULL;
    struct lnode *tail = NULL;
    struct lnode *curr = NULL;

    char line[MAXLINE];

    /* open file */
    FILE *fptr = fopen("romeo.txt", "r");

    while (fgets(line, MAXLINE, fptr))
    {
        /* save line in list */
        char *save = (char *)malloc(strlen(line) + 1);
        strcpy(save, line);

        struct lnode *new = (struct lnode *)malloc(sizeof(struct lnode));

        if (tail != NULL)
            tail->next = new;
        new->text = save;
        new->next = NULL;
        tail = new;

        /* handle empty list */
        if (head == NULL)
            head = new;
    }

    for (curr = head; curr; curr = curr->next)
        printf("%s", curr->text);

    fclose(fptr);
    return 0;
}