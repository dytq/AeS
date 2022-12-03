#include "transform.h"

unsigned char * inv_sub_byte_column(unsigned char * s_table, int column);
unsigned char * inv_sub_byte(unsigned char * s_table);
unsigned char * inv_shift_row(unsigned char * s_table);
unsigned char * inv_mix_column(unsigned char * s_table);
void decypher_message(unsigned char * s_table, unsigned char ** k_ptr_i, int nbr_round);
