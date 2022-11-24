#include <stdio.h>

#define SIZE_AES 128
#define TAB_SIZE (SIZE_AES/8)


unsigned char MESSAGE[TAB_SIZE] = 
{ 
	0x1A, 0x25, 0xDC, 0x8B,
	0x18, 0x78, 0x19, 0x56,
	0x6B, 0xD2, 0xB1, 0x17,
	0xDB, 0x2F, 0XC4, 0xBD
};

unsigned char K_0[TAB_SIZE] = 
{
	0x81, 0xEB, 0x5A, 0x28,
	0x39, 0x17, 0x18, 0xB0,
	0xD2, 0x44, 0xFF, 0x69,
	0xCD, 0X13, 0x15, 0xFD
};

// nist specification 
unsigned char SUB_BYTES_8_OCT[16][16] = 
{
	{ 0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76 },
	{ 0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0 },
	{ 0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15 },
	{ 0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75 },
	{ 0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84 },
	{ 0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf },
	{ 0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8 },
	{ 0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2 },
	{ 0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73 },
	{ 0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb },
	{ 0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79 },
	{ 0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08 },
	{ 0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a },
	{ 0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e },
	{ 0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf },
	{ 0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16 }
};

// par colonne
unsigned char MIX_COLUM_8_OCT[4][4] =
{
	{ 0x02, 0x03, 0x01, 0x01 },
	{ 0x01, 0x02, 0x03, 0x01 },
	{ 0x01, 0x01, 0x02, 0x03 },
	{ 0x03, 0x01, 0x01, 0x02 }
};

// table to column 
unsigned int COLUMN[4][4] =
{
	{ 0, 4, 8 , 12 },
	{ 1, 5, 9 , 13 },
	{ 2, 6, 10, 14 },
	{ 3, 7, 11, 15 },
};

// shift row 
int SHIFT_PERMUTATION_TABLE_8_OCT[TAB_SIZE] = 
{
	0, 1, 2, 3, 5, 6, 7, 4, 10, 11, 8, 9, 15, 14, 13, 12
};

// Signatures
int get_naif_bit_poid_plus_fort(unsigned short reste);
unsigned short naif_division_euclidienne(unsigned short dividende, unsigned short diviseur);
unsigned char * xor_key(unsigned char * s_table, unsigned char * k);
unsigned char * sub_byte(unsigned char * s_table);
unsigned char * shift_row(unsigned char * s_table);
unsigned char * mix_column(unsigned char * s_table);

// Fonctions
int get_naif_bit_poid_plus_fort(unsigned short reste) 
{
	int bit_poids_plus_fort = 0;
	while(reste != 1) 
	{
		reste = reste >> 1;
		bit_poids_plus_fort ++;
	}
	return bit_poids_plus_fort;
}

// return reste
unsigned short naif_division_euclidienne(unsigned short dividende, unsigned short diviseur)
{
	unsigned short reste = dividende;
	
	int bit_poids_plus_fort_diviseur = get_naif_bit_poid_plus_fort(diviseur);
	int bit_poids_plus_fort_reste = get_naif_bit_poid_plus_fort(reste);

	while(bit_poids_plus_fort_reste >= bit_poids_plus_fort_diviseur) 
	{
		reste = reste ^ (diviseur << (bit_poids_plus_fort_reste - bit_poids_plus_fort_diviseur));
		bit_poids_plus_fort_reste = get_naif_bit_poid_plus_fort(reste);
	}
	if(reste > 0xFF)
	{
		fprintf(stderr, "return value overflow"); 
	}
	return reste;
}

unsigned char * xor_key(unsigned char * s_table, unsigned char * k)
{
	for(int i = 0; i < TAB_SIZE; i++)
	{
		s_table[i] = s_table[i] ^ K_0[i];
	}
	return s_table;
}

unsigned char * sub_byte(unsigned char * s_table)
{
	struct Vector2D {
		int x;
		int y;
	};

	for(int i = 0; i < TAB_SIZE; i++)
	{
		struct Vector2D vector;
		unsigned char s_val = s_table[i]; 
		
		vector.x = (s_val & 0xF0) >> 4;
		vector.y = s_val & 0x0F;
		
		s_table[i] = SUB_BYTES_8_OCT[vector.x][vector.y];
	}
	return  s_table;
}

unsigned char * shift_row(unsigned char * s_table)
{
	unsigned char tmp_tab[TAB_SIZE];

	for(int i = 0; i < TAB_SIZE; i++) 
	{
		tmp_tab[i] = s_table[SHIFT_PERMUTATION_TABLE_8_OCT[i]];
	}

	// copy tmp_tab before free (end scope) 
	for(int i = 0; i < TAB_SIZE; i++)
	{
		s_table[i] = tmp_tab[i];
	}
	return s_table; 
}

unsigned char * mix_column(unsigned char * s_table)
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
				tmp_value ^= naif_division_euclidienne(MIX_COLUM_8_OCT[j][k] * s_table[COLUMN[i][k]], 0x11B);
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

int main()
{
	unsigned char * s_table = MESSAGE; 
	unsigned char * k = K_0;

	// s xor k_0 
	s_table = xor_key(s_table, k);
	
	// SUB_BYTE 
	s_table = sub_byte(s_table);

	// SHIFT ROW
	s_table = shift_row(s_table);

	// MIX COLUMN
	s_table = mix_column(s_table);

	int index_tab = 0;
	for(int i = 0; i < TAB_SIZE/4; i++)
	{
		for(int j = 0; j < TAB_SIZE/4; j++)
		{
			printf("%X ", s_table[index_tab]);
			index_tab++;
		}
		printf("\n");
	}
	
	return 0;
}