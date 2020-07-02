#include "helpers.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>

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

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE edged[height][width];

    for (int r = 0; r < height; r++)
    {
        for (int c = 0; c < width; c++)
        {
            edged[r][c] = image[r][c];
        }
    }


   typedef struct
    {
        int rgbtBlue;
        int rgbtGreen;
        int rgbtRed;
    }
    SOBEL;

    SOBEL Gx, Gy;

    int xgrid[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int ygrid[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    for (int r = 0; r < height; r++)
    {
        for (int c = 0; c < width; c++)
        {
            Gx.rgbtBlue = 0;
            Gx.rgbtGreen = 0;
            Gx.rgbtRed = 0;

            Gy.rgbtBlue = 0;
            Gy.rgbtGreen = 0;
            Gy.rgbtRed = 0;

            for (int x = -1; x < 2; x++)
            {
                for (int y = -1; y < 2; y++)
                {
                    if ((r + x < 0) || (r + x == height) || (c + y < 0) || (c + y == width))
                    {
                        continue;
                    }


                        Gx.rgbtBlue += (image[r + x][c + y].rgbtBlue * xgrid[x + 1][y + 1]);
                        Gx.rgbtGreen += (image[r + x][c + y].rgbtGreen * xgrid[x + 1][y + 1]);
                        Gx.rgbtRed += (image[r + x][c + y].rgbtRed * xgrid[x + 1][y + 1]);

                        Gy.rgbtBlue += (image[r + x][c + y].rgbtBlue * ygrid[x + 1][y + 1]);
                        Gy.rgbtGreen += (image[r + x][c + y].rgbtGreen * ygrid[x + 1][y + 1]);
                        Gy.rgbtRed += (image[r + x][c + y].rgbtRed * ygrid[x + 1][y + 1]);

                }
            }
            edged[r][c].rgbtBlue = round(fmin(255, sqrt(pow(Gx.rgbtBlue, 2) + pow(Gy.rgbtBlue, 2))));
            edged[r][c].rgbtGreen = round(fmin(255, sqrt(pow(Gx.rgbtGreen, 2) + pow(Gy.rgbtGreen, 2))));
            edged[r][c].rgbtRed = round(fmin(255, sqrt(pow(Gx.rgbtRed, 2) + pow(Gy.rgbtRed, 2))));

        }
    }

    for (int r = 0; r < height; r++)
    {
        for (int c = 0; c < width; c++)
        {
            image[r][c] = edged[r][c];
        }
    }
    return;
}
