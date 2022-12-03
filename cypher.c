#include <stdio.h>
#include "cypher.h"

// Normal function
unsigned char * sub_byte_column(unsigned char * s_table, int column) 
{ 
	return transform_sub_bytes_table_column(s_table, column, NORMAL_OP);
}

unsigned char * sub_byte(unsigned char * s_table)
{
	return transform_sub_bytes(s_table, NORMAL_OP);
}

unsigned char * shift_row(unsigned char * s_table)
{	
	return tranform_shift_row(s_table, NORMAL_OP); 
}

unsigned char * mix_column(unsigned char * s_table)
{
	return transform_mix_column(s_table, NORMAL_OP);
}


void cypher_message(unsigned char * s_table, unsigned char ** k_ptr_i, int nbr_round)
{
	if(nbr_round > MAX_ROUND) 
	{
		fprintf(stderr, "trop de tours");
		return;
	}
	s_table = add_round_key(s_table, k_ptr_i[0]);
	
	for(int round = 1; round < nbr_round + 1; round++)
	{
		// PRINT MSG 
		printf("ROUND %d\n", round-1);
		print_table(s_table, TAB_SIZE, 4);
		
		// SUB_BYTE 
		s_table = sub_byte(s_table);

		// SHIFT ROW
		s_table = shift_row(s_table);

		// MIX COLUMN
		if((round-1) < 9) 
		{
			s_table = mix_column(s_table);
		}
		
		// XOR KEY 
		s_table = add_round_key(s_table, k_ptr_i[round]);
	}
	
	printf("RESULTAT CHIFFREMENT: \n");
	print_table(s_table, TAB_SIZE,4);
}
