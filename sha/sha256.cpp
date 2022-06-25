#include <iostream>
#include <string>
#include <stdint-gcc.h>
#include <string.h>
#include <byteswap.h>
using namespace std;

/*CONSTANTS*/
unsigned int constants[64] = {0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
                              0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
                              0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
                              0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
                              0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
                              0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
                              0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
                              0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2};

/*OPERATIONS*/
#define ROTLEFT(a, b) (((a) << (b)) | ((a) >> (32 - (b))))
#define ROTRIGHT(a, b) (((a) >> (b)) | ((a) << (32 - (b))))
#define CH(x, y, z) (((x) & (y)) ^ (~(x) & (z)))
#define MAJ(x, y, z) (((x) & (y)) ^ ((x) & (z)) ^ ((y) & (z)))
#define s0(x) (ROTRIGHT(x, 7) ^ ROTRIGHT(x, 18) ^ ((x) >> 3))
#define s1(x) (ROTRIGHT(x, 17) ^ ROTRIGHT(x, 19) ^ ((x) >> 10))
#define S0(x) (ROTRIGHT(x, 2) ^ ROTRIGHT(x, 13) ^ ROTRIGHT(x, 22))
#define S1(x) (ROTRIGHT(x, 6) ^ ROTRIGHT(x, 11) ^ ROTRIGHT(x, 25))

void print_binary_number(uint8_t n)
{
    for (int i = 0; i < 8; i++)
    {
        if (n & 1)
            cout << 1;
        else
            cout << 0;
        n>>=1;
    }
    cout << "-";
}
void print_binary_number(uint64_t n)
{
    for (int i = 0; i < 64; i++)
    {
        if (n & 1)
            cout << 1;
        else
            cout << 0;
        n>>=1;
    }
    cout << "-";
}
void print(uint8_t *input, int size)
{
    for (int i = 0; i < size; i++)
    {
        print_binary_number(*input);
        input++;
    }
    cout << endl;
}

//TODO: little and big endian
int main()
{
    char *input = "abc";

    uint64_t length = strlen(input);
    int curr_block_length = 0;

    // 512 bits(64 bytes) blocks
    // 448 bits(56 bytes) of info and 64(8 bytes) for length of message
    cout << "Lenth: " << length << endl;
    if (length < 56)
    {
        uint8_t block[64] = {0};
        for (int i = 0; i < length; i++)
            block[i] = input[i];

        curr_block_length += length;
        print(block, curr_block_length);

        // add 1 and padd with 0s until 56 bytes
        block[curr_block_length] = 128;
        curr_block_length++;
        print(block, curr_block_length);

        curr_block_length = 56;
        print(block, curr_block_length);

        // after that add 8 bytes of length of bits

        block[curr_block_length] = length * 8;
        curr_block_length = 64;
        print_binary_number(length * 8);
        // print(block, curr_block_length);
    }
}