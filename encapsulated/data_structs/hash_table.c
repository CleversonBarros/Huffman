#include "hash_table"

void create_empty_table(unsigned char code_map[][9])
{
	int lines;
	for(lines = 0; lines < 256; i++) code_map[lines][0] = '\0';
}