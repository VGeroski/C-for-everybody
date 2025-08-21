/* A Touring Machine. This is a subset of an important concept in Computer Science called a Turing Machine.
 * We call it a "Touring Machine" because it "wanders around and does things in memory" similar to a Turing Machine.
 * Your computer has 256 characters of memory.
 * The machine keeps track of the "position" or the "head" where data is to be written.
 * The starting position is zero.
 * You are to read a sequence of instructions from input and perform those instructions.
 * When there are no more instructions, print the memory out as a zero-terminated C character array.
 * Here are the instructions you need to support:
 *
 * 42     Store this value into the memory at the current position
 * >      Move the "position" one to the right (i.e. position++);
 * <      Move the "position" one to the left (i.e. position--);
 *
 * All of the numbers should be in the range of 0-255 so they fit into a C char variable.
 */

#include <stdio.h>
#include <string.h>

int extract_value(char token[])
{
    int value = 0, i = 0;

    for (i = 0; token[i] != '\0'; i++)
        value = 10 * value + (token[i] - '0');

    return value;
}

int main()
{
    char memory[256], token[256], line[256];
    int position = 0, value;

    for (int i = 0; i < 256; i++)
        memory[i] = '\0';

    while (1)
    {
        if (fgets(line, sizeof(line), stdin) == NULL)
        {
            break; // EOF or input error
        }

        // Remove trailing newline character
        line[strcspn(line, "\n")] = 0;

        // Check for empty line
        if (line[0] == '\0')
        {
            break;
        }

        // Tokenize input line
        char *tok = strtok(line, " ");

        while (tok != NULL)
        {
            if (tok[0] == '>')
                position++;
            else if (tok[0] == '<')
                position--;
            else
                memory[position] = extract_value(tok);

            tok = strtok(NULL, " ");
        }
    }

    printf("Memory:\n%s\n", memory);
}