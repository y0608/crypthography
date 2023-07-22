#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int main()
{
    char *input = "the quick brown fox jumps over the lazy dog";
    int input_len = strlen(input);
    
    char *key = "cryptii";
    int key_pos = 0;
    int key_len = strlen(key);

    char *result = malloc(input_len);

    for (int i = 0; i < input_len; i++)
    {
        if(input[i] == ' ')
        {
            result[i] = ' ';
            continue;
        }

        result[i] = (input[i] - 'a' + key[key_pos] - 'a') % 26 + 'a';

        key_pos++;
        if(key_pos >= key_len)
            key_pos = 0;
    }

    printf("%s\n",result);

    return 0;
}