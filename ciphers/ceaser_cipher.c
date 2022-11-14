#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *encypher(char *data, int shift)
{
    char *result = malloc(sizeof(char) * strlen(data));

    for (int i = 0; i < strlen(data); i++)
    {
        if (data[i] < 'a' || data[i] > 'z')
            result[i] = data[i];
        else if (data[i] < 'z' - shift)
            result[i] = data[i] + shift;
        else
            result[i] = data[i] - ('z' - 'a') + shift;
    }

    return result;
}

char *decypher(char *data, int shift)
{
    char *result = malloc(sizeof(char) * strlen(data));

    for (int i = 0; i < strlen(data); i++)
    {
        if (data[i] < 'a' || data[i] > 'z')
            result[i] = data[i];
        else if (data[i] - shift > 'a')
            result[i] = data[i] - shift;
        else
            result[i] = data[i] + ('z' - 'a') - shift;
    }

    return result;
}

void brute_force(char *encrypted)
{
    printf("\nDecrypting...\n");
    for (int i = 1; i < 25; i++)
    {
        char *decrypted = decypher(encrypted, i);
        printf("%d: %s\n", i, decrypted);
    }
}

int main()
{
    char *encrypted = encypher("hello", 10);
    printf("Encrypted: %s\n", encrypted);
    
    char *decrypted = decrypt("hello", 10);
    printf("Decrypted: %s\n", decrypted);
    
    brute_force(encrypted);
    return 0;
}
