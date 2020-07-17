#include <stdbool.h>
#include <stdio.h>
#include <strings.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "dictionary.h"

#define HASHTABLE_SIZE 65536

// remember, ptrs are initialized independently, 'check' and 'load' will each require you to create one or more ptrs to iterate through linked list (ptr->next)
typedef struct node
{
    char word[LENGTH + 1]; // implemented in 'hash', 'check', 'load', 'size'
    struct node *next; // implemented in 'check' and 'load'
}
node;

int fullDictionary = 0; // set global counter to zero, incremented in 'load' function, called in 'size' function
node *hashtable[HASHTABLE_SIZE]; // declare hashtable at size 2^16, called in 'load' function

unsigned int hash(const char *word) // function takes constant char 'word', returns unsigned int 'hash'
{
    unsigned int hash = 0; // initialize hash to zero
    for (int i = 0, n = strlen(word); i < n; i++)
    {
        return (int)((hash >> 16) ^ (hash & 0xffff)); // hash return from cs50x staff delipity; obscure hash signature & minimize collisons
    }
    return true;
}

bool check(const char *word)
{
    char lowercase[strlen(word)]; // hash & check need to use lowercase as reference point for all hash values and string comparisons
    strcpy(lowercase, word);
    for (int i = 0; i < strlen(lowercase); i++) // iterate through each word to convert lowercase
    {
        lowercase[i] = tolower(lowercase[i]); // check implementation seems easier than hash implementation in re lowercase
    }
    int index = hash(lowercase); // begin to restructure arbitary hash values into a coherent hashtable index via linked list
    node *ptr = hashtable[index]; // in ith iteration, ptr refers to ith index in the hash table
    while (ptr != NULL) // ensures ptr will only return NULL at EOF
    {
        for (ptr = hashtable[index]; ptr != NULL; ptr = ptr->next) // iterate ptr through hashtable until ptr reaches NULL
        {
            if (strcasecmp(ptr->word, lowercase) == 0)
            {
                return true;
            }
        }
    }
    return false; // implicit NULL
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    FILE *in = fopen(dictionary, "r"); // verbatim from week5 lecture notes
    if (in == NULL)
    {
        return false;
    }
    for (int i = 0; i < HASHTABLE_SIZE; i++) // iterate through the hashtable
    {
        hashtable[i] = NULL; // initialize at NULL
        char buffer[LENGTH + 1]; // each word needs room for max char count plus NULL terminator
        while (fscanf(in, "%s", buffer) != EOF) // iterate through the dictionary until EOF]
        {
            node *tmp = calloc(1, sizeof(node)); // initialize the cursor
            strncpy(tmp->word, buffer, sizeof(buffer)); // copy words into buffer
            int index = hash(buffer); // export hash values
            if (hashtable[index] == NULL)
            {
                hashtable[index] = tmp; // ptr continuity
            }
            else
            {
                tmp->next = hashtable[index];
                hashtable[index] = tmp;
            }
            fullDictionary++; // increment the global counter within the while (fscanf) loop but outside of the linked list cursor iteration
        }
    }
    fclose(in);
    return true;
}

unsigned int size(void)
{
    return fullDictionary;
}

bool unload(void)
{
    for (int i = 0; i < HASHTABLE_SIZE; i++)
    {
        node* ptr;
        ptr = hashtable[i];
        node* tmp = NULL;
        while (ptr != NULL)
        {
            tmp = ptr;
            ptr = ptr->next;
        }
        free(tmp);
    }
    return true;
}