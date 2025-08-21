/* The program will create a 10 element array and read in 10 integers into the array.
 * Then the program will print the integers backwards.
 * Then the program will scan for entries in the array which contain the value 100
 * and print out the index of the entries with the number 100.
 * The program will also count the number of entries which equal 100.
 * The program should work even if there are no entries which equal 100.
 * See the sample output for the expect format of the output.
 *
 * input:
 * 9
 * 5
 * 100
 * 16
 * 18
 * 20
 * 6
 * 100
 * 1
 * 77
 *
 * expected output:
 *
 * numb[9] = 77
 * numb[8] = 1
 * numb[7] = 100
 * numb[6] = 6
 * numb[5] = 20
 * numb[4] = 18
 * numb[3] = 16
 * numb[2] = 100
 * numb[1] = 5
 * numb[0] = 9
 *
 * Searching for entries equal to 100
 *
 * Found 100 at 2
 * Found 100 at 7
 *
 * Found 2 entries with 100
 */

#include <stdio.h>

void printbackwards(int arr[], int size)
{
    int i;
    for (i = size - 1; i >= 0; i--)
        printf("numb[%d] = %d\n", i, arr[i]);
}

void searchforentry(int arr[], int size, int key)
{
    printf("\nSearching for entries equal to %d\n\n", key);

    int i, n = 0;
    for (i = 0; i < size; i++)
    {
        if (arr[i] == key)
        {
            printf("Found %d at %d\n", key, i);
            n++;
        }
    }

    printf("\nFound %d entries with %d\n", n, key);
}

int main()
{
    int i, v, arr[10];
    for (i = 0; i < 10; i++)
    {
        scanf("%d", &v);
        arr[i] = v;
    }

    printbackwards(arr, 10);

    searchforentry(arr, 10, 100);

    return 0;
}