/**
 * Emulating Python Strings
 */

#include <stdio.h>
#include <stdlib.h>

struct pystr
{
    int length;
    int alloc; /* length of the *data */
    char *data;
};

/* Constructor, like in py x = str() */
struct pystr *pystr_new()
{
    struct pystr *p = malloc(sizeof(*p));
    p->length = 0;
    p->alloc = 10;
    p->data = malloc(10);
    p->data[0] = '\0';

    return p;
}

/* Destructor */
void pystr_del(const struct pystr *self)
{
    free((void *)self->data);
    free((void *)self);
}

void pystr_dump(const struct pystr *self)
{
    printf("Pystr length=%d alloc=%d data=%s\n", self->length, self->alloc, self->data);
}

int pystr_len(const struct pystr *self)
{
    return self->length;
}

char *pystr_str(const struct pystr *self)
{
    return self->data;
}

void pystr_append(struct pystr *self, char ch)
{
    if (self->length >= (self->alloc - 2))
    {
        self->alloc = self->alloc + 10;
        self->data = (char *)realloc(self->data, self->alloc);
    }

    self->data[self->length] = ch;
    self->length++;
    self->data[self->length] = '\0';
}

void pystr_appends(struct pystr *self, char *str)
{
    for (char *c = str; *c != '\0'; c++)
        pystr_append(self, *c);
}

void pystr_assign(struct pystr *self, char *str)
{
    self->length = 0;
    free(self->data);
    pystr_appends(self, str);
}

int main()
{
    printf("Testing pystr class\n");
    struct pystr *x = pystr_new();
    pystr_dump(x);

    pystr_append(x, 'H');
    pystr_dump(x);

    pystr_appends(x, "ello world");
    pystr_dump(x);

    pystr_assign(x, "A completly new string");
    printf("String = %s\n", pystr_str(x));
    printf("length = %d\n", pystr_len(x));

    pystr_del(x);

    return 0;
}