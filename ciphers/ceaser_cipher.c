#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// TODO: make it with files so it can work with bigger data
char *encypher(char *data, int shift)
{
    char *result = malloc(sizeof(char) * strlen(data));

    for (int i = 0; i < strlen(data); i++)
    {
        if (data[i] >= 'A' && data[i] <= 'Z')
        {
            if (data[i] + shift > 'Z') // if it goes over the alphabet start from the beginning
                result[i] = data[i] + shift - ('Z' - 'A') - 1;
            else
                result[i] = data[i] + shift;
        }
        else if (data[i] >= 'a' && data[i] <= 'z')
        {
            if (data[i] + shift > 'z')
                result[i] = data[i] + shift - ('z' - 'a') - 1;
            else
                result[i] = data[i] + shift;
        }
        else
            result[i] = data[i];
    }

    return result;
}

// void brute_force(char *encrypted)
// {
//     printf("\nDecrypting...\n");
//     for (int i = 1; i < 25; i++)
//     {
//         char *decrypted = decypher(encrypted, i);
//         printf("%d: %s\n", i, decrypted);
//     }
// }

int main()
{
    // char *encrypted = encypher("hello", 10);
    // printf("Encrypted: %s\n", encrypted);

    // char *decrypted = decrypt("hello", 10);
    // printf("Decrypted: %s\n", decrypted);

    char *text = "The quick brown fox jumps over the lazy dog.";
    char *encrypted = encypher(text, 7);
    printf("Result: %s\n", encrypted);
    // brute_force(encrypted);

    return 0;
}
