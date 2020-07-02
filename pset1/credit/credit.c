//Luhn algorithm for checking credit card validity

#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    //Get credit card number, and ensure positive value.
    long ccnumber;
    do
    {
        ccnumber = get_long("Number: ");
    }
    while (ccnumber <= 0);

    //Check that it's 13, 15 or 16 digits.
    int countdigits = 0;
    long validation = ccnumber;

    while (validation > 0)
    {
        validation /= 10;
        countdigits++;
    }

    if (countdigits != 13 && countdigits != 15 && countdigits != 16)
    {
        printf("INVALID\n");
    }

    else
    {
        //A loop to process each digit, starting from the right, and add them as per Luhn specs
        int check1 = 0;
        int check2;
        long n = ccnumber;
        while (n > 0)
        {
            check1 += (n % 10);
            n /= 10;
            check2 = (n % 10) * 2;
            check1 += (check2 % 10) + (check2 / 10);
            n /= 10;
        }

        //First Luhn check
        if (check1 % 10 != 0)
        {
            printf("INVALID\n");
        }

        //AMEX specs
        else if (countdigits == 15)
        {
            long amex = (ccnumber / 10000000000000);
            if (amex != 34 && amex != 37)
            {
                printf("INVALID\n");
            }
            else
            {
                printf("AMEX\n");
            }
        }

        //VISA 13 digit Specs
        else if (countdigits == 13)
        {
            printf("VISA\n");
        }

        //16 digit VISA or MASTERCARD specs
        else if (countdigits == 16)
        {
            if (ccnumber / 1000000000000000 == 4)
            {
                printf("VISA\n");
            }
            else
            {
                long master = (ccnumber / 100000000000000);
                if (master > 50 && master < 56)
                {
                    printf("MASTERCARD\n");
                }
                else
                {
                    printf("INVALID\n");
                }
            }
        }
    }
}