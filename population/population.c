#include <cs50.h>
#include <stdio.h>

int start_size(void);
int end_size(int s);

int calculate(int s, int e);
void print_n(int years);

// MAIN
int main(void)
{
    // TODO: Prompt for start size
    int s = start_size();

    // TODO: Prompt for end size
    int e = end_size(s);

    // TODO: Calculate number of years until we reach threshold
    int y = calculate(s, e);

    // TODO: Print number of years

    print_n(y);
}

// START SIZE
int start_size(void)
{
    int s;
    do
    {
        s = get_int("Start Size: ");
    }
    while (s < 9);
    return s;
}

// END SIZE
int end_size(int s)
{
    int e;
    do
    {
        e = get_int("End Size: ");
    }
    while (e < s);
    return e;
}

// CALCULATE
int calculate(int s, int e)
{
    int n = s;
    int years = 0;
    if (n != e)
    {
        do
        {
            n = n + (n / 3) - (n / 4);
            years++;
        }
        while (n < e);
    }
    else
    {
        years = 0;
    }

    return years;
}

// PRINT
void print_n(int years)
{
    printf("Years: %i\n", years);
}