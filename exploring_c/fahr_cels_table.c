/*
 * print Fahrenheit-Celsius table
 */

#include <stdio.h>

int main() {
    const float lower = 0;   /* lower limit of temp scale */
    const float upper = 300; /* upper limit */
    const float step = 20;   /* step size */

    float fahr = lower;
    printf("Fahrenheit\t Celsius\n");
    while (fahr <= upper) {
        float celsius = 5.0f/9.0f * (fahr - 32);
        printf("%3.0f \t\t %6.1f\n", celsius, fahr);
        fahr = fahr + step;
    }
}
