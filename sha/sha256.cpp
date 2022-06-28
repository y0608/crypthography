#include <iostream>
#include <string>
#include <cstring>
#include <stdint-gcc.h>
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
	uint32_t initial_hash[] = {0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a, 0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19};

	// char input[] = "abc";
	char input[] = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
	uint64_t input_length = strlen(input);
	// cout << input_length << endl;

	// 448 bits(56 bytes) of info and 64(8 bytes) for length of message in the last block
	int number_of_blocks = (input_length + 8) / 64 + 1;
	// cout << number_of_blocks << endl;

	for (int block_number = 0; block_number < number_of_blocks; block_number++)
	{
		int end_of_block = block_number * 64 + 64;

		// Copy input into block
		uint8_t block[64] = {0};
		for (int input_index = end_of_block - 64, block_index = 0;
			 input_index < end_of_block && input_index < input_length;
			 input_index++, block_index++)
			block[block_index] = input[input_index];

		// Last block
		if (block_number == number_of_blocks - 1)
		{
			// Add 1 between msg and padded 0s
			block[input_length % 64] = 128;
			// TODO: check if it is needed to pad

			//  Padd with 0s until 56th byte - already padded because block is full of 0s at the start

			// Add the length of the message in the last 64 bits(8 bytes)
			int bit_length = input_length * 8;
			for (int i = 0; i < 8; i++)
			{
				block[63 - i] = bit_length & 255; // 0b11111111
				bit_length >>= 8;
			}
		}

		// CREATE MESSAGE SCHEUDLE:
		uint32_t msg_schedule[64];
		uint32_t current_word = 0;

		// Add the first 16 values from block
		int msg_schedule_index = 0;
		for (int i = 0; i < 64; i += 4)
		{
			// block is uint8 and msg_schedule is uint32
			// put 4 bytes from block to one msg_schedule
			for (int j = 0; j < 3; j++)
			{
				current_word |= block[i + j];
				current_word <<= 8;
			}
			// no need to <<= 8
			current_word |= block[i + 3];

			msg_schedule[msg_schedule_index] = current_word;
			// cout << endl
			//      << msg_schedule_index << ": ";

			// print_binary_number32(msg_schedule[msg_schedule_index]);

			msg_schedule_index++;
			current_word = 0;
		}
		// msg_schedule_index is now 16

		// Continue making the message schedule
		for (; msg_schedule_index < 64; msg_schedule_index++)
		{
			// cout << endl
			//      << msg_schedule_index << ": ";
			msg_schedule[msg_schedule_index] = s1(msg_schedule[msg_schedule_index - 2]) + msg_schedule[msg_schedule_index - 7] + s0(msg_schedule[msg_schedule_index - 15]) + msg_schedule[msg_schedule_index - 16];
			// print_binary_number32(msg_schedule[msg_schedule_index]);
		}

		// COPMRESSION:

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

		// UPDATE STATE REGISTERS
		for (int i = 0; i < 8; i++)
		{
			// combine state registers and initial hash
			state_registers[i] += initial_hash[i];
			// update initial_hash
			initial_hash[i] = state_registers[i];
		}

		print(block, 64);
		cout << "\n\n";
	}

	// print
	for (int i = 0; i < 8; i++)
		cout << hex << initial_hash[i];
	cout << endl;
}