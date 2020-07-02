//Assesses readability of text and assigns grade level (US)

#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <math.h>

int count_letters(string x);
int count_words(string x);
int count_sent(string x);

int main(void)
{
    //Prompt user to input text
    string text = get_string("Text: ");

    //Use functions defined below to count letters, words and sentences. They are assigned float value so they return floats in next calculations
    float letters = count_letters(text);
    float words = count_words(text);
    float sent = count_sent(text);

    //Calculate values to input into Coleman-Liau formula
    float wph = 100 / words;
    float L = (letters * wph);
    float S = (sent * wph);

    //Calculate Coleman-Liau score from imported formula
    float index = 0.0588 * L - 0.296 * S - 15.8;

    //Print Grade based on result, rounded to nearest integer for between 1 to 16 and printing 16+ or Before Grade 1 otherwise
    if (index >= 1 && index <= 16)
    {
        printf("Grade %i\n", (int) round(index));
    }
    else if (index > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Before Grade 1\n");
    }
}

//Counting functions in form of loops which run through string array and count up appropriate data

int count_letters(string x)
{
    int letters = 0;
    for (int i = 0; i < strlen(x); i++)
    {

        if ((x[i] >= 'a' && x[i] <= 'z') || (x[i] >= 'A' && x[i] <= 'Z'))

        letters++;

    }

    return letters;
}

int count_words(string x)
{
    int words = 0;
    for (int i = 0; i < strlen(x); i++)
    {
        if (x[i] == ' ')

        words++;

    }

    return words + 1;
}

int count_sent(string x)
{
    int sent = 0;
    for (int i = 0; i < strlen(x); i++)
    {
        if (x[i] == '.' || x[i] == '?' || x[i] == '!')

        sent++;

    }

    return sent;
}

