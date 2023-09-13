#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int convert(string input);

//int number = 0:

int main(void)
{
    string input = get_string("Enter a positive integer: ");

    for (int i = 0, n = strlen(input); i < n; i++)
    {
        if (!isdigit(input[i]))
        {
            printf("Invalid Input!\n");
            return 1;
        }
    }

    // Convert string to int
    printf("%i\n", convert(input));
}

int convert(string input)
{
    // TODO
    int string_length = strlen(input);

    if (string_length == 0)
    {
        return 0;
    }

    int last_char = input[string_length -1];

    int converted_last_char = last_char - '0';

    input[string_length - 1] = '\0';

    return converted_last_char + 10 * convert(input);

}