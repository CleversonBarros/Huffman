#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "./data_structs/binary_tree.h"
#include "./data_structs/linked_list.h"

/* gcc -o exec main.c data_structs/binary_tree.c data_structs/linked_list.c */

int main()
{

	FILE* data = fopen("base.csv","w");
	fprintf(data, "%s\n", "N_ELEMENTS, B_TREE, LIST");

		
	srand((unsigned)time(NULL));

	int i, random, save_list[10000];

	binary_tree *bt = create_empty_binary_tree();
	node *list = create_linked_list();
	
	for (i = 0; i < 10000; ++i)
	{
		random = rand()%1000000;
		bt = add_tree(bt, random);
		list = add_list(list, random);
		save_list[i] = random;
	}

	for (i = 0; i < 10000; ++i)
	{
		fprintf(data, "%d, %d, %d\n", i, search_tree(bt, save_list[i]), search_list(list, save_list[9999-i]));
	}

	fclose(data);

}
