#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

string encrypt(string plaintext, int key);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    int key = atoi(argv[1]);

    string plaintext = get_string("plaintext: ");

    string ciphertext = encrypt(plaintext, key);

    printf("ciphertext: %s\n", ciphertext);
}

string encrypt(string plaintext, int key)
{
    for (int i = 0, n = strlen(plaintext); i < n; i++)
    {
        char c = plaintext[i];

        if (isupper(c))
        {
            plaintext[i] = ((c - 'A' + key) % 26) + 'A';
        }
        else if (islower(c))
        {
            plaintext[i] = ((c - 'a' + key) % 26) + 'a';
        }
    }

    return plaintext;
}
