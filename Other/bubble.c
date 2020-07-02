#include <stdio.h>
#include <cs50.h>
#include <string.h>

#define MAX 10

void bubble_sort(void);

int unsorted[MAX];

int length;

int main(void)
{
    length = get_int("How many numbers?\n");

    for (int i = 0; i < length; i++)
    {
        unsorted[i] = get_int("Number %i: ", i + 1);
    }

    bubble_sort();

    for (int n = 0; n < length; n++)
    {
        printf("%i ", unsorted[n]);
    }
    printf("\n");
}

void bubble_sort(void)
{
    int swaps = 1;

    do
    {
        swaps = 0;

        for (int i = 0; i < length - 1; i++)
        {
            for (int j = i + 1; j < length; j++)
            {
                if (unsorted[i] > unsorted [j])
                {
                    int temp = unsorted[i];
                    unsorted[i] = unsorted[j];
                    unsorted[j] = temp;
                    swaps++;
                }
            }
        }
    }
    while (swaps != 0);
    return;
}