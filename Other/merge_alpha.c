#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void merge_sort(int i, int j, char a[], char aux[]);

int main(void)
{
    char unsorted[500];
    char aux[500];
    int length;

    string input = get_string("Enter letters: ");

    length = strlen(input);

    for (int i = 0; i < length; i++)
    {
        unsorted[i] = input[i];
    }

    merge_sort(0, length - 1, unsorted, aux);

    for (int j = 0; j < length; j++)
    {
        printf("%c", unsorted[j]);
    }
    printf("\n");
}

void merge_sort(int i, int j, char a[], char aux[])
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
        else if (toupper(a[pointer_left]) < toupper(a[pointer_right]))
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