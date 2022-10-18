#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>


bool validate_key(string key);


int main(int argc, string argv[])
{
    // Checks for input:

    if (argc != 2) // must be exactly one argument.
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }


    string key = argv[1]; // assignement of the key.


    if (strlen(key) != 26) // key must be exactly 26 chars long.
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }


    if (validate_key(key) == 0) // key validation...
    {
        printf("Invalid key.\n");
        return 1;
    }


    string plain = get_string("plaintext: ");


    int key_mapping[26]; // mapping of the chars to ASCII, relative to a or A.


    for (int i = 0; i < strlen(key); i++) // generation of the mapping...
    {
        char c = key[i];
        int index;

        if (islower(c) > 0) // lowercase, index will be int in ASCII of the char - 97.
        {
            index = (int)c - 97;
        }
        else // uppercase, index will be int in ASCII of the char - 65.
        {
            index = (int)c - 65;
        }

        key_mapping[i] = index - i;
    }


    char coded[strlen(plain)];


    for (int i = 0; i < strlen(plain); i++) // coding of the plain text
    {
        char c = plain[i];
        int index;

        if (islower(c) > 0) // lowercase, index will be int in ASCII of the char - 97.
        {
            index = (int)c - 97;
        }
        else // uppercase, index will be int in ASCII of the char - 65.
        {
            index = (int)c - 65;
        }

        if (index >= 0 && index <= 26) // Only indexes between 0 and 26 inclusive are allowed to be changed.
        {
            int new_index = (int)c + key_mapping[index];
            char new_char = (char) new_index;
            coded[i] = new_char;
        }
        else
        {
            coded[i] = c;
        }
    }

    printf("ciphertext: ");

    for (int i = 0; i < strlen(plain); i++)
    {
        printf("%c", coded[i]);
    }

    printf("\n");
}



bool validate_key(string key)
{
    for (int i = 0; i < strlen(key); i++) // loop through key...
    {
        char c = key[i];
        int j = (int)c;
        int index;

        if (islower(c) > 0) // lowercase, index will be int in ASCII of the char - 97.
        {
            index = j - 97;
        }
        else // uppercase, index will be int in ASCII of the char - 65.
        {
            index = j - 65;
        }

        if (index < 0 || index > 26) // Only indexes between 0 and 26 inclusive are allowed to score.
        {
            return false;
        }
    }


    for (int i = 0; i < strlen(key); i++)
    {
        for (int j = 0; j < strlen(key); j++)
        {
            if (i != j)
            {
                if (key[i] == key[j])
                {
                    return false;
                }
            }
        }
    }


    return true;
}