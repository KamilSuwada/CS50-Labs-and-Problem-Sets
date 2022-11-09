#include "helpers.h"
#include "stdio.h"
#include <math.h>


// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            RGBTRIPLE rgb = image[h][w]; // get the pixel
            int average = round((rgb.rgbtRed + rgb.rgbtGreen + rgb.rgbtBlue) / 3.0); // calculate the average of the values.

            // setting the values to the average.
            image[h][w].rgbtRed = average;
            image[h][w].rgbtGreen = average;
            image[h][w].rgbtBlue = average;
        }
    }

    return;
}


// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int length, index;

    if (width % 2 == 0)
    {
        length = width / 2;
    }
    else
    {
        length = (width - 1) / 2;
    }

    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < length; w++)
        {
            index = width - (w + 1);
            RGBTRIPLE temp = image[h][w]; // get the copy of the pixel

            // swap pixels
            image[h][w] = image[h][index];
            image[h][index] = temp;
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width]; // copy of the ORIGINAL image

    for (int h = 0; h < height; h++) // loop through rows
    {
        for (int w = 0; w < width; w++) // loop through columns
        {
            temp[h][w] = image[h][w];
        }
    }


    for (int h = 0; h < height; h++) // loop through rows
    {
        for (int w = 0; w < width; w++) // loop through columns
        {
            // account for sum of rgb values and number of pixels
            float red = 0;
            float blue = 0;
            float green = 0;
            int number_of_pixels = 0;

            for (int hh = -1; hh < 2; hh++) // loop through row -1 to row + 1
            {
                for (int ww = -1; ww < 2; ww++) // loop through column -1 to row + 1
                {

                    if (h + hh < 0 || h + hh >= height) // check if the pixel is in the boundries (row)
                    {
                        continue;
                    }

                    if (w + ww < 0 || w + ww >= width) // check if the pixel is in the boundries (column)
                    {
                        continue;
                    }

                    // compute averages !!! use temp copy to compute values !!!
                    red += temp[h + hh][w + ww].rgbtRed;
                    blue += temp[h + hh][w + ww].rgbtBlue;
                    green += temp[h + hh][w + ww].rgbtGreen;
                    number_of_pixels += 1;
                }
            }

            // assign averages to the original image
            image[h][w].rgbtRed = round(red / number_of_pixels);
            image[h][w].rgbtGreen = round(green / number_of_pixels);
            image[h][w].rgbtBlue = round(blue / number_of_pixels);
        }
    }

    return;
}


// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width]; // copy of the ORIGINAL image

    for (int h = 0; h < height; h++) // loop through rows
    {
        for (int w = 0; w < width; w++) // loop through columns
        {
            temp[h][w] = image[h][w];
        }
    }

    int gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    for (int h = 0; h < height; h++) // loop through rows
    {
        for (int w = 0; w < width; w++) // loop through columns
        {
            // account for sum of rgb values and number of pixels, for each gx and gy.
            float gx_red = 0;
            float gx_blue = 0;
            float gx_green = 0;

            float gy_red = 0;
            float gy_blue = 0;
            float gy_green = 0;

            for (int hh = -1; hh < 2; hh++) // loop through row -1 to row + 1
            {
                for (int ww = -1; ww < 2; ww++) // loop through column -1 to row + 1
                {

                    if (h + hh < 0 || h + hh >= height) // check if the pixel is in the boundries (row)
                    {
                        continue;
                    }

                    if (w + ww < 0 || w + ww >= width) // check if the pixel is in the boundries (column)
                    {
                        continue;
                    }

                    // compute Sobel !!! use temp copy to compute values !!!
                    gx_red += temp[h + hh][w + ww].rgbtRed * gx[hh + 1][ww + 1];
                    gx_blue += temp[h + hh][w + ww].rgbtBlue * gx[hh + 1][ww + 1];
                    gx_green += temp[h + hh][w + ww].rgbtGreen * gx[hh + 1][ww + 1];

                    gy_red += temp[h + hh][w + ww].rgbtRed * gy[hh + 1][ww + 1];
                    gy_blue += temp[h + hh][w + ww].rgbtBlue * gy[hh + 1][ww + 1];
                    gy_green += temp[h + hh][w + ww].rgbtGreen * gy[hh + 1][ww + 1];
                }
            }

            // calculate Sobel values:
            int red = round(sqrt(gx_red * gx_red + gy_red * gy_red));
            int green = round(sqrt(gx_green * gx_green + gy_green * gy_green));
            int blue = round(sqrt(gx_blue * gx_blue + gy_blue * gy_blue));

            if (red > 255)
            {
                red = 255;
            }

            if (green > 255)
            {
                green = 255;
            }

            if (blue > 255)
            {
                blue = 255;
            }

            // assign values to the original image
            image[h][w].rgbtRed = red;
            image[h][w].rgbtGreen = green;
            image[h][w].rgbtBlue = blue;
        }
    }

    return;
}