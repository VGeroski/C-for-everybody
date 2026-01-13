#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct dnode
{
    char *key;
    char *value;
    struct dnode *next;
};

struct pydict
{
    struct dnode *head;
    struct dnode *tail;
    int count;
};

/* Constructor - dct = dict() */
struct pydict *pydict_new()
{
    struct pydict *p = malloc(sizeof(*p));
    p->head = p->tail = NULL;
    p->count = 0;

    return p;
}

/* Descrutor - del(dct) */
void pydict_del(struct pydict *self)
{
    struct dnode *cur, *next;

    cur = self->head;
    while (cur)
    {
        free(cur->key);
        free(cur->value);
        next = cur->next;
        free(cur);
        cur = next;
    }
    free((void *)self);
}

/* print(lst) */
void pydict_print(struct pydict *self)
{
    struct dnode *cur = self->head;

    printf("{");
    while (cur)
    {
        printf("'%s': '%s'", cur->key, cur->value);
        if (cur->next)
            printf(", ");

        cur = cur->next;
    }
    printf("}\n");
}

/* len(dct) */
int pydict_len(const struct pydict *self)
{
    return self->count;
}

struct dnode *pydict_find(struct pydict *self, char *key)
{
    struct dnode *cur = self->head;
    while (cur)
    {
        if (strcmp(cur->key, key) == 0)
            return cur;
        cur = cur->next;
    }

    return NULL;
}

/* x.get(key) - Returns NULL if not found */
char *pydict_get(struct pydict *self, char *key)
{
    struct dnode *entry = pydict_find(self, key);
    if (entry != NULL)
        return entry->value;

    return NULL;
}

/* x[key] = value; Insert or replace the value associated with a key */
struct pydict *pydict_put(struct pydict *self, char *key, char *value)
{
    struct dnode *old = pydict_find(self, key);
    if (old != NULL)
    {
        /* maybe we need to reallocate! */
        int new_value_len = strlen(value) + 1;
        char *tmp = realloc(old->value, new_value_len);
        if (!tmp)
        {
            perror("realloc");
            exit(EXIT_FAILURE);
        }
        old->value = tmp;
        strcpy(old->value, value);
    }
    else
    {
        struct dnode *new = malloc(sizeof(*new));
        int key_len = strlen(key) + 1;
        new->key = malloc(key_len);
        strcpy(new->key, key);

        int value_len = strlen(value) + 1;
        new->value = malloc(value_len);
        strcpy(new->value, value);

        new->next = NULL;

        if (self->head == NULL)
            self->head = self->tail = new;
        else
        {
            self->tail->next = new;
            self->tail = new;
        }

        self->count++;
    }

    return self;
}

int main()
{
    struct pydict *dct = pydict_new();

    pydict_put(dct, "z", "Catch phrase");
    pydict_print(dct);

    pydict_put(dct, "z", "W");
    pydict_print(dct);

    pydict_put(dct, "y", "B");
    pydict_print(dct);

    pydict_put(dct, "y", "Hello");
    pydict_print(dct);

    pydict_put(dct, "c", "D");
    pydict_print(dct);

    printf("Length = %d\n", pydict_len(dct));

    printf("z = %s\n", pydict_get(dct, "z"));
    printf("x = %s\n", pydict_get(dct, "x"));

    printf("\nDump\n");
    for (struct dnode *cur = dct->head; cur != NULL; cur = cur->next)
        printf("%s = %s\n", cur->key, cur->value);

    pydict_del(dct);
}