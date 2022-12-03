#include <stdio.h>
#include "decypher.h"

//	4. Inverse function 
unsigned char * inv_sub_byte_column(unsigned char * s_table, int column)
{
	return transform_sub_bytes_table_column(s_table, column, NORMAL_OP);
}

unsigned char * inv_sub_byte(unsigned char * s_table) 
{
	return transform_sub_bytes(s_table, INVERSE_OP);
}

unsigned char * inv_shift_row(unsigned char * s_table) 
{
	return tranform_shift_row(s_table, INVERSE_OP);
}

unsigned char * inv_mix_column(unsigned char * s_table)
{
	return transform_mix_column(s_table, INVERSE_OP);
}

void decypher_message(unsigned char * s_table, unsigned char ** k_ptr_i, int nbr_round)
{
	if(nbr_round > MAX_ROUND) 
	{
		fprintf(stderr, "trop de tours");
		return;
	}

	for(int round = nbr_round; round > 0; round--)
	{
		// XOR KEY 
		s_table = add_round_key(s_table, k_ptr_i[round]);
		
		// INV MIX COLUMN
		if((round-1) < 9)
		{
			s_table = inv_mix_column(s_table);
		}
		
		// INV SHIFT ROW
		s_table = inv_shift_row(s_table);
		
		// INV SUB BYTES
		s_table = inv_sub_byte(s_table);
	
		// PRINT MSG 
		printf("ROUND: %d \n", round-1);
		print_table(s_table, TAB_SIZE,4);
	
	}

	// s xor k_0 
	s_table = add_round_key(s_table, k_ptr_i[0]);
	
	printf("RESULTAT DÉCHIFFREMENT: \n");
	print_table(s_table, TAB_SIZE,4);
	
}

