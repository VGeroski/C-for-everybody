#include <stdio.h>

/*binsearch: find x in v[0] <= v[1] <= ... <= v[n-1] */
int binsearch(int x, int v[], int n) {
    int low, high, mid;

    low = 0;
    high = n - 1;
    while (low <= high) {
        mid = (low + high) / 2;
        if (x < v[mid])
            high = mid - 1;
        else if (x > v[mid])
            low = mid + 1;
        /* found match */
        else
            return mid;
    }

    /* no match */
    return -1;
}

int main() {
    int v[] = {7, 10, 15, 20, 65, 100};
    printf("Searching for position of element 20: %d", binsearch(20, v, sizeof(v) / sizeof(v[0])));
}