#include "binary_tree.h"

struct binary_tree
{
	int item;
	struct binary_tree *left;
	struct binary_tree *right;

};

binary_tree* create_empty_binary_tree()
{
	return NULL;
}

binary_tree* create_binary_tree(int item, binary_tree *left, binary_tree *right)
{
	binary_tree *new_binary_tree = (binary_tree*) malloc(sizeof(binary_tree));
	new_binary_tree->item = item;
	new_binary_tree->left = left;
	new_binary_tree->right = right;
	return new_binary_tree;	
}

binary_tree* add_tree(binary_tree *bt, int item)
{
	if (bt == NULL)
	{
		bt = create_binary_tree(item, NULL, NULL);
	} 
	
	else if (bt->item > item)
	{
		bt->left = add_tree(bt->left, item);
	} 
	
	else
	{
		bt->right = add_tree(bt->right, item);
	}

	return bt;
}

int search_tree(binary_tree *bt, int item)
{
	if (bt == NULL || bt->item == item)
	{
		return 1;
	}

	else if (bt->item > item)
	{
		return 1 + search_tree(bt->left, item);
	}

	else
	{
		return 1 + search_tree(bt->right, item);
	}
}

void print_pre_order(binary_tree *bt)
{
	if (bt!=NULL)
	{
		printf("%d ", bt->item);
		print_pre_order(bt->left);
		print_pre_order(bt->right);
	}
}