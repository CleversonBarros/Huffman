#include "binary_tree.h"

struct node
{
	unsigned char item;
	int frequency; //(falta colocar void aq)
	node *next;
	node *left;
	node *right;
};

node *create_node(char unsigned item, int frequency) //(falta colocar void aq)
{
	node *new_node = (node*)malloc(sizeof(node));
	new_node->item = item;
	new_node->frequency = frequency;
	new_node->left = NULL;
	new_node->right = NULL;
	return new_node;
}

int is_child(node *t)
{
	return (t->right == NULL && t->left == NULL);
}

int binary_tree_size(node *root)
{
	if(root == NULL) return 0;
	return 1 + binary_tree_size(root->left) + binary_tree_size(root->right);
}


void print_pre_order(node *tree)
{
	if (tree != NULL)
	{
		printf("%c|%d\n", tree->item,tree->frequency);
		print_pre_order(tree->left);
		print_pre_order(tree->right);
	}
}
