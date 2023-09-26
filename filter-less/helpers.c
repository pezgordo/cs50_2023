#include "helpers.h"
#include <math.h>
#include <stddef.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Iterate over infile's scanlines

    for (int h = 0; h < height; h++)

    {
        // Iterate over pixels in scanline
        for (int w = 0; w < width; w++)
        {
            int average_tone = round(((image[h][w].rgbtBlue) + (image[h][w].rgbtGreen) + (image[h][w].rgbtRed)) / 3.0);

            image[h][w].rgbtBlue = average_tone;
            image[h][w].rgbtGreen = average_tone;
            image[h][w].rgbtRed = average_tone;
        }
    }

    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
// Iterate over infile's scanlines
{
    for (int h = 0; h < height; h++)

    {
        // Iterate over pixels in scanline
        for (int w = 0; w < width; w++)
        {

            int sepiaRed = round(.393 * image[h][w].rgbtRed + .769 * image[h][w].rgbtGreen + .189 * image[h][w].rgbtBlue);
            int sepiaGreen = round(.349 * image[h][w].rgbtRed + .686 * image[h][w].rgbtGreen + .168 * image[h][w].rgbtBlue);
            int sepiaBlue = round(.272 * image[h][w].rgbtRed + .534 * image[h][w].rgbtGreen + .131 * image[h][w].rgbtBlue);

            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }

            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }

            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }
            image[h][w].rgbtRed = sepiaRed;
            image[h][w].rgbtGreen = sepiaGreen;
            image[h][w].rgbtBlue = sepiaBlue;
        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{

    RGBTRIPLE image_copy_2[height][width];

    for (int h = 0; h < height; h++)
    {
        // Iterate over pixels in scanline

        int rev = width - 1;

        for (int w = 0; w < width; w++)
        {
            image_copy_2[h][w] = image[h][rev];

            // image[h][w] = image_copy_2[h][w];

            rev--;
        }

        for (int ww = 0; ww < width; ww++)
        {
            image[h][ww] = image_copy_2[h][ww];
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE image_copy[height][width];

    for (int hh = 0; hh < height; hh++)
    {
        for (int ww = 0; ww < width; ww++)
        {
            image_copy[hh][ww] = image[hh][ww];
        }
    }

    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {

            float count = 0.0;
            int red = 0;
            int green = 0;
            int blue = 0;

            // Find Top Left
            if (((h - 1) >= 0) && ((w - 1) >= 0))
            {
                int top_left = image_copy[h - 1][w - 1].rgbtRed;
                int top_left_green = image_copy[h - 1][w - 1].rgbtGreen;
                int top_left_blue = image_copy[h - 1][w - 1].rgbtBlue;
                red = red + top_left;
                green = green + top_left_green;
                blue = blue + top_left_blue;
                count++;
            }

            // Find Top
            if ((h - 1) >= 0)
            {
                int top = image_copy[h - 1][w].rgbtRed;
                int top_green = image_copy[h - 1][w].rgbtGreen;
                int top_blue = image_copy[h - 1][w].rgbtBlue;
                red = red + top;
                green = green + top_green;
                blue = blue + top_blue;
                count++;
            }

            // Find Top Right
            if (((h - 1) >= 0) && ((w + 1) < width))
            {
                int top_right = image_copy[h - 1][w + 1].rgbtRed;
                int top_right_green = image_copy[h - 1][w + 1].rgbtGreen;
                int top_right_blue = image_copy[h - 1][w + 1].rgbtBlue;

                red = red + top_right;
                green = green + top_right_green;
                blue = blue + top_right_blue;
                count++;
            }

            // Find Right
            if ((w + 1) < width)
            {
                int right = image_copy[h][w + 1].rgbtRed;
                int right_green = image_copy[h][w + 1].rgbtGreen;
                int right_blue = image_copy[h][w + 1].rgbtBlue;
                red = red + right;
                green = green + right_green;
                blue = blue + right_blue;
                count++;
            }

            // Find Bottom Right
            if (((h + 1) < height) && ((w + 1) < width))
            {
                int bottom_right = image_copy[h + 1][w + 1].rgbtRed;
                int bottom_right_green = image_copy[h + 1][w + 1].rgbtGreen;
                int bottom_right_blue = image_copy[h + 1][w + 1].rgbtBlue;
                red = red + bottom_right;
                green = green + bottom_right_green;
                blue = blue + bottom_right_blue;
                count++;
            }

            // Find Bottom
            if ((h + 1) < height)
            {
                int bottom = image_copy[h + 1][w].rgbtRed;
                int bottom_green = image_copy[h + 1][w].rgbtGreen;
                int bottom_blue = image_copy[h + 1][w].rgbtBlue;
                red = red + bottom;
                green = green + bottom_green;
                blue = blue + bottom_blue;
                count++;
            }

            // Find Bottom Left
            if (((h + 1) < height) && ((w - 1) >= 0))
            {
                int bottom_left = image_copy[h + 1][w - 1].rgbtRed;
                int bottom_left_green = image_copy[h + 1][w - 1].rgbtGreen;
                int bottom_left_blue = image_copy[h + 1][w - 1].rgbtBlue;
                red = red + bottom_left;
                green = green + bottom_left_green;
                blue = blue + bottom_left_blue;
                count++;
            }

            // Find Left
            if ((w - 1) >= 0)
            {
                int left = image_copy[h][w - 1].rgbtRed;
                int left_green = image_copy[h][w - 1].rgbtGreen;
                int left_blue = image_copy[h][w - 1].rgbtBlue;
                red = red + left;
                green = green + left_green;
                blue = blue + left_blue;
                count++;
            }

            // Find Middle

            int middle = image_copy[h][w].rgbtRed;
            int middle_green = image_copy[h][w].rgbtGreen;
            int middle_blue = image_copy[h][w].rgbtBlue;
            red = red + middle;
            green = green + middle_green;
            blue = blue + middle_blue;
            count++;

            image[h][w].rgbtBlue = round(blue / count);
            image[h][w].rgbtGreen = round(green / count);
            image[h][w].rgbtRed = round(red / count);
        }
    }
    return;
}
