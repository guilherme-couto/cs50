// Implements a dictionary's functionality
#include <stdio.h>
#include <strings.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 100000;

// Hash table
node *table[N];

// função para inicializar a hash table
void clean_table(void)
{
    for (int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }
}

// Número de palavras
unsigned int num;



// Returns true if word is in dictionary else false
unsigned int word_hash(const char *word);

bool check(const char *word)
{
    node *cursor = table[word_hash(word)];

    while (cursor != NULL)
    {
        if (strcasecmp(word, cursor->word) == 0) // ALGUMA COISA AQUI
        {
            return true;
        }
        else
        {
            cursor = cursor->next;
        }
    }

    return false;
}

unsigned int word_hash(const char *word)
{
    char *s = malloc(sizeof(char) * (strlen(word) + 1));
    for (int i = 0; i <= strlen(word); i++)
    {
        s[i] = tolower(word[i]);
    }
    s[strlen(word) + 1] = '\0';
    unsigned int nhash = hash(s);
    free(s);
    return nhash;
}



// Hashes word to a number
unsigned int hash(const char *word)
{

    //source: code from dasblinkenlight (https://stackoverflow.com/questions/20462826/hash-function-for-strings-in-c)

    unsigned int hash = 0;
    for (int i = 0 ; word[i] != '\0' ; i++)
    {
        hash = 31 * hash + word[i];
    }
    return hash % N;
}



// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // open dictionary
    FILE *dicio = fopen(dictionary, "r");

    num = 0;

    // check if file can be open
    if (dicio == NULL)
    {
        return false;
    }

    // read word from dic and put into a node
    // first word
    char word[LENGTH + 1];
    clean_table();

    while (fscanf(dicio, "%s", word) != EOF)
    {
        num ++; //counting how many words are loaded

        node *n = malloc(sizeof(node));

        if (n == NULL)
        {
            return false;
        }

        // atualizar node
        strcpy(n->word, word);

        // hash code
        // insert node into hash table using the hash code
        n->next = table[hash(word)];
        table[hash(word)] = n;

        // ler a próxima palavra
    }

    fclose(dicio);
    return true;
}



// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return num;
}



// Unloads dictionary from memory, returning true if successful else false
void destroy(node *t);

bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        destroy(table[i]);
    }
    return true;
}

void destroy(node *t)
{
    node *cursor = t;

    if (cursor != NULL)
    {
        destroy(cursor->next);
        free(cursor);
    }

}