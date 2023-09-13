#include "helpers.h"

void colorize(int height, int width, RGBTRIPLE image[height][width])
{
    // Change all black pixels to a color of your choosing

    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {

            if ((image[h][w].rgbtBlue == 0) && (image[h][w].rgbtGreen == 0) && (image[h][w].rgbtRed == 0))
            {
                image[h][w].rgbtRed = 255;
            }
        }
    }
}
