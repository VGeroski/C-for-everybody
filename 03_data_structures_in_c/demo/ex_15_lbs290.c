/* You are to perform the following steps in a function named process():
 *  - (1) Print out the string you are passed.
 *  - (2) Count the number of characters in the string.
 *  - (3) If there are more than 10 characters in the string print out the 10th character (line[9])
 *  - (4) Go through the string and replace every blank with a dash '-'
 *  - (5) Print out the new string with dashes.
 */

#include <stdio.h>
#include <string.h>

void process(char line[]) 
{
    printf("\nString: %s\n",line);

    int len = strlen(line);
    printf("Count=%d\n", len);

    if (len > 10)
    {
        printf("The ninth character is: %c\n", line[9]);
    }

    int i;
    for (i = 0; i < len; i++)
    {
        if (line[i] == ' ')
            line[i] = '-';
    }

    printf("String: %s\n",line);
}

int main()
{
    char line[1000];
    
    strcpy(line, "Hi there and welcome to LBS290");
    process(line);

    strcpy(line, "I love C");
    process(line);
}
