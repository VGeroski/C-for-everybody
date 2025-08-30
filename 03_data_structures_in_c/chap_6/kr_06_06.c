#include <stdio.h>
#include <stdlib.h>

int main()
{
    struct point
    {
        double x;
        double y;
    };

    struct point *pp;

    pp = (struct point *)malloc(sizeof(struct point));

    pp->x = 3.0;
    pp->y = 4.0;

    printf("(%f, %f)\n", pp->x, pp->y);

    free(pp);
    return 0;
}