#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../data_structs/binary_tree.h"
#include "../data_structs/priority_queue.h"
#include "../data_structs/hash_table.h"

void get_byte_frequency(FILE *file, int *frequency);

void create_huffman_tree(priority_queue *q);

void generate_code_map(unsigned char code_map[][9], unsigned char *temp, node *root, int i);

int trash_size(unsigned char code_map[][9], int *frequency);

int compress(FILE *file);
