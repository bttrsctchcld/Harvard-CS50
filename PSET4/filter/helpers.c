#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "helpers.h"

// grayscale averages the RGB values and resets the values to the common average
// sepia is CS50 custom function, but need to round the integers and cap the values to 255 (white)
// blur suggests recursion, since the adjusted value for each pixel derives from the original value of surrounding pixels
    // blur average should include the target pixels own value

void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    float gray;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            gray = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.00);
            {
                image[i][j].rgbtBlue = gray;
                image[i][j].rgbtGreen = gray;
                image[i][j].rgbtRed = gray;
            }
        }
    }
    return;
}

void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    float sepiaBlue;
    float sepiaGreen;
    float sepiaRed;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            sepiaBlue = round(image[i][j].rgbtRed * .272 + image[i][j].rgbtGreen * .534 + image[i][j].rgbtBlue * .131);
            sepiaGreen = round(image[i][j].rgbtRed * .349 + image[i][j].rgbtGreen * .686 + image[i][j].rgbtBlue * .168);
            sepiaRed = round(image[i][j].rgbtRed * .393 + image[i][j].rgbtGreen * .769 + image[i][j].rgbtBlue * .189);
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            image[i][j].rgbtBlue = sepiaBlue;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtRed = sepiaRed;
        }
    }
}

void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < (width / 2); j++)
        {
            RGBTRIPLE carbuncle = image[i][j];
            image[i][j] = image[i][width - (j + 1)];
            image[i][width - (j + 1)] = carbuncle;
        }
    }
    return;
}

void blur(int height, int width, RGBTRIPLE image[height][width])
{
    float blurBlue;
    float blurGreen;
    float blurRed;

    RGBTRIPLE imagecopy[height][width];
    float counter;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            blurBlue = 0;
            blurGreen = 0;
            blurRed = 0;
            counter = 0;

            for (int k = -1; k < 2; k++)
            {
                if (j + k < 0 || j + k > height - 1)
                {
                    continue;
                }
                for (int h = -1; h < 2; h++)
                {
                    if (i + h < 0 || i + h > width - 1)
                    {
                        continue;
                    }

                    blurBlue += image[i + h][j + k].rgbtBlue;
                    blurGreen += image[i + h][j + k].rgbtGreen;
                    blurRed += image[i + h][j + k].rgbtRed;
                    counter++;
                }
            }
            imagecopy[i][j].rgbtBlue = round(blurBlue / counter);
            imagecopy[i][j].rgbtGreen = round(blurGreen / counter);
            imagecopy[i][j].rgbtRed = round(blurRed / counter);
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = imagecopy[i][j].rgbtBlue;
            image[i][j].rgbtGreen = imagecopy[i][j].rgbtGreen;
            image[i][j].rgbtRed = imagecopy[i][j].rgbtRed;
        }
    }
}