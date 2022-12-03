#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "tools.h"
#include "const.h"

unsigned char * transform_sub_bytes_table_column(unsigned char * s_table, int column, mod_ope mode);
unsigned char * transform_sub_bytes(unsigned char * s_table, mod_ope mode);
unsigned char * tranform_shift_row(unsigned char * s_table, mod_ope mode);
unsigned char * transform_mix_column(unsigned char * s_table, mod_ope mode);
unsigned char * add_round_key(unsigned char * s_table, unsigned char * k);

#endif // TRANSFORM_H
