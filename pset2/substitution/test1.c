//Substitution encryption with alphabet key

#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>

bool check_alpha(string x);
bool check_repeat(string x);
string cipher(string x);

int main(int argc, string argv[])
{
    //Check that key is provided
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    //Check that only letters
    if (check_alpha(argv[1]) != true)
    {
        printf("Key must contain only characters\n");
        return 1;
    }

    //Check that there are 26 letters
    if (strlen(argv[1]) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    string key = argv[1];

    //Convert key to same case
    for (int i = 0; i < strlen(key); i++)
    {
        key[i] = toupper(key[i]);
    }

    //Check for no repeated letters
    if (check_repeat(key) != true)
    {
        printf("Each character can only be used once.\n");
        return 1;
    }

    printf("%s\n", cipher(key));

}

//Loop to check each character of key and return true/false
bool check_alpha(string x)
{
    for (int i = 0; i < strlen(x); i++)
    {
        if (!isalpha(x[i]))
        {
            return false;
        }
    }
    return true;
}

bool check_repeat(string x)
{
    for (int i = 0; i < (strlen(x) - 1); i++)
    {
        for (int j = i + 1; j < strlen(x); j++)
        {
            if (x[j] == x[i])
            {
                return false;
            }
        }
    }
    return true;
}

string cipher(string x)
{
    for (int i = 0; i < strlen(x); i++)
    {
        x[i] = 'a' + i;
    }
    return x;
}