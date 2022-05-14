// https://www.boxentriq.com/code-breaking/rail-fence-cipher
// https://crypto.interactive-maths.com/rail-fence-cipher.html

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
void print_table(char *table, int width, int height)
{
    char *result = malloc(width + 1);
    for (int row = 0; row < height; row++)
    {
        for (int column = 0; column < width; column++)
        {
            if (table[row * width + column] == 0)
                printf(" ");
            else
                printf("%c", table[row * width + column]);
        }
        printf("\n");
    }
}
char *encrypt(char *data, int height)
{
    int width = strlen(data);

    // generate table
    int size = width * height * sizeof(char);
    char *table = malloc(size);
    memset(table, 0, size);

    for (int row = 0, column = 0, direction = 1; column < width; column++)
    {
        table[row * width + column] = data[column];
        row += direction;
        if (row >= height - 1 || row <= 0)
            direction *= -1;
    }

    // print_table(table, width, height);

    char *result = malloc(width + 1);
    for (int row = 0, result_index = 0; row < height; row++)
    {
        for (int column = 0; column < width; column++)
        {
            if (table[row * width + column] != 0)
            {
                result[result_index] = table[row * width + column];
                result_index++;
            }
        }
    }

    result[strlen(result)] = 0;
    free(table);
    return result;
}

char *decrypt(char *data, int height)
{
    int width = strlen(data);

    int size = width * height * sizeof(char);
    char *table = malloc(size);
    memset(table, 0, size);

    for (int row = 0, data_index = 0; row < height; row++)
    {
        int gap1 = (height - row) * 2 - 2, gap2 = (row + 1) * 2 - 2;
        if (gap1 == 0)
            gap1 = gap2;
        else if (gap2 == 0)
            gap2 = gap1;

        for (int column = row; column < width; column += gap1, swap(&gap1, &gap2))
        {
            table[row * width + column] = data[data_index];
            data_index++;
        }
    }

    // print_table(table, width, height);

    char *result = malloc(width + 1);
    for (int row = 0, column = 0, direction = 1, result_index = 0; column < width; column++)
    {
        result[result_index] = table[row * width + column];
        result_index++;

        row += direction;
        if (row >= height - 1 || row <= 0)
            direction *= -1;
    }

    free(table);
    return result;
}

void brute_force(char *data)
{
    for (int i = 2; i < strlen(data)+1; i++)
    {
        char *decrypted = decrypt(data, i);
        printf("Rail %d: %s\n", i, decrypted);
    }
}

int main()
{
    int rails = 5; // >=2
    char *data = "HELLOFROMBULGARIA";

    char *encrypted = encrypt(data, rails);
    printf("Encrypted: %s\n", encrypted);
    
    char *decrypted = decrypt(encrypted, rails);
    printf("Decrypted: %s\n\n", decrypted);

    brute_force(encrypted);

    return 0;
}
