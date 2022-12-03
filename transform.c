#include <stdio.h>
#include "transform.h"
#include "const.h"

// Transfom function 
unsigned char * transform_sub_bytes_table_column(unsigned char * s_table, int column, mod_ope mode) 
{

	struct Vector2D {
		unsigned char x;
		unsigned char y;
	};

	for(int i = 0; i < SIZE_COLUMN; i++)
	{
		unsigned char value = s_table[COLUMN[column][i]]; 

		struct Vector2D vector;
		
		vector.x = (value & 0xF0) >> 4;
		vector.y = value & 0x0F;

		switch (mode) 
		{
			case NORMAL_OP:
				s_table[COLUMN[column][i]] = SUB_BYTES_8_OCT[vector.x][vector.y];
				break;
			case INVERSE_OP:
				s_table[COLUMN[column][i]] =  INV_SUB_BYTE[vector.x][vector.y];
				break;
			default:
				fprintf(stderr, "mode operation in sub byte function not defined, not effect in table");
		}
	}
	return s_table;
}

unsigned char * tranform_shift_row(unsigned char * s_table, mod_ope mode) 
{
	unsigned char tmp_tab[TAB_SIZE];

	int index_tab = 0;
	for(int i = 0; i < 4; i++) 
	{
		for(int j = 0; j < 4; j++)
		{
			switch (mode) 
			{
				case NORMAL_OP:
					tmp_tab[index_tab] = s_table[SHIFT_PERMUTATION_TABLE_8_OCT[i][j]];
					break;
				case INVERSE_OP:
					tmp_tab[index_tab] = s_table[INV_SHIFT_PERMUTATION_TABLE_8_OCT[i][j]];
					break;
				default:
					fprintf(stderr, "mode operation in row shift function not defined, not effect in table");
			}
			index_tab ++;
		}
	}

	// copy tmp_tab before free (end scope) 
	for(int i = 0; i < TAB_SIZE; i++)
	{
		s_table[i] = tmp_tab[i];
	}
	return s_table; 
}

unsigned char * transform_sub_bytes(unsigned char * s_table, mod_ope mode)
{
	for(int i = 0; i < 4; i++)
	{
		switch (mode) {
			case NORMAL_OP:
				s_table = transform_sub_bytes_table_column(s_table, i, NORMAL_OP);
				break;
			case INVERSE_OP:
				s_table = transform_sub_bytes_table_column(s_table, i, INVERSE_OP);
				break;
			default:
				fprintf(stderr, "mode operation in sub_bytes function not defined, not effect in table");
		}
	}
	return s_table;
}

unsigned char * transform_mix_column(unsigned char * s_table, mod_ope mode)
{
	unsigned char tmp_tab[TAB_SIZE];
	int index = 0;
	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			short tmp_value = 0;
			for(int k = 0; k < 4; k++)
			{
				unsigned short tmp = s_table[COLUMN[i][k]]; // 0xFF << 8 = 0xFF00
				unsigned char multiply_number = 0x00;
				
				switch (mode) {
					case NORMAL_OP:
						multiply_number = MIX_COLUM_8_OCT[j][k];
						break;
					case INVERSE_OP:
						multiply_number = INV_MIX_COLUM_8_OCT[j][k];
						break;
					default:
						fprintf(stderr, "mode operation not defined in mix column, return 0 by default"); 
				}
				tmp = polynomial_multiplication(tmp, multiply_number);	
				tmp_value ^= naif_division_euclidienne(tmp, 0x11B);
			}
			tmp_value = naif_division_euclidienne(tmp_value, 0X11B);
			tmp_tab[COLUMN[i][j]] = tmp_value;
			index ++;
		}
	}

	// copy tmp_tab before free (end scope) 
	for(int i = 0; i < TAB_SIZE; i++)
	{
		s_table[i] = tmp_tab[i];
	}
	return s_table;
}

unsigned char * add_round_key(unsigned char * s_table, unsigned char * k)
{
	for(int i = 0; i < TAB_SIZE; i++)
	{
		s_table[i] = s_table[i] ^ k[i];
	}
	return s_table;
}

