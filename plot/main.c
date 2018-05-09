#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "./data_structs/binary_tree.h"
#include "./data_structs/linked_list.h"

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
		//fprintf(data,"%d, %d\n", i, search_tree(bt, random));
		//fprintf(data,"%d, %d\n", i, search_list(list, random));
	}
	printf("chegou aq\n");
	//print_linked_list_last_to_first (list); return 0;
	for (i = 0; i < 10000; ++i)
	{
		fprintf(data, "%d, %d, %d\n", i, search_tree(bt, save_list[i]), search_list(list, save_list[9999-i]));
	}

	fclose(data);
	printf("chegouaq\n");
}