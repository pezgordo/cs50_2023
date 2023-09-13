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

    // Create array to store eight char number / 2 values for each char in text
    //int store[text_length][BITS_IN_BYTE];

    // Create array to store remainders to each char number for each char in text
    int binary[text_length][BITS_IN_BYTE];

    // Para cada char en texto[]
    for (int x = 0; x < text_length; x++)
    {
        // Convertir texto[] char to ASCII decimal value
        int numero = texto[x];

        // para cada char in texto insertar su division entre 2 en array store
        for (int i = 0 ; i < 8; i++)
            {
                binary[x][i] = numero % 2;
                numero = numero / 2;

                //store[x][i] = (numero = numero / 2);
            }
        // para cada char in texto insertar su valor binario en array binary
        //for (int n = 0; n <  BITS_IN_BYTE; n++)
          //  {

            //    binary[x][n] = (store[x][n] % 2);
            //}


        for (int b = BITS_IN_BYTE - 1; b >= 0; b--)
            {
                print_bulb(binary[x][b]);

            }
        /*
        for (int b = BITS_IN_BYTE; b >= 0; b--)
            {

                printf("%i", binary[x][b]);
                printf("\n");
            }
        */
       //printf("%i", binary[x][x]);
        //printf("%i", x);
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
