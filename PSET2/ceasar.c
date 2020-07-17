#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
    if (argc == 2 && isdigit(*argv[1]))
    {
        int key = atoi(argv[1]);
        string plaintext = get_string("plaintext: ");
        printf("ciphertext: ");
        for (int r = 0, n = strlen(plaintext); r < n; r++)
        {
            if (plaintext[r] >= 'a' && plaintext[r] <= 'z')
            {
                printf("%c", (((plaintext[r] - 'a') + key) % 26) + 'a');
            }
            else if (plaintext[r] >= 'A' && plaintext[r] <= 'Z')
            {
                printf("%c", (((plaintext[r] - 'A') + key) % 26) + 'A');
            }
            else
            {
                printf("%c", plaintext[r]);
            }
        }
        printf("\n");
        return 0;
    }
    else if (argc != 2)
    {
        printf("Please use a single key.\n");
        return 1;
    }
    else
    {
        printf("Please use a single, non-negative integer.\n");
        return 1;
    }
}