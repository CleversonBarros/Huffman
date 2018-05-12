#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


typedef struct binary_tree binary_tree;

struct binary_tree;

binary_tree* create_empty_binary_tree();

binary_tree* add_tree(int item);

int get_item(binary_tree *bt);

int is_child(binary_tree *t);

int binary_tree_size(binary_tree *root);

void print_pre_order(binary_tree *tree);