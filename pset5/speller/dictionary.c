// Implements a dictionary's functionality

#include <stdbool.h>
#include <string.h>
#include <strings.h>
#include <stdio.h>
#include <stdlib.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = LENGTH;

// Hash table
node *table[N];

void destroy(node *list);
int wordcount = 0;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    int h_value = hash(word);

    node *trav = table[h_value];

    while (trav != NULL)
    {
        if (strcasecmp(trav->word, word) == 0)
            return true;
        else
            trav = trav->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    int h_value = strlen(word);
    return h_value;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    FILE *dic = fopen(dictionary, "r");
    if (dic == NULL)
        return false;

    char new_word[LENGTH + 1];

    while (fscanf(dic, "%s", new_word) != EOF)
    {
        //malloc space for word
        node *n = malloc(sizeof(node));
        if (n == NULL)
            return false;

        //Assign word to n
        strcpy(n->word, new_word);
        n->next = NULL;

        //Hash word
        int h_value = hash(n->word);

        //Insert into table
        if (table[h_value] == NULL)
        {
            table[h_value] = n;
            wordcount++;
        }
        else
        {
            n->next = table[h_value];
            table[h_value] = n;
            wordcount++;
        }
    }
    if (fscanf(dic, "%s", new_word) == EOF)
    {
        fclose(dic);
        return true;
    }
    else
        return false;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return (wordcount);
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        destroy(table[i]);
    }
    return true;
}

void destroy(node *list)
{
    if (list == NULL)
        return;
    destroy(list->next);
    free(list);
}
