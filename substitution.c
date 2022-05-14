//https://en.wikipedia.org/wiki/Substitution_cipher

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *input_array = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890 ";
char *mixed_array = "ViDRKj1dCef2vQLw3FY SabcgEBhZk5x4yMz6WJlTmG7nNo8pqU9XrHOAst0IuP";

void swap(char *a, char *b)
{
    char temp = *a;
    *a = *b;
    *b = temp;
}
char *generate_char_array(int iterations)
{
    srand(time(0));  

    char *result = malloc(sizeof(char) * strlen(input_array));
    strcpy(result, input_array);

    for (; iterations > 0; iterations--)
        swap(&result[rand() % strlen(result)], &result[rand() % strlen(result)]);

    return result;
}

char *encypher(char *data)
{
    char *result = malloc(sizeof(char) * strlen(data));

    for (int i = 0; i < strlen(data); i++)
    {
        int j = 0;
        while (input_array[j] != data[i])
            j++;

        result[i] = mixed_array[j];
    }

    return result;
}

char *decypher(char *data)
{
    char *result = malloc(sizeof(char) * strlen(data));

    for (int i = 0; i < strlen(data); i++)
    {
        int j = 0;
        while (mixed_array[j] != data[i])
            j++;
        result[i] = input_array[j];
    }

    return result;
}

int main()
{
    mixed_array = generate_char_array(100);
    printf("Character array: %s\nMixed array: %s\n\n",input_array,mixed_array);

    char *data = "hello worldz";

    char *encrypted = encypher(data);
    printf("%s\n", encrypted);

    char *decrypted = decypher(encrypted);
    printf("%s\n", decrypted);

    return 0;
}
