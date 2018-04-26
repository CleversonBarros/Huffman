#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


typedef struct node node;

struct node;

node *create_node(char unsigned item, int frequency); //falta void

int is_child(node *t);

int binary_tree_size(node *root);

void print_pre_order(node *tree);