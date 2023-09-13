// Practice working with structs
// Practice applying sorting algorithms

#include <cs50.h>
#include <stdio.h>

#define NUM_CITIES 10

typedef struct
{
    string city;
    int temp;
} avg_temp;

avg_temp temps[NUM_CITIES];

void sort_cities(void);

// Use for bubble sort
void swap_indexes(int x, int y);

int main(void)
{
    temps[0].city = "Austin";
    temps[0].temp = 97;

    temps[1].city = "Boston";
    temps[1].temp = 82;

    temps[2].city = "Chicago";
    temps[2].temp = 85;

    temps[3].city = "Denver";
    temps[3].temp = 90;

    temps[4].city = "Las Vegas";
    temps[4].temp = 105;

    temps[5].city = "Los Angeles";
    temps[5].temp = 82;

    temps[6].city = "Miami";
    temps[6].temp = 97;

    temps[7].city = "New York";
    temps[7].temp = 85;

    temps[8].city = "Phoenix";
    temps[8].temp = 107;

    temps[9].city = "San Francisco";
    temps[9].temp = 66;

    sort_cities();

    printf("\nAverage July Temperatures by City\n\n");

    for (int i = 0; i < NUM_CITIES; i++)
    {
        printf("%s: %i\n", temps[i].city, temps[i].temp);
    }
}

// TODO: Sort cities by temperature in descending order
void sort_cities(void)
{
    // Add your code here
    // BUBBLE SORT
    int swap_counter = 1;

    int i = 0;

    while (swap_counter != 0)
    {
        swap_counter = 0;

        for (int n = 0; n < NUM_CITIES - 1; n++)
        {
            if (temps[n].temp > temps[n + 1].temp)
            {
                swap_indexes(n, n + 1);
                swap_counter = swap_counter + 1;
            }
        }
    }

    /*
    // SELECTION SORT

    for (int ii = 0; ii < NUM_CITIES; ii++)
    {
        int crawler = ii;

        int min_index = ii;


        // find city with the lowest temperature
        for (int i = ii; i < NUM_CITIES; i++)
        {
            if(temps[i].temp < temps[min_index].temp)
            {
                min_index = i;
            }
        }

        // Swap min_index with index[0]
        // Swap city with the lowerst temperature with index[0]
        if (min_index !=0)
        {
            int temporary_temp = temps[ii].temp;
            string temporary_city = temps[ii].city;

            temps[ii].temp = temps[min_index].temp;
            temps[ii].city = temps[min_index].city;

            temps[min_index].temp = temporary_temp;
            temps[min_index].city = temporary_city;
        }


    }
*/
    // Reverse order of the array
    int start = 0;
    int end = NUM_CITIES - 1;

    while (start < end)
    {
        // Swap elements at start and end
        int temporary_order_temp_2 = temps[start].temp;
        string temporary_order_city_2 = temps[start].city;

        temps[start].temp = temps[end].temp;
        temps[start].city = temps[end].city;

        temps[end].temp = temporary_order_temp_2;
        temps[end].city = temporary_order_city_2;

        // Move the pointers towards the center
        start++;
        end--;
    }
}

void swap_indexes(int x, int y)
{
    int temporary_order_temp = temps[x].temp;
    string temporary_order_city = temps[x].city;

    temps[x].temp = temps[y].temp;
    temps[x].city = temps[y].city;

    temps[y].temp = temporary_order_temp;
    temps[y].city = temporary_order_city;
}
