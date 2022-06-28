#include <iostream>
#include <string>
#include <stdint-gcc.h>
#include <string.h>
#include <byteswap.h>
#include "hash.h"
using namespace std;

void print_binary_number(uint8_t n)
{
    for (int i = 0; i < 8; i++)
    {
        if (n & 0x80)
            cout << 1;
        else
            cout << 0;
        n <<= 1;
    }
    cout << "-";
}
void print_binary_number32(uint32_t n)
{
    for (int i = 0; i < 32; i++)
    {
        if (i % 8 == 0)
            cout << ":";
        if (n & 0x80000000)
            cout << 1;
        else
            cout << 0;
        n <<= 1;
    }
    cout << "-";
}

void print(uint8_t *input, int size)
{
    for (int i = 0; i < size; i++)
        print_binary_number(input[i]);
    cout << endl;
}

int main()
{
    char a[] = "abc";
    char *input = a;

    uint64_t length = strlen(input);
    int curr_block_length = 0;

    uint32_t initial_hash[] = {0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a, 0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19};

    // 512 bits(64 bytes) blocks
    // 448 bits(56 bytes) of info and 64(8 bytes) for length of message

    // cout << "Lenth: " << length << endl;
    if (length < 56)
    {
        uint8_t block[64] = {0};
        for (int i = 0; i < length; i++)
        {
            block[i] = input[i];
        }

        curr_block_length += length;
        // cout << "ASCII to binary: " << endl;
        // print(block, curr_block_length);

        // cout << "Add 1 between msg and padded 0s: " << endl;
        block[curr_block_length] = 128;
        curr_block_length++;
        // print(block, curr_block_length);

        // cout << "Padd with 0s until 56 bytes: " << endl;
        curr_block_length = 56;
        // print(block, curr_block_length);

        // cout << "after that add 8 bytes of length of bits: << endl;
        int bit_length = length * 8;
        curr_block_length = 63;
        for (int i = 0; i < 8; i++)
        {
            block[curr_block_length - i] = bit_length & 255;
            bit_length >>= 8;
        }
        curr_block_length = 64;
        // print(block, curr_block_length);
        // cout << endl;

        // create message_scheudle and add first 16 32bits to it
        uint32_t msg_schedule[64];
        uint32_t current = 0;

        int msg_schedule_index = 0;
        for (int i = 0; i < 64; i += 4)
        {
            for (int j = 0; j < 3; j++)
            {
                current |= block[i + j];
                current <<= 8;
            }
            current |= block[i + 3];

            msg_schedule[msg_schedule_index] = current;
            // cout << endl
            //      << msg_schedule_index << ": ";

            // print_binary_number32(msg_schedule[msg_schedule_index]);

            msg_schedule_index++;
            current = 0;
        }
        // msg_schedule_index is now 16

        // continue making the message schedule
        for (; msg_schedule_index < 64; msg_schedule_index++)
        {
            // cout << endl
            //      << msg_schedule_index << ": ";
            msg_schedule[msg_schedule_index] = s1(msg_schedule[msg_schedule_index - 2]) + msg_schedule[msg_schedule_index - 7] + s0(msg_schedule[msg_schedule_index - 15]) + msg_schedule[msg_schedule_index - 16];
            // print_binary_number32(msg_schedule[msg_schedule_index]);
        }

        // compression:

        // copy initial hash
        uint32_t state_registers[8];
        for (int i = 0; i < 8; i++)
            state_registers[i] = initial_hash[i];

        // traverse every word from schedule
        for (int i = 0; i < 64; i++)
        {
            // calculate temprary varaibles
            uint32_t tmp1 = S1(state_registers[4]) + CH(state_registers[4], state_registers[5], state_registers[6]) + state_registers[7] + constants[i] + msg_schedule[i],
                     tmp2 = S0(state_registers[0]) + MAJ(state_registers[0], state_registers[1], state_registers[2]);
            // print_binary_number32(tmp1);
            // cout << endl;
            // print_binary_number32(tmp2);
            // cout << endl;

            // move everything down
            state_registers[7] = state_registers[6];
            state_registers[6] = state_registers[5];
            state_registers[5] = state_registers[4];
            state_registers[4] = state_registers[3];
            state_registers[3] = state_registers[2];
            state_registers[2] = state_registers[1];
            state_registers[1] = state_registers[0];

            state_registers[0] = tmp1 + tmp2;

            state_registers[4] += tmp1;
        }

        for (int i = 0; i < 8; i++)
        {
            print_binary_number32(state_registers[i]);
            cout << endl;
        }

        // combine state registers and initial hash
        for (int i = 0; i < 8; i++)
            state_registers[i] += initial_hash[i];

        // print
        for (int i = 0; i < 8; i++)
            cout << hex << state_registers[i];
        cout << endl;
    }
}