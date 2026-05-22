# C for Everybody

## Objekti
Objektno Orijentisani principi
 - Enkapsulacija – Spajanje koda I podataka zajedno
 - Apstrakcija – Odvajanje interfejsa od implementacije
 - Nasledjivanje – Kreiranje druge klase tako sto cemo da nasledimo vec postojacu (DRY)
 - Polimorfizam – Razlicitno ponasanje objekta zavisno od implementacije

## Mape
Mape su zajednicki termin koji se koristi da opise apstraktni kljuc / vrednost kolekciju (C++ mape, Python dictionary, Java Map, PHP Arrays)
Iterator pattern je apstrakcija koja sluzi da se krecemo kroz vise implementacija.

Klijentski kod za testiranje Map klase:
```c
int main()
{
    struct MapEntry *cur;
    struct Map * map = Map_new();

    printf("Testing Map class\n");
    map->put(map, "z", 8);
    map->put(map, "z", 1);
    map->put(map, "y", 2);
    map->put(map, "b", 3);
    map->put(map, "a", 4);
    map->dump(map);

    printf("z=%d\n", map->get(map, "z", 42));
    printf("x=%d\n", map->get(map, "x", 42));

    map->del(map);
}
```
### Struktura MapEntry i Map

Struktura `MapEntry` - struktura koja ce da cini cvorove u listi. Kljuc `key` je string, a pravi podaci ce naknadno da se cuvaju u novo alociranom prostoru. `value` je int tako da ce biti odmah alociran u cvoru.
```c
struct MapEntry 
{
    char *key;  /* public */
    int value;  /* public */
    struct MapEntry *__prev;
    struct MapEntry *__next;
};
```
Struktura `Map` sadrzi atribute i metode. Ovde se koriste pokazivaci na funkcije kako bismo mogli kasnije preko Map objekta da pristupimo metodama. Ovo je enkapsulacija.
```c
struct Map 
{
   /* Private attributes */
   struct MapEntry *__head;
   struct MapEntry *__tail;
   int __count;

   /* Public methods */
   void (*put)(struct Map* self, char *key, int value);
   int (*get)(struct Map* self, char *key, int def);
   int (*size)(struct Map* self);
   void (*dump)(struct Map* self);
   void (*del)(struct Map* self);
};

```
### Konstruktor

Kreiramo objekat preko konstruktora, alociramo potrebnu memoriju.
```c
struct Map * Map_new() 
{
    struct Map *p = malloc(sizeof(*p));

    p->__head = NULL;
    p->__tail = NULL;
    p->__count = 0;

    p->put = &__Map_put;
    p->get = &__Map_get;
    p->size = &__Map_size;
    p->dump = &__Map_dump;
    p->del = &__Map_del;
    return p;
}
```
### toString - pomocni debuger

Pre nego sto krenemo da implementiramo druge metode, pravimo nas mali debuger. Ovo je samo pomocna funkcija kojom stampamo unutrasnja stanja klase (nesto slicno kao toString u Javi)
```c
void __Map_dump(struct Map* self)
{
    struct MapEntry *cur;
    printf("Object Map count=%d\n", self->count);
    for(cur = self->__head; cur != NULL ; cur = cur->__next)
         printf("  %s=%d\n", cur->key, cur->value);
}
```
### Destruktor

Obzirom da smo memoriju zauzimali dinamicki, nas zadatak je i da sve ocistimo i vratimo memoriju nakon unistenja objekta.
Takodje oslobadjamo i memoriju za `key`. Napomena: Kada se obrise objekat, ne mozemo mu vise pristupiti, zato uvek pamtimo sledeci pre brisanja trenutnog.
```c
void __Map_del(struct Map* self)
{
    struct MapEntry *cur, *next;
    cur = self->__head;
    while(cur) 
    {
        free(cur->key);
        next = cur->__next;
        free(cur);
        cur = next;
    }
    free((void *)self);
}
```
### Dohvatanje i postavljanje vrednosti

Dohvatanje vrednosti za dati kljuc. Koristimo pomocnu funkciju `find` koja ce zapravo da nam vrati pokazivac na trazeni element.
```c
int __Map_get(struct Map* self, char *key, int def)
{
    struct MapEntry *retval = __Map_find(self, key);
    if ( retval == NULL ) return def;
    return retval->value;
}
```

Postavljenje vrednosti u mapu. Koristimo opet pomocnu funkciju `find`, ali da proverimo da li je kljuc vec u mapi. Ako jeste samo cemo da azuriramo vrednost.
```c
void __Map_put(struct Map *self, char *key, int value)
{
    struct MapEntry *old = __Map_find(self, key);
    if (old != NULL)
    {
        old->value = value;
        return;
    }

    struct MapEntry *new = malloc(sizeof(*new));
    if (new == NULL)
        error("malloc");

    new->key = malloc(strlen(key) + 1);
    if (new->key == NULL)
    {
        free(new);
        error("malloc");
    }
    strcpy(new->key, key);
    new->value = value;
    new->__next = NULL;

    if (self->__head == NULL)
        self->__head = new;
    else
        self->__tail->__next = new;
    self->__tail = new;
    
    self->__count++;
}
```
![dodavanje-prazna-mapa](/img/dodavanje_prazna_mapa.jpg)
![dodavanje-mapa](/img/dodavanje_mapa.jpg)

## Iteratori
Prolazimo kroz elemente kolekcije, postujuci granice apstrakcije.
Kada dodamo iterator, klijentski za testiranje izgleda:
```c
int main()
{
    struct Map *map = Map_new();
    struct MapEntry *cur;
    struct MapIter *iter;

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
}
```

Radi lakseg pracenja stanje po memoriji, prihvatamo prostiji model u memoriji:
![uproscen-prikaz](/img/uproscavanje_slike.jpg)