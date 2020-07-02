#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void merge_sort(int i, int j, string a[], string aux[]);

string words[500];
string aux[500];
string end = "/End";

int main(void)
{
    int length = -1;

    int w = -1;

    do
    {
        w++;
        length++;
        words[w] = get_string("Word: ");
    }
    while (strcmp(words[w], end) != 0);

    merge_sort(0, length - 1, words, aux);

    for (int j = 0; j < length - 1; j++)
    {
        printf("%s, ", words[j]);
    }

    printf("%s.\n", words[length - 1]);
}

void merge_sort(int i, int j, string a[], string b[])
{
    if (j <= i)
        return;

    int mid = (i + j) / 2;

    merge_sort(i, mid, a, b);
    merge_sort(mid + 1, j, a, b);

    int pointer_left = i;
    int pointer_right = mid + 1;
    int k;

    for (k = i; k <= j; k++)
    {
        if (pointer_left == mid + 1)
        {
            b[k] = a[pointer_right];
            pointer_right++;
        }
        else if (pointer_right == j + 1)
        {
            b[k] = a[pointer_left];
            pointer_left++;
        }
        else
        {
            int l = -1;
            int m = 0;
            int n = 0;

            do
            {
                l++;


                if (toupper(a[pointer_left][l]) < toupper(a[pointer_right][l]))
                {
                    b[k] = a[pointer_left];
                    m++;
                }
                else if (toupper(a[pointer_left][l]) > toupper(a[pointer_right][l]))
                {
                    b[k] = a[pointer_right];
                    n++;
                }
            }
            while (toupper(a[pointer_left][l]) == toupper(a[pointer_right][l]));

            pointer_left += m;
            pointer_right += n;
        }
    }

    for (k = i; k <=j; k++)
    {
        a[k] = b[k];
    }

}