#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef uint8_t BYTE;

int BLOCK_SIZE = 512;

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Usage: %i", argc);
        return 1;
    }

    FILE *raw_file = fopen(argv[1], "r");

    if (raw_file == NULL)
    {
        printf("Unable to open file\n");
        return 1;
    }

    BYTE buffer_size = BLOCK_SIZE;
    BYTE *buffer = (BYTE *) malloc(sizeof(BYTE) * BLOCK_SIZE);

    char n = 0;
    int j = 0;

    int file = 0;

    while (fread(buffer, sizeof(BYTE), BLOCK_SIZE, raw_file) == BLOCK_SIZE)
    {
        FILE *picture;
        // If start of new JPEG
        if ((buffer[0] == 0xff) && (buffer[1] == 0xd8) && (buffer[2] == 0xff) && ((buffer[3] & 0xf0) == 0xe0))
        {

            char filename[8];
            sprintf(filename, "%03i.jpg", n);
            picture = fopen(filename, "a");

            if (picture == NULL)
            {
                printf("Error opening file/n");
                return 1;
            }

            n++;
            j++;

            if (n == j)
            {
                file = 1;
                fwrite(buffer, sizeof(BYTE), BLOCK_SIZE, picture);
            }
        }
        else
        {
            char filename[8];
            sprintf(filename, "%03i.jpg", n - 1);
            picture = fopen(filename, "a");

            if (file > 0)
            {
                fwrite(buffer, sizeof(BYTE), BLOCK_SIZE, picture);
            }
        }
        fclose(picture);
    }

    fclose(raw_file);

    free(buffer);
}
