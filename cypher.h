#ifndef CYPHER_H
#define CYPHER_H

#include "transform.h"

unsigned char * sub_byte_column(unsigned char * s_table, int column); 
unsigned char * sub_byte(unsigned char * s_table);
unsigned char * shift_row(unsigned char * s_table);
unsigned char * mix_column(unsigned char * s_table);

void cypher_message(unsigned char * s_table, unsigned char ** k_ptr_i, int nbr_round);
#endif // CYPHER_H
