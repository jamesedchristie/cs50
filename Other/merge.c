#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>

#define MAX 10

void merge_sort(int i, int j, int a[], int aux[]);

int main(void)
{
    int unsorted[MAX];
    int aux[MAX];
    int length;

    length = get_int("How many numbers?\n");

    for (int i = 0; i < length; i++)
    {
        unsorted[i] = get_int("Number %i: ", i + 1);
    }

    merge_sort(0, length - 1, unsorted, aux);

    for (int n = 0; n < length; n++)
    {
        printf("%i ", unsorted[n]);
    }
    printf("\n");
}

void merge_sort(int i, int j, int a[], int aux[])
{
    if (j <= i)
        return;

    int mid = (i + j) / 2;

    merge_sort(i, mid, a, aux);
    merge_sort(mid + 1, j, a, aux);

    int pointer_left = i;
    int pointer_right = mid + 1;
    int k;

    for (k = i; k <= j; k++)
    {
        if (pointer_left == mid + 1)
        {
            aux[k] = a[pointer_right];
            pointer_right++;
        }
        else if (pointer_right == j + 1)
        {
            aux[k] = a[pointer_left];
            pointer_left++;
        }
        else if (a[pointer_left] < a[pointer_right])
        {
            aux[k] = a[pointer_left];
            pointer_left++;
        }
        else
        {
            aux[k] = a[pointer_right];
            pointer_right++;
        }
    }

    for (k = i; k <=j; k++)
    {
        a[k] = aux[k];
    }

}
