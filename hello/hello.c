#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // declare variable 'name' with string format
    string name = get_string("What is your name: ");
    // print the name input
    printf("hello, %s\n", name);
}
