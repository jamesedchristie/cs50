#include <stdio.h>
#include <cs50.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
    srand(time(0));
    int x = rand() % 100;
    int guess = get_int("What number am I thinking of?\n");
    while (guess != x)
    if (guess < x)
    {
        printf("Higher\n");
        guess = get_int("Try again: ");
    }
    else if (guess > x)
    {
        printf("Lower\n");
        guess = get_int("Try again: ");
    }
    printf("You got it!\n");
}