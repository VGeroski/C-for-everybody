#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct lnode
{
    char *text;
    struct lnode *next;
};

struct pylist
{
    struct lnode *head;
    struct lnode *tail;
    int count;
};

/* Constructor - lst = list() */
struct pylist *pylist_new()
{
    struct pylist *new = malloc(sizeof(*new));
    new->head = NULL;
    new->tail = NULL;
    new->count = 0;

    return new;
}

/* Descrutor - del(lst) */
void pylist_del(struct pylist *self)
{
    struct lnode *curr, *next;
    curr = self->head;
    while (curr)
    {
        free(curr->text);
        next = curr->next;
        free(curr);
        curr = next;
    }

    free((void *)self);
}

/* print(lst) */
void pylist_print(struct pylist *self)
{
    printf("[");
    struct lnode *curr = self->head;

    while (curr)
    {
        printf("'%s'", curr->text);
        if (curr->next == NULL)
            printf("]\n");
        else
            printf(", ");

        curr = curr->next;
    }
}

/* len(lst) */
int pylist_len(const struct pylist *self)
{
    return self->count;
}

/* lst.append("Hello World") */
void pylist_append(struct pylist *self, char *str)
{
    struct lnode *new = malloc(sizeof(*new));
    new->next = NULL;

    size_t len = strlen(str) + 1;
    new->text = malloc(len);
    strcpy(new->text, str);

    if (self->head == NULL)
    {
        self->head = self->tail = new;
    }
    else
    {
        self->tail->next = new;
        self->tail = new;
    }

    self->count++;
}

int compare_strings(const char *s1, const char *s2)
{
    while (*s1 != '\0' && *s2 != '\0' && *s1 == *s2)
    {
        s1++;
        s2++;
    }

    return *s1 - *s2;
}

/* lst.index("Hello World") - if not found -1 */
int pylist_index(struct pylist *self, char *str)
{
    if (self->head == NULL)
        return -1;

    struct lnode *curr = self->head;
    int index = 0;
    while (curr)
    {
        if (strcmp(curr->text, str) == 0)
            return index;

        index++;
        curr = curr->next;
    }

    return -1;
}

int main()
{
    struct pylist *lst = pylist_new();

    pylist_append(lst, "Hello World");
    pylist_print(lst);

    pylist_append(lst, "Catch phrase");
    pylist_print(lst);

    pylist_append(lst, "Brian");
    pylist_print(lst);

    printf("Length = %d\n", pylist_len(lst));          /* 3 */
    printf("Brian? %d\n", pylist_index(lst, "Brian")); /* 2 */
    printf("Bob? %d\n", pylist_index(lst, "Bob"));     /* -1 */

    pylist_del(lst);

    return 0;
}