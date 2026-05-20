#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct HashMapEntry
{
    /* public: */
    char *key;
    int value;
    /* private: */
    struct HashMapEntry *__prev;
    struct HashMapEntry *__next;
};

struct HashMap
{
    int __buckets;
    struct HashMapEntry *__heads[8];
    struct HashMapEntry *__tails[8];
    int __count;

    /* public methods: */
    void (*put)(struct HashMap *self, char *key, int value);
    int (*get)(struct HashMap *self, char *key, int def);
    int (*size)(struct HashMap *self);
    void (*dump)(struct HashMap *self);
    struct HashMapIter *(*iter)(struct HashMap *self);
    void (*del)(struct HashMap *self);
};

struct HashMapIter
{
    int __bucket;
    struct HashMap *__map;
    struct HashMapEntry *__current;

    struct HashMapEntry *(*next)(struct HashMapIter *self);
    void (*del)(struct HashMapIter *self);
};

struct HashMapEntry *__HashMapIter_next(struct HashMapIter *self)
{
    struct HashMapEntry *retval;

    /* If we are at the end of a chain and there are still more buckets
     * scan for a bucket that is not NULL */
    while (self->__current == NULL)
    {
        self->__bucket++;
        if (self->__bucket >= self->__map->__buckets)
            return NULL;
        self->__current = self->__map->__heads[self->__bucket];
    }

    retval = self->__current;
    if (self->__current != NULL)
        self->__current = self->__current->__next;

    return retval;
}

void HashMapIter_del(struct HashMapIter *self)
{
    free((void *)self);
}

struct HashMapIter *__HashMap_iter(struct HashMap *map)
{
    struct HashMapIter *iter = malloc(sizeof(*iter));
    iter->__map = map;
    iter->__bucket = 0;
    iter->__current = map->__heads[iter->__bucket];

    iter->next = &__HashMapIter_next;
    iter->del = &HashMapIter_del;

    return iter;
}

int getBucket(char *str, int buckets)
{
    unsigned int hash = 123456;
    if (str == NULL)
        return 0;

    for (; *str; str++)
        hash = (hash << 3) ^ *str; // shift 3, and then xor

    return hash % buckets;
}

struct HashMapEntry *__HashMap_find(struct HashMap *self, char *key, int bucket)
{
    struct HashMapEntry *cur;
    if (self == NULL || key == NULL)
        return NULL;

    for (cur = self->__heads[bucket]; cur; cur = cur->__next)
        if (strcmp(key, cur->key) == 0)
            return cur;

    return NULL;
}

int __HashMap_get(struct HashMap *self, char *key, int def)
{
    int bucket = getBucket(key, self->__buckets);
    struct HashMapEntry *retval = __HashMap_find(self, key, bucket);
    if (retval == NULL)
        return def;

    return retval->value;
}

void __HashMap_put(struct HashMap *self, char *key, int value)
{
    if (self == NULL || key == NULL)
        return;

    int bucket = getBucket(key, self->__buckets);

    /* check if key already exists */
    struct HashMapEntry *existing = __HashMap_find(self, key, bucket);

    if (existing != NULL)
    {
        existing->value = value;
        return;
    }

    /* allocate new entry */
    struct HashMapEntry *entry = malloc(sizeof(*entry));

    /* allocate and copy key */
    entry->key = malloc(strlen(key) + 1);

    if (entry->key == NULL)
    {
        fprintf(stderr, "malloc failed\n");
        free(entry);
        return;
    }

    strcpy(entry->key, key);

    entry->value = value;

    /* initialize links */
    entry->__next = NULL;
    entry->__prev = NULL;

    /* insert into bucket */
    if (self->__heads[bucket] == NULL)
    {
        /* first node in bucket */
        self->__heads[bucket] = entry;
        self->__tails[bucket] = entry;
    }
    else
    {
        /* append to tail */
        entry->__prev = self->__tails[bucket];
        self->__tails[bucket]->__next = entry;
        self->__tails[bucket] = entry;
    }

    self->__count++;
}

int __HashMap_size(struct HashMap *self)
{
    return self->__count;
}

void __HashMap_dump(struct HashMap *self)
{
    struct HashMapEntry *cur;

    printf("Object HashMap@%p count = %d buckets = %d\n",
           self, self->__count, self->__buckets);

    for (int i = 0; i < self->__buckets; i++)
    {
        for (cur = self->__heads[i]; cur; cur = cur->__next)
            printf(" %s = %d [%d]\n", cur->key, cur->value, i);
    }
}

void __HashMap_del(struct HashMap *self)
{
    struct HashMapEntry *cur, *next;

    for (int i = 0; i < self->__buckets; i++)
    {
        cur = self->__heads[i];
        while (cur)
        {
            free(cur->key);
            next = cur->__next;
            free(cur);
            cur = next;
        }
    }
    free((void *)self);
}

struct HashMap *Map_new()
{
    struct HashMap *p = malloc(sizeof(*p));

    p->__buckets = 8;
    for (int i = 0; i < p->__buckets; i++)
    {
        p->__heads[i] = NULL;
        p->__tails[i] = NULL;
    }

    p->__count = 0;

    p->put = &__HashMap_put;
    p->get = &__HashMap_get;
    p->size = &__HashMap_size;
    p->dump = &__HashMap_dump;
    p->iter = &__HashMap_iter;
    p->del = &__HashMap_del;

    return p;
}

int main()
{
    struct HashMap *map = Map_new();
    struct HashMapEntry *cur;
    struct HashMapIter *iter;

    /* Make sure we see all output up to an error */
    setvbuf(stdout, NULL, _IONBF, 0);

    printf("Map test\n");
    map->put(map, "z", 8);
    map->put(map, "z", 1);
    map->put(map, "y", 2);
    map->put(map, "b", 3);
    map->put(map, "a", 4);
    map->dump(map);

    printf("size=%d\n", map->size(map));

    printf("z=%d\n", map->get(map, "z", 42));
    printf("x=%d\n", map->get(map, "x", 42));

    printf("\nIterate\n");
    iter = map->iter(map);
    while (1)
    {
        cur = iter->next(iter);
        if (cur == NULL)
            break;
        printf("%s=%d\n", cur->key, cur->value);
    }
    iter->del(iter);

    map->del(map);

    return 0;
}