#include <stdio.h>

int main () {
    int i;
    float val, sum;
    i = 0;
    sum = 0;
    while(i != 5) {
        scanf("%f", &val);
        sum += val;
        i++;
    }
    printf("The total is: %.1f\n", sum);
    printf("The average is: %.1f\n", sum / i);
}