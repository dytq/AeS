#include <stdio.h>
#include "cypher.h"
#include "decypher.h"

unsigned char MESSAGE[TAB_SIZE] = 
{ 
	0x32, 0x88, 0x31, 0xe0,
	0x43, 0x5A, 0x31, 0x37,
	0xF6, 0x30, 0x98, 0x07,
	0xA8, 0x8D, 0XA2, 0x34
};

unsigned char K_0[TAB_SIZE] = 
{
	0x2B, 0x28, 0xAB, 0x09,
	0x7E, 0xAE, 0xF7, 0xCF,
	0x15, 0xD2, 0x15, 0x4F,
	0x16, 0XA6, 0x88, 0x3C
};

// Key generation
unsigned char * key_gen(unsigned char * k, unsigned char * k_i, int index_k)
{
	// ROT WORD
	k_i[COLUMN[0][0]] = k[COLUMN[3][1]];
	k_i[COLUMN[0][1]] = k[COLUMN[3][2]];
	k_i[COLUMN[0][2]] = k[COLUMN[3][3]];
	k_i[COLUMN[0][3]] = k[COLUMN[3][0]];
	
	// SUB Byte
	k_i = sub_byte_column(k_i, 0);

	// xor column 
	k_i[COLUMN[0][0]] ^= k[COLUMN[0][0]] ^ RCON[index_k][0];
	k_i[COLUMN[0][1]] ^= k[COLUMN[0][1]] ^ RCON[index_k][1];
	k_i[COLUMN[0][2]] ^= k[COLUMN[0][2]] ^ RCON[index_k][2];
	k_i[COLUMN[0][3]] ^= k[COLUMN[0][3]] ^ RCON[index_k][3];
		
	for(int i = 1; i < 4; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			k_i[COLUMN[i][j]] = k[COLUMN[i][j]] ^ k_i[COLUMN[i-1][j]];
		}
	}

	return k_i;
}

int main()
{
	unsigned char * s_table = MESSAGE; 
	
	printf("MESSAGE: \n");
	print_table(s_table, TAB_SIZE, 4);

	unsigned char k_table[11][TAB_SIZE]; 
	unsigned char * k_ptr_i[11];

	for(int i = 0; i < 11; i++)
	{
		k_ptr_i[i] = k_table[i];
	}
	
	k_ptr_i[0] = K_0;
	k_ptr_i[1] = key_gen(K_0, k_ptr_i[1], 0);
	
	for(int i = 2; i < 11; i++)
	{
		k_ptr_i[i] = key_gen(k_ptr_i[i-1], k_ptr_i[i], i-1);
	}

	printf("KEYS K:\n");
	for(int i = 0; i < 11; i++)
	{
		printf("K_%d\n",i);
		print_table(k_ptr_i[i], TAB_SIZE, 4);
	}
	
	cypher_message(s_table, k_ptr_i, 1);
	decypher_message(s_table, k_ptr_i, 1);
	
	return 0;
}
