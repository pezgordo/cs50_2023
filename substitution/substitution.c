#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

string encrypt(string text, string key);

int main(int argc, string argv[])
{
    // If there is no argv
    if (argc < 2)
    {
        printf("%s key\n", argv[0]);
        return 1;
    }
    // if there is more than 1 argv
    else if (argc > 2)
    {
        printf("you inserter more than 1 key");
        return 1;
    }

    string key = argv[1];
    int string_length = strlen(key);

    if (string_length != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    // verify all characters are letters
    for (int i = 0; key[i] != '\0'; i++)
    {
        if (!isalpha(key[i]))
        {
            printf("key does not have valid characters\n");
            return 1;
        }
    }

    // verify there is no dupplicate characters
    for (int i = 0; i < string_length; i++)
    {
        for (int k = i + 1; k < string_length; k++)
        {
            if (key[i] == key[k])
            {
                printf("Duplicates found\n");
                return 1;
            }
        }
    }

    string message = get_string("plaintext: ");

    string ciphertext = encrypt(message, key);

    printf("%s\n", key);

    printf("ciphertext: %s\n", ciphertext);
}

string encrypt(string text, string key)
{
    int str_length = strlen(text);

    char alphabet[26];
    char ch = 'a';

    char alphabet_up[26];
    char ch_up = 'A';

    char key_array[26];

    // Create a lower chase alphabet array
    for (int i = 0; i < 26; i++)
    {
        alphabet[i] = ch;
        ch = ch + 1;
    }

    // Create an upper case alphabet array

    for (int i = 0; i < 26; i++)
    {
        alphabet_up[i] = ch_up;
        ch_up = ch_up + 1;
    }

    // Create key array
    for (int i = 0; i < 26; i++)
    {
        key_array[i] = toupper(key[i]);
    }

    // For each char on text
    for (int ii = 0; ii < str_length; ii++)
    {
        for (int c = 0; c < 26; c++)
        {
            if (isupper(text[ii]))
            {
                if (text[ii] == alphabet_up[c])
                {
                    text[ii] = key_array[c];
                    break;
                }
            }
            else if (islower(text[ii]))
            {
                if (text[ii] == alphabet[c])
                {
                    text[ii] = tolower(key_array[c]);
                    break;
                }
            }
        }
    }

    return text;
}
