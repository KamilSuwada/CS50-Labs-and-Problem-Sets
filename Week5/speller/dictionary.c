// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char value[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 30000; // 30'000 seems enough for the large problem set
//to match speller50 execution time. Not much gain after further increase...

// Hash table
node *table[N];

// Number of items in dict.
int dictionary_size = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    int key = hash(word); // get hash for the word
    node *n = table[key]; // tap into the box for that hash

    while (n != NULL) // until there is no nodes in the box...
    {
        // strcasecmp comes from strings.h
        if (strcasecmp(n->value, word) == 0) // check if the word given is equal the one in dictionary...
        {
            return true; // if so, true
        }
        n = n->next; // otherwise, got to next node
    }

    return false; // no matches; false is returned.
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    int value = 11; // initial value of the hash
    for (int i = 0; i < strlen(word); i++) // go through every char
    {
        value = value * 5 + tolower(word[i]) * 3; // generate hash increment
    }
    return value % N; // return modulus of hash by N, to make sure it fits in the table.
    // got inspired to use prime numbers and modulus from: https://stackoverflow.com/a/2624210
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *f = fopen(dictionary, "r");

    if (f == NULL)
    {
        //printf("Could not allocate memory for file...\n");
        return false;
    }

    // create a word buffer:
    char buffer[LENGTH + 1];

    // read each word from file
    while (fscanf(f, "%s", buffer) != EOF)
    {
        // allocate memory for next node and null check it:
        node *n = malloc(sizeof(node));

        if (n == NULL)
        {
            //printf("Could not allocate memory for node...\n");
            return false;
        }

        // copy string from the read word to the buffer"
        strcpy(n->value, buffer);

        // get hash value:
        int hash_val = hash(n->value);

        // leave crumbs to the next value:
        n->next = table[hash_val];

        // insert current at hash:
        table[hash_val] = n;

        // account for this word in count:
        dictionary_size += 1;
    }

    // closing the file.
    fclose(f);

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return dictionary_size;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++) // iterate through every box
    {
        node *n = table[i]; // get the node in the box
        while (n != NULL) // until all nodes in the box are gone...
        {
            node *temp = n; // make a copy of the pointer to the first node in list
            n = n->next; // assign next pointer as first (current)
            free(temp); // free original first
        }

        if (i + 1 == N) // if reached end of box
        {
            return true; // return true.
        }
    }

    return false; // something is wrong, return false!
}
