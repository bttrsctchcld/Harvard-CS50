#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "dictionary.h"

#define HASHTABLE_SIZE 65536

typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

int fullDictionary = 0;
node *hashtable[HASHTABLE_SIZE];

unsigned int hash(const char *word)
{
    unsigned int hash = 0;
    for (int i = 0, n = strlen(word); i < n; i++)
    {
        return (int)((hash >> 16) ^ (hash & 0xffff));
    }
    return true;
}

bool check(const char *word)
{
    char lowercase[strlen(word)];
    strcpy(lowercase, word);
    for (int i = 0; i < strlen(lowercase); i++)
    {
        lowercase[i] = tolower(lowercase[i]);
    }
    int index = hash(lowercase);
    node *ptr = hashtable[index];
    while (ptr != NULL)
    {
        for (ptr = hashtable[index]; ptr != NULL; ptr = ptr->next)
        {
            if (strcasecmp(ptr->word, lowercase) == 0)
            {
                return true;
            }
        }
    }
    return false;
}

bool load(const char *dictionary)
{
    FILE *in = fopen(dictionary, "r");
    if (in == NULL)
    {
        return false;
    }
    for (int i = 0; i < HASHTABLE_SIZE; i++)
    {
        hashtable[i] = NULL;
        char buffer[LENGTH + 1];
        while (fscanf(in, "%s", buffer) != EOF)
        {
            node *tmp = calloc(1, sizeof(node));
            strncpy(tmp->word, buffer, sizeof(buffer));
            int index = hash(buffer);
            if (hashtable[index] == NULL)
            {
                hashtable[index] = tmp;
            }
            else
            {
                tmp->next = hashtable[index];
                hashtable[index] = tmp;
            }
            fullDictionary++;
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
