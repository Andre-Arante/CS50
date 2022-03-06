// Implements a dictionary's functionality

#include <string.h>
#include <strings.h>
#include <ctype.h>
#include <stdbool.h>
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

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// count size
int count_size = 0;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    int idx = hash(word);
    node *cursor = table[idx];

    while (cursor != NULL) {

        // check for word
        if(strcasecmp(word, cursor->word) == 0) {
            return true;
        }

        // if not found move on
        cursor = cursor->next;
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    //convert first letter to ASCII value between 0 and 25
    return (int) (toupper(word[0]) - 65);
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO: Open the dictionary file
    FILE *file = fopen(dictionary, "r");
    if (file == NULL) {
        return false;
    }

    // TODO: Read strings from file with scanf(file, "%s", word)
    // returns EOF once reaches the end of file
    char word[LENGTH + 1];
    while (fscanf(file, "%s", word) != EOF) {

        // create a new node
        node *n = malloc(sizeof(node));
        if (n == NULL) {
            return false;
        }

        // copy word to the new node
        strcpy(n->word, word);
        n->next = NULL;

        // generate hash and insert into the hash table
        int idx = hash(word);

        // if first node
        if (table[idx] == NULL) {
            table[idx] = n;
        }
        else {
            n->next = table[idx];
            table[idx] = n;
        }

        // clean up
        count_size++;
    }

    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return count_size;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // iterate through each bucket
    for (int i = 0; i < N; i++) {

        while (table[i] != NULL) {
            node *temp = table[i]->next;
            free(table[i]);
            table[i] = temp;
        }

    }

    return true;
}
