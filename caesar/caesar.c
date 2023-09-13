#include <cs50.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool only_digits(string input);

string transform(string text, int key);

int main(int argc, string argv[])
{
    // checks that argc is no longer than 2 and that there are only digits in argv[1]
    if ((argc > 2) || (argc < 2))
    {
        printf("Usage: ./caesar\n");
        return 1;
    }
    else if (only_digits(argv[1]))
    {
        printf("Usage: %s %s\n", argv[0], argv[1]);
        return 1;
    }
    else if (argc == 1)
    {
        printf("You did not enter any Key value\n");
        return 1;
    }
    /*
    else
        {
            printf("You Entered: %s \n", argv[1]);

        }
    */
    // convert argv[1] from string to int
    int key_entered = atoi(argv[1]);

    // printf("int %i \n", key_entered);

    string text_entered = get_string("please enter text: ");

    string encrypted_text = transform(text_entered, key_entered);

    printf("ciphertext: %s\n", encrypted_text);
}

bool only_digits(string input)
{
    for (int i = 0; input[i] != '\0'; i++)
    {
        // Returns true if it finds a non digit character
        if (!isdigit(input[i]))
        {
            return true;
        }
    }
    return false;
}

string transform(string text, int key)
{
    int text_length = strlen(text);

    char c_text[text_length];
    char r_text[text_length];

    for (int i = 0; i < text_length; i++)
    {
        if (isalpha(text[i]))
        {
            // int int_char = text[i];
            if (isupper(text[i]))
            {
                c_text[i] = text[i] - 65;
                r_text[i] = (c_text[i] + key) % 26;
                text[i] = r_text[i] + 65;
            }
            else if (islower(text[i]))
            {
                c_text[i] = text[i] - 97;
                r_text[i] = (c_text[i] + key) % 26;
                text[i] = r_text[i] + 97;
            }
        }
    }

    return text;
}