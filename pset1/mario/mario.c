#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int rows;
    int spaces;
    int hash1;
    int hash2;

    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 20);

    for (rows = 0; rows < height; rows++)
    {
        for (spaces = height - rows - 1; spaces > 0; spaces--)
        {
            printf(" ");
        }
        for (hash1 = 0; hash1 <= rows; hash1++)
        {
            printf("#");
        }
        printf("  ");
        for (hash2 = 0; hash2 <= rows; hash2++)
        {
            printf("#");
        }
        printf("\n");
    }
}