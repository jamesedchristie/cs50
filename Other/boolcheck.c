#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <stdlib.h>

bool check_digits(string x);

int main(void)
{
    string a = get_string("String: ");
    if (check_digits(a) == true)
    {
        printf("Digits\n");
    }
    else
    {
        printf("Not Digits\n");
    }
}

bool check_digits(string x)
{
    for (int i = 0; i < strlen(x); i++)
    {
        if (!isdigit(x[i]))
        {
            return false;
        }
    }
    return true;
}