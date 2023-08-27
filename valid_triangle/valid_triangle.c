//Includes
#include <cs50.h>
#include <stdio.h>

//declare functions

int add_sides(int a, int b, int c);

int main (void)
{
    //ask for first side

    int x = get_int("First side length: ");

    //ask for second side

    int y = get_int("Second side length: ");

    //ask for third side

    int z = get_int("Third side length: ");

    //call add_sides function
    int result = add_sides(x, y, z);

    if(result == 1)
    {
        printf("triangle is possible\n");
    }
    else if(result == 0)
    {
        printf("triangle is not possible\n");
    }


}


//function definitions
//define add_sides function
int add_sides(int a, int b, int c)
{

    if (((a + b) < c) || ((a + c) < b)  || ((b + c) < a))
    {
        return 0;
    }
    else
    {
        return 1;
    }
}