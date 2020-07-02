// Simple caesar cypher

#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <stdlib.h>

bool check_digits(string x);

int main(int argc, string argv[])
{
    //Check that user enters key in command line
    if (argc != 2 || check_digits(argv[1]) != true || atoi(argv[1]) < 0)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    //Prompt for phrase to encrypt
    string plain = get_string("plaintext: ");

    //Run each character through cipher only if alphabetical
    for (int i = 0; i < strlen(plain); i++)
    {
        if isalpha(plain[i])
        {
            if islower(plain[i])
            {
                plain[i] = ((plain[i] - 'a') + atoi(argv[1])) % 26 + 'a';
            }
            else
            {
                plain[i] = ((plain[i] - 'A') + atoi(argv[1])) % 26 + 'A';
            }
        }
    }

    //Print encrypted phrase
    printf("ciphertext: %s\n", plain);
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
