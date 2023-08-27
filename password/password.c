// Check that a password has at least one lowercase letter, uppercase letter, number and symbol
// Practice iterating through a string
// Practice using the ctype library

#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

bool valid(string password);

int main(void)
{
    string password = get_string("Enter your password: ");
    if (valid(password))
    {
        printf("Your password is valid!\n");
    }
    else
    {
        printf("Your password needs at least one uppercase letter, lowercase letter, number and symbol\n");
    }
}

// TODO: Complete the Boolean function below
bool valid(string password)
{

    bool has_upper = false;
    bool has_lower = false;
    bool has_number = false;
    bool has_symbol = false;

    //check if password has UPPERCASE letter

    for(int i = 0; password[i]; i++)
    {
        if(isupper(password[i]))
        {
            has_upper = true;
        }

    }

    //check if password has lowercase letter
    for(int i = 0; password[i]; i++)
    {
        if(islower(password[i]))
        {
            has_lower = true;
        }

    }

    //check to see if password has a number
   for(int i = 0; password[i]; i++)
    {
        if(isdigit(password[i]))
        {
            has_number = true;
        }

    }
    //check to see if password has a symbol
   for(int i = 0; password[i]; i++)
    {
        if(ispunct(password[i]))
        {
            has_symbol = true;
        }

    }



    return has_upper && has_lower && has_number && has_symbol;
}
