#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


char random_allele();

int main(void)
{
srand(time(0));

printf("%c\n", random_allele());
printf("%i\n", rand());

}

char random_allele()
{
    int r = rand() % 3;
    if (r == 0)
    {
        return 'A';
    }
    else if (r == 1)
    {
        return 'B';
    }
    else
    {
        return 'O';
    }
}