#include <stdio.h>
#include <cs50.h>



int main(void)
{
    int hundred[100];
    int n;
    for (n = 0; n < 100; n++)
    {
        hundred[n] = n * 2;
    }
    int number = get_int("No: ");
    printf("%i\n", hundred[number]);
}