// Implements a dictionary's functionality

#include <stdbool.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = (LENGTH + 1) * 'z';

// Hash table
node *table[N];
int total = 0;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // KETVIRTA
    int h = hash(word);

    node *cursor = table[h];

    while (cursor != NULL)
    {
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }

        cursor = cursor->next;
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // ANTRA

    int count = 0;
    for (int i = 0; i < strlen(word); i++)
    {
        count += tolower(word[i]);
    }

    return (count % N);
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // PIRMA
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }

    char word[LENGTH + 1];

    while (fscanf(file, "%s", word) != EOF)
    {
        node *n_node = malloc(sizeof(node));

        if (n_node == NULL)
        {
            return false;
        }

        strcpy(n_node->word, word);
        n_node->next = NULL;

        int index = hash(word);

        if (table[index] == NULL)
        {
            table[index] = n_node;
            total++;
        }
        else
        {
            n_node->next = table[index];
            table[index] = n_node;
            total++;
        }

    }
    fclose(file);
    return true;

}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // TRECIA
    return total;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // PENKTA

    for (int i = 0; i < N; i++)
    {
        node *head = table[i];
        node *cursor = head;
        node *tmp = head;

        while(cursor != NULL)
        {
            cursor = cursor->next;
            free(tmp);
            tmp = cursor;
        }
    }

    return true;
}
