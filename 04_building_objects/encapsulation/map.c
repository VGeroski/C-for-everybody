#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct MapEntry
{
    char *key;
    int value;
    /* private: */
    struct MapEntry *__next;
};

struct Map
{
    /* private: */
    struct MapEntry *__head;
    struct MapEntry *__tail;
    int __count;

    /* public methods: */
    void (*put)(struct Map *self, char *key, int value);
    int (*get)(struct Map *self, char *key, int def);
    int (*size)(struct Map *self);
    void (*dump)(struct Map *self);
    void (*del)(struct Map *self);
};

void error(const char *message)
{
    perror(message);
    exit(EXIT_FAILURE);
}

/**
 * map->dump - In effect a toString() except we print
 * the contents of the Map to stdout
 *
 * self - The pointer to the instance of this class
 */
void __Map_dump(struct Map *self)
{
    struct MapEntry *cur;
    printf("Object Map count = %d\n", self->__count);
    for (cur = self->__head; cur; cur = cur->__next)
        printf("    %s = %d\n", cur->key, cur->value);
}

/**
 * Descrutor for the Map Class
 *
 * Loops through and frees all the keys and
 * entries in the map. The values are integers
 * so there is no need to free them
 */
void __Map_del(struct Map *self)
{
    struct MapEntry *cur, *next;
    cur = self->__head;
    while (cur)
    {
        free(cur->key);
        next = cur->__next;
        free(cur);
        cur = next;
    }
    free((void *)self);
}

int __Map_size(struct Map *self) { return self->__count; }

/* Helper method to find particular node with given key */
struct MapEntry *__Map_find(struct Map *self, char *key)
{
    struct MapEntry *cur = self->__head;
    while (cur)
    {
        if (strcmp(cur->key, key) == 0)
            return cur;
        cur = cur->__next;
    }

    return NULL;
}

/**
 * map->get - Locate and return the value for the
 * corresponding key or a default value
 *
 * self - The pointer to the instance of the class
 * key - A character pointer to the key value
 * def - A default value to return if the ket is not in the Map
 */
int __Map_get(struct Map *self, char *key, int def)
{
    struct MapEntry *retval = __Map_find(self, key);
    if (retval == NULL)
        return def;
    return retval->value;
}

/**
 * map->put - Add or update an entry in the Map
 *
 * self - The pointer to the instance of the class
 * key - A character pointer to the key value
 * value - The value to be stored with associated key
 *
 * If the key is not in the Map, an entry is added.
 * If there is already an entry in the Map for the key,
 * the value is updated.
 */
void __Map_put(struct Map *self, char *key, int value)
{
    struct MapEntry *old = __Map_find(self, key);
    if (old != NULL)
        old->value = value;
    else
    {
        struct MapEntry *new = malloc(sizeof(*new));
        new->key = malloc(strlen(key) + 1);
        if (new == NULL || new->key == NULL)
            error("malloc");
        strcpy(new->key, key);
        new->value = value;
        new->__next = NULL;

        if (self->__head == NULL)
            self->__head = self->__tail = new;
        else
        {
            self->__tail->__next = new;
            self->__tail = new;
        }

        self->__count++;
    }
}

struct Map *Map_new()
{
    struct Map *p = malloc(sizeof(*p));
    if (p == NULL)
        error("malloc");

    p->__head = p->__tail = NULL;
    p->__count = 0;

    p->put = &__Map_put;
    p->get = &__Map_get;
    p->size = &__Map_size;
    p->dump = &__Map_dump;
    p->del = &__Map_del;

    return p;
}

int main()
{
    struct Map *map = Map_new();

    printf("Testing Map class:\n");
    map->put(map, "z", 8);
    map->put(map, "z", 1);
    map->put(map, "y", 2);
    map->put(map, "b", 3);
    map->put(map, "a", 4);
    map->dump(map);

    printf("z = %d\n", map->get(map, "z", 42));
    printf("x = %d\n", map->get(map, "x", 42));

    map->del(map);

    return 0;
}