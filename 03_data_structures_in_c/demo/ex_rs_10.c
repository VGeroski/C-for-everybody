/*
 * Write a C program to prompt for two strings and concatenate them
 * as shown in in the Python code below.
 * Use the functions strcpy and strcat from the string.h library in your code.
 * Pre-allocate your character arrays large enought to handle up to 100 characters
 * on input for each string (i.e. do not use malloc).
 *
 * python code:
 *   print('Enter two strings');
 *   first = input()
 *   second = input()
 *   print(first + " & " + second)
 */

#include <stdio.h>
#include <string.h>

int main()
{
    printf("Enter two strings\n");
    char first[100];
    char second[100];
    char res[203];

    fgets(first, sizeof(first), stdin);
    first[strcspn(first, "\n")] = '\0';

    fgets(second, sizeof(second), stdin);
    second[strcspn(second, "\n")] = '\0';

    strcpy(res, first);
    strcat(res, " & ");
    strcat(res, second);

    printf("%s\n", res);
}