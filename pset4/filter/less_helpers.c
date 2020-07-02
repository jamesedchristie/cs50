#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE grey[height][width];

    for (int r = 0; r < height; r++)
    {
        for (int c = 0; c < width; c++)
        {
            float x = image[r][c].rgbtBlue + image[r][c].rgbtGreen + image[r][c].rgbtRed;
            float y = x / 3;
            grey[r][c].rgbtBlue = round(y);
            grey[r][c].rgbtGreen = round(y);
            grey[r][c].rgbtRed = round(y);
            image[r][c] = grey[r][c];
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE sepia[height][width];

    for (int r = 0; r < height; r++)
    {
        for (int c = 0; c < width; c++)
        {
            int sepB = round(.272 * image[r][c].rgbtRed + .534 * image[r][c].rgbtGreen + .131 * image[r][c].rgbtBlue);
            if (sepB > 255)
                sepB = 255;
            int sepG = round(.349 * image[r][c].rgbtRed + .686 * image[r][c].rgbtGreen + .168 * image[r][c].rgbtBlue);
            if (sepG > 255)
                sepG = 255;
            int sepR = round(.393 * image[r][c].rgbtRed + .769 * image[r][c].rgbtGreen + .189 * image[r][c].rgbtBlue);
            if (sepR > 255)
                sepR = 255;

            sepia[r][c].rgbtBlue = sepB;
            sepia[r][c].rgbtGreen = sepG;
            sepia[r][c].rgbtRed = sepR;
            image[r][c] = sepia[r][c];
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE mirror[height][width];

    for (int r = 0; r < height; r++)
    {
        for (int c = 0; c < width; c++)
        {
            mirror[r][c] = image[r][width - (c + 1)];
        }
    }

    for (int r = 0; r < height; r++)
    {
        for (int c = 0; c < width; c++)
        {
            image[r][c] = mirror[r][c];
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE blurred[height][width];

    for (int r = 0; r < height; r++)
    {
        for (int c = 0; c < width; c++)
        {
            int blurB;
            int blurG;
            int blurR;
            float x = 4;
            float y = 6;
            float z = 9;

            if (r == 0)
            {
                if (c == 0)
                {
                    blurB = round((image[r][c].rgbtBlue + image[r][c + 1].rgbtBlue + image[r + 1][c].rgbtBlue + image[r + 1][c + 1].rgbtBlue) / x);
                    blurG = round((image[r][c].rgbtGreen + image[r][c + 1].rgbtGreen + image[r + 1][c].rgbtGreen + image[r + 1][c + 1].rgbtGreen) / x);
                    blurR = round((image[r][c].rgbtRed + image[r][c + 1].rgbtRed + image[r + 1][c].rgbtRed + image[r + 1][c + 1].rgbtRed) / x);
                }
                else if (c == width - 1)
                {
                    blurB = round((image[r][c].rgbtBlue + image[r][c - 1].rgbtBlue + image[r + 1][c].rgbtBlue + image[r + 1][c - 1].rgbtBlue) / x);
                    blurG = round((image[r][c].rgbtGreen + image[r][c - 1].rgbtGreen + image[r + 1][c].rgbtGreen + image[r + 1][c - 1].rgbtGreen) / x);
                    blurR = round((image[r][c].rgbtRed + image[r][c - 1].rgbtRed + image[r + 1][c].rgbtRed + image[r + 1][c - 1].rgbtRed) / x);
                }
                else
                {
                    blurB = round((image[r][c].rgbtBlue + image[r][c - 1].rgbtBlue + image[r][c + 1].rgbtBlue + image[r + 1][c].rgbtBlue + image[r + 1][c - 1].rgbtBlue + image[r + 1][c + 1].rgbtBlue) / y);
                    blurG = round((image[r][c].rgbtGreen + image[r][c - 1].rgbtGreen + image[r][c + 1].rgbtGreen + image[r + 1][c].rgbtGreen + image[r + 1][c - 1].rgbtGreen + image[r + 1][c + 1].rgbtGreen) / y);
                    blurR = round((image[r][c].rgbtRed + image[r][c - 1].rgbtRed + image[r][c + 1].rgbtRed + image[r + 1][c].rgbtRed + image[r + 1][c - 1].rgbtRed + image[r + 1][c + 1].rgbtRed) / y);
                }
            }

            else if (c == 0 && r != 0)
            {
                if (r == height - 1)
                {
                    blurB = round((image[r][c].rgbtBlue + image[r][c + 1].rgbtBlue + image[r - 1][c].rgbtBlue + image[r - 1][c + 1].rgbtBlue) / x);
                    blurG = round((image[r][c].rgbtGreen + image[r][c + 1].rgbtGreen + image[r - 1][c].rgbtGreen + image[r - 1][c + 1].rgbtGreen) / x);
                    blurR = round((image[r][c].rgbtRed + image[r][c + 1].rgbtRed + image[r - 1][c].rgbtRed + image[r - 1][c + 1].rgbtRed) / x);
                }
                else
                {
                    blurB = round((image[r][c].rgbtBlue + image[r - 1][c].rgbtBlue + image[r + 1][c].rgbtBlue + image[r + 1][c + 1].rgbtBlue + image[r - 1][c + 1].rgbtBlue + image[r][c + 1].rgbtBlue) / y);
                    blurG = round((image[r][c].rgbtGreen + image[r - 1][c].rgbtGreen + image[r + 1][c].rgbtGreen + image[r + 1][c + 1].rgbtGreen + image[r - 1][c + 1].rgbtGreen + image[r][c + 1].rgbtGreen) / y);
                    blurR = round((image[r][c].rgbtRed + image[r - 1][c].rgbtRed + image[r + 1][c].rgbtRed + image[r + 1][c + 1].rgbtRed + image[r - 1][c + 1].rgbtRed + image[r][c + 1].rgbtRed) / y);
                }

            }

            else if (r == height - 1 && r != 0)
            {
                if (c == width - 1)
                {
                    blurB = round((image[r][c].rgbtBlue + image[r][c - 1].rgbtBlue + image[r - 1][c].rgbtBlue + image[r - 1][c - 1].rgbtBlue) / x);
                    blurG = round((image[r][c].rgbtGreen + image[r][c - 1].rgbtGreen + image[r - 1][c].rgbtGreen + image[r - 1][c - 1].rgbtGreen) / x);
                    blurR = round((image[r][c].rgbtRed + image[r][c - 1].rgbtRed + image[r - 1][c].rgbtRed + image[r - 1][c - 1].rgbtRed) / x);
                }
                else
                {
                    blurB = round((image[r][c].rgbtBlue + image[r][c - 1].rgbtBlue + image[r][c + 1].rgbtBlue + image[r - 1][c].rgbtBlue + image[r - 1][c - 1].rgbtBlue + image[r - 1][c + 1].rgbtBlue) / y);
                    blurG = round((image[r][c].rgbtGreen + image[r][c - 1].rgbtGreen + image[r][c + 1].rgbtGreen + image[r - 1][c].rgbtGreen + image[r - 1][c - 1].rgbtGreen + image[r - 1][c + 1].rgbtGreen) / y);
                    blurR = round((image[r][c].rgbtRed + image[r][c - 1].rgbtRed + image[r][c + 1].rgbtRed + image[r - 1][c].rgbtRed + image[r - 1][c - 1].rgbtRed + image[r - 1][c + 1].rgbtRed) / y);
                }
            }

            else if (c == width - 1 && r != 0 && r != height - 1)
            {
                blurB = round((image[r][c].rgbtBlue + image[r + 1][c].rgbtBlue + image[r - 1][c].rgbtBlue + image[r + 1][c - 1].rgbtBlue + image[r][c - 1].rgbtBlue + image[r - 1][c - 1].rgbtBlue) / y);
                blurG = round((image[r][c].rgbtGreen + image[r + 1][c].rgbtGreen + image[r - 1][c].rgbtGreen + image[r + 1][c - 1].rgbtGreen + image[r][c - 1].rgbtGreen + image[r - 1][c - 1].rgbtGreen) / y);
                blurR = round((image[r][c].rgbtRed + image[r + 1][c].rgbtRed + image[r - 1][c].rgbtRed + image[r + 1][c - 1].rgbtRed + image[r][c - 1].rgbtRed + image[r - 1][c - 1].rgbtRed) / y);
            }

            else
            {
                blurB = round((image[r][c].rgbtBlue + image[r][c - 1].rgbtBlue + image[r][c + 1].rgbtBlue + image[r - 1][c].rgbtBlue + image[r - 1][c - 1].rgbtBlue + image[r - 1][c + 1].rgbtBlue + image[r + 1][c].rgbtBlue + image[r + 1][c - 1].rgbtBlue + image[r + 1][c + 1].rgbtBlue) / z);
                blurG = round((image[r][c].rgbtGreen + image[r][c - 1].rgbtGreen + image[r][c + 1].rgbtGreen + image[r - 1][c].rgbtGreen + image[r - 1][c - 1].rgbtGreen + image[r - 1][c + 1].rgbtGreen + image[r + 1][c].rgbtGreen + image[r + 1][c - 1].rgbtGreen + image[r + 1][c + 1].rgbtGreen) / z);
                blurR = round((image[r][c].rgbtRed + image[r][c - 1].rgbtRed + image[r][c + 1].rgbtRed + image[r - 1][c].rgbtRed + image[r - 1][c - 1].rgbtRed + image[r - 1][c + 1].rgbtRed + image[r + 1][c].rgbtRed + image[r + 1][c - 1].rgbtRed + image[r + 1][c + 1].rgbtRed) / z);
            }

            blurred[r][c].rgbtBlue = blurB;
            blurred[r][c].rgbtGreen = blurG;
            blurred[r][c].rgbtRed = blurR;
        }
    }

    for (int r = 0; r < height; r++)
    {
        for (int c = 0; c < width; c++)
        {
            image[r][c] = blurred[r][c];
        }
    }
    return;
}
