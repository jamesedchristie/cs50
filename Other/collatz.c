#include <stdio.h>
#include <cs50.h>

int collatz(int n);
int steps = 0;

int main(void)
{
    int n = get_int("n: ");
    
    printf("Collatz(n): %i\n", collatz(n));
}

int collatz(int n)
{
    if (n == 1)
        return steps;
    else if (n % 2 == 0)
    {
        steps++;
        return collatz(n / 2);
    }
    else
    {
        steps++;
        return collatz(3 * n + 1);
    }
}