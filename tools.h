#ifndef TOOLS_H
#define TOOLS_H

int get_naif_bit_poid_plus_fort(unsigned short reste);
unsigned short naif_division_euclidienne(unsigned short dividende, unsigned short diviseur);
unsigned short polynomial_multiplication(unsigned short tmp, unsigned char multiply_number); 
void print_table(unsigned char * table, int tab_size, int padding);

#endif // TOOLS_H
