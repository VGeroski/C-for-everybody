#include <stdio.h>

/* swap: interchange *px and *py */
void swap(int *px, int *py) {
    const int temp = *px;
    *px = *py;
    *py = temp;
}

int main() {
    int a = 10;
    int b = 20;

    printf("before swap (a, b): %d %d\n", a, b);
    swap(&a, &b);
    printf("after swap (a, b): %d %d\n", a, b);

    return 0;
}