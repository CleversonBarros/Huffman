#include "binary_tree.h"

struct binary_tree
{
	int item;
	binary_tree *left;
	binary_tree *right;
};

binary_tree* create_empty_binary_tree()
{
	return NULL;
}

binary_tree* add_tree(int item)
{
	binary_tree *new_node = (binary_tree*)malloc(sizeof(binary_tree));
	new_node->item = item;
	new_node->left = NULL;
	new_node->right = NULL;
	return new_node;
}

int get_item(binary_tree *bt)
{
	return bt->item;
}

int is_child(binary_tree *t)
{
	return (t->right == NULL && t->left == NULL);
}

int binary_tree_size(binary_tree *root)
{
	if(root == NULL) return 0;
	return 1 + binary_tree_size(root->left) + binary_tree_size(root->right);
}


void print_pre_order(binary_tree *tree)
{
	if (tree != NULL)
	{
		printf("%d\n", tree->item);
		print_pre_order(tree->left);
		print_pre_order(tree->right);
	}
}
