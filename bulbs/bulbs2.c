#include <cs50.h>
#include <stdio.h>
#include <string.h>

const int BITS_IN_BYTE = 8;

void print_bulb(int bit);

int main(void)
{
    // TODO
    // Get text Input
    string texto = get_string("Insert Text: ");



    //Text length
    int text_length = strlen(texto);

    int store[text_length][BITS_IN_BYTE];


    // Para cada char en texto[]
    for (int x = 0; x < text_length; x++)
    {
        int numero = texto[x];


        // para cada char in texto insertar su division entre 2 en array store
        for (int i = 0 ; i < 8; i++)
            {

                //store[x][i] = (numero % 2);

                store[x][i] = (numero /= 2) % 2;
            }

        for (int b = 0; b <  BITS_IN_BYTE; b++)
            {
                print_bulb(store[x][b]);

            }
        printf("\n");
    }

}


void print_bulb(int bit)
{
    if (bit == 0)
    {
        // Dark emoji
        printf("\U000026AB");
    }
    else if (bit == 1)
    {
        // Light emoji
        printf("\U0001F7E1");
    }
}
