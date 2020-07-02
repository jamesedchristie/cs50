#include <stdio.h>
#include <math.h>

typedef struct
{
    int rgbtRed;
    int rgbtBlue;
    int rgbtGreen;
}
RGBTRIPLE;

int main(void)
{
    int height = 10;
    int width = 10;

    RGBTRIPLE pic[height][width];

    for (int x = 0; x < height; x++)
    {
        for (int y = 0; y < width; y++)
        {
            pic[x][y].rgbtRed = 2 + ((x + (y * 2) + 1) * 5);
            pic[x][y].rgbtBlue = 2 + ((x + (y * 2) + 1) * 7);
            pic[x][y].rgbtGreen = 2 + ((x + (y * 2) + 1) * 8);
        }
    }

    RGBTRIPLE bimage[height + 2][width + 2];

    for (int r = 0; r <= height + 1; r++)
    {
        for (int c = 0; c <= width + 1; c++)
        {
            if (r == 0 || r == height + 1 || c == 0 || c == width + 1)
            {
                bimage[r][c].rgbtBlue = 0;
                bimage[r][c].rgbtGreen = 0;
                bimage[r][c].rgbtRed = 0;
            }
            else
                bimage[r][c] = pic[r - 1][c - 1];
        }
    }


    RGBTRIPLE edged[height + 2][width + 2];

    RGBTRIPLE Gx, Gy;

    int xgrid[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int ygrid[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    for (int r = 1; r <= height; r++)
    {
        for (int c = 1; c <= width; c++)
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
                    Gx.rgbtBlue += (bimage[r + x][c + y].rgbtBlue * xgrid[x + 1][y + 1]);
                    Gx.rgbtGreen += (bimage[r + x][c + y].rgbtGreen * xgrid[x + 1][y + 1]);
                    Gx.rgbtRed += (bimage[r + x][c + y].rgbtRed * xgrid[x + 1][y + 1]);

                    Gy.rgbtBlue += (bimage[r + x][c + y].rgbtBlue * ygrid[x + 1][y + 1]);
                    Gy.rgbtGreen += (bimage[r + x][c + y].rgbtGreen * ygrid[x + 1][y + 1]);
                    Gy.rgbtRed += (bimage[r + x][c + y].rgbtRed * ygrid[x + 1][y + 1]);
                }
            }
            edged[r][c].rgbtBlue = (int)round(sqrt(pow(Gx.rgbtBlue, 2) + pow(Gy.rgbtBlue, 2))) % 255;
            edged[r][c].rgbtGreen = (int)round(sqrt(pow(Gx.rgbtGreen, 2) + pow(Gy.rgbtGreen, 2))) % 255;
            edged[r][c].rgbtRed = (int)round(sqrt(pow(Gx.rgbtRed, 2) + pow(Gy.rgbtRed, 2))) % 255;

        }
    }

    for (int r = 1; r <= height; r++)
    {
        for (int c = 1; c <= width; c++)
        {
            pic[r - 1][c - 1] = bimage[r][c];
        }
    }
    printf("%i, %i, %i\n", pic[5][5].rgbtRed, pic[5][5].rgbtGreen, pic[5][5].rgbtBlue);
}