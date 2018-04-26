#include "compress.h"

void get_byte_frequency(FILE *file, int *frequency)
{
	unsigned char c;

	while((fscanf(file,"%c",&c)) != EOF)
	{
		frequency[c]++;
	}

}

void create_huffman_tree(priority_queue *q)
{
	if(size_queue(q) == 1) return;

	node *child1 = q->head;
	node *child2 = q->head->next;
	node *new = create_node('*',child1->frequency + child2->frequency);

	new->left = child1;
	new->right = child2;
	dequeue(q);
	queue(q,new);

	create_huffman_tree(q);
}

void generate_code_map(unsigned char code_map[][9], unsigned char *temp, node *root, int i)
{

	if(is_child(root))
	{
		int j;
		for(j = 0; j < i; j++)
		{
			code_map[root->c][j] = temp[j];
		}
		code_map[root->c][j] = '\0';
	}

	if(root->left != NULL)
	{
		temp[i] = '0';
		temp[i+1] = '\0';
		generate_code_map(code_map, temp, root->left, i + 1);
		temp[i] = '\0';
	}

	if(root->right != NULL)
	{
		temp[i] = '1';
		temp[i+1] = '\0';
		generate_code_map(code_map, temp, root->right, i + 1);
		temp[i] = '\0';
	}
}

int trash_size(unsigned char code_map[][9], int *frequency)
{
	int size = 0;
	int i, trash;

	for(i = 0; i < 256; i++)
	{
		if(code_map[i][0] != '\0')
		{
			size += (strlen(code_map[i]) * frequency[i]);
		}
	}

	trash = 8 - (size % 8);

	return trash;
}

/*
char *decimalToBinary(int x)
{
	char binary[9];
}
*/

int compress(FILE *file)
{
	FILE *output;
	output = fopen("pronto.das","wb");

	int frequency[256] = {0};
	unsigned char code_map[256][9];
	unsigned char temp[256];
	priority_queue *q  = create_queue();

	temp[0] = '\0';

	get_byte_frequency(file, frequency);
	add_queue(q,frequency);
	create_huffman_tree(q);

	create_empty_table(code_map);
	generate_code_map(code_map, temp, q->head, 0);
//	writeheader(output, q->head);

	//Escrever tamanho do lixo, da arvore, e a arvore.

	/*
	//DEBUG
	//MATRIZ
	for(int i = 0; i < 256; i++)
	{
		if(code_map[i][0] != '\0') printf("%s\n",code_map[i]);
	}
	//FILA E ARVORE
	printf("PRINT QUEUE ESTADO FINAL\n");
	print_queue(q);
	printf("FIM DA QUEUE\n");
	printf("PRINT DA ARVORE ESTADO FINAL");
	print_pre_order(q->head);
	printf("FIM DA ARVORE\n");
	
	//TAMANHO ARVORE E TAMANHO LIXO
	printf("tamanho da arvore %d\n",tree_size(q->head));
	printf("tamanho do lixo %d\n",trash_size(code_map, frequency));
	//END
	*/
}
