// Write a function to replace vowels with numbers
// Get practice with strings
// Get practice with command line
// Get practice with switch

#include <cs50.h>
#include <stdio.h>
#include <string.h>

string replace(string input);

int main(int argc, string argv[])
{

    if (argc != 2)
    {
        printf("Usage: %s word\n", argv[0]);
        return 1;
    }
    string result = replace(argv[1]);
    printf("%s\n", result);
}

string replace(string input)
{
    string change = input;
    for (int i = 0; i < strlen(change); i++)
        switch (change[i])
        {
            case 'a':
                change[i] = '6';
                break;
            case 'e':
                change[i] = '3';
                break;
            case 'i':
                change[i] = '1';
                break;
            case 'o':
                change[i] = '0';
                break;
        }
    return change;
}