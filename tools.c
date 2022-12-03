#include <stdio.h>
#include "tools.h"

// Tools function 
int get_naif_bit_poid_plus_fort(unsigned short reste) 
{
	if(reste == 0)
	{
		return 0;
	}
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
	if(dividende == 0)
	{
		return 0;
	}
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

unsigned short polynomial_multiplication(unsigned short value, unsigned char multiply_number) 
{
	if(multiply_number == 0)
	{
		return 0;
	}
	int bit_poids_plus_fort = get_naif_bit_poid_plus_fort(multiply_number);
	unsigned short res = 0x0000;

	multiply_number = multiply_number ^ (0x01 << bit_poids_plus_fort);
	
	unsigned short reduc_value;
	res = (value << bit_poids_plus_fort);
	
	while(multiply_number != 0)
	{
		bit_poids_plus_fort = get_naif_bit_poid_plus_fort(multiply_number);
		reduc_value = (value << bit_poids_plus_fort );
		res = res ^ reduc_value;  	
		multiply_number = multiply_number ^ (0x01 << bit_poids_plus_fort);
	}
	return res;
}

void print_table(unsigned char * table, int tab_size, int padding)
{
	for(int i = 0; i < 16; i++)
	{
		if(table[i] < 0x0F)
		{
			printf("0%x ", table[i]);
		}
		else 
		{
			printf("%x ", table[i]);
		}
		if(!( (i+1) % 4))
		{
			printf("\n");
		}
	}
	printf("\n");
}

