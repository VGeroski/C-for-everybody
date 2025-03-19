/*
*
* Command         Action

* = 1.23          Sets the accumulator to 1.23
* + 5.0           Adds 5.0 to the accumulator
* / 2.0           Divides accumulator by 2.0
* * 6.3           Multiplies the accumulator by 6.3
* - 4.0           Subtracts 4.0 from the accumulator
* S 0.0           Stops the program
*/

#include <stdio.h>

int main()
{
    char line[256];
    char opcode;
    float value, display = 0.0;

    while (fgets(line, 256, stdin) != NULL) {
        sscanf(line, "%c %f", &opcode, &value);
        if (opcode == 'S') break;

        switch (opcode) {
            case '=':
                display = value;
                break;
            case '+':
                display += value;
                break;
            case '-':
                display -= value;
                break;
            case '*':
                display *= value;
                break;
            case '/':
                display /= value;
                break;
        }

        printf("Display: %.2f\n", display);
    }
}