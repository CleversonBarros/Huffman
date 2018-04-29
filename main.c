#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node node;
typedef struct priorityQueue priorityQueue;

struct node
{
	unsigned char c;
	int frequency;
	node *next;
	node *left;
	node *right;
};

struct priorityQueue
{
	node *head;
};


void printQueue(priorityQueue *q)
{
	node *aux;
	for(aux = q->head; aux != NULL; aux = aux->next)
	{
		printf("%c|%d\n",aux->c,aux->frequency);
	}
}

void print_pre_order(node *tree)
{
	if (tree != NULL) {
		printf("%hhX|%d\n", tree->c,tree->frequency);
		print_pre_order(tree->left);
		print_pre_order(tree->right);
	}
}

node *createNode(char unsigned c, int frequency)
{
	node *new = (node*)malloc(sizeof(node));
	new->c = c;
	new->frequency = frequency;
	new->left = NULL;
	new->right = NULL;
	return new;
}

int is_empty(priorityQueue *q)
{
	if(q->head == NULL) return 1;
	else return 0;
}

priorityQueue *createQueue(void)
{
	priorityQueue *q = (priorityQueue*)malloc(sizeof(priorityQueue));
	q->head = NULL;
	return q;
}

void queue(priorityQueue *q, node *new)
{
	if(is_empty(q) || new->frequency < q->head->frequency)
	{
		new->next = q->head;
		q->head = new;
	}

	else
	{
		node *current = q->head;
		while((current->next != NULL) && (current->next->frequency < new->frequency))
		{
			current = current->next;
		}
		new->next = current->next;
		current->next = new;
	}
}

void dequeue(priorityQueue *q)
{

	int i;

	if(is_empty(q))
	{
		printf("Queue is empty\n");
	}
	else
	{	
		for (i = 0; i < 2; ++i)
		{
			node *new = q->head;
			q->head = q->head->next;
			new->next = NULL;
		}

	}
}

void getByteFrequency(FILE *file, int *frequency)
{
	unsigned char c;

	while((fscanf(file,"%c",&c)) != EOF)
	{
		frequency[c]++;
	}

}

unsigned char set_bit(unsigned char c, int i)
{
	unsigned char mask = 1 << i;
	return mask | c;
}

int is_bit_i_set(unsigned char c, int i)
{
	unsigned char mask = 1 << i;
	return mask & c;
}

void addToQueue(priorityQueue *q, int *frequency)
{
	unsigned int i;

	for(i = 0; i < 256; i++)
	{
		if(frequency[i])
		{
			node* node = createNode(i,frequency[i]);
			queue(q, node); 		
		}
	}
}

int sizeQueue(priorityQueue *q)
{
	int i;
	node *aux = q->head;

	for(i = 0; aux != NULL; i++)
	{
		aux = aux->next;
	}

	return i;
}

void createHuffmanTree(priorityQueue *q)
{
	if(sizeQueue(q) == 1) return;

	node *child1 = q->head;
	node *child2 = q->head->next;
	node *new = createNode('*',child1->frequency + child2->frequency);

	new->left = child1;
	new->right = child2;
	dequeue(q);
	queue(q,new);

	createHuffmanTree(q);
}

int is_child(node *t)
{
	if(t->right == NULL && t->left == NULL) return 1;
	else return 0;
}

void generateCodeMap(unsigned char codeMap[][256], unsigned char *temp, node *root, int i)
{

	if(is_child(root))
	{
		int j;
		for(j = 0; j < i; j++)
		{
			codeMap[root->c][j] = temp[j];
		}
		codeMap[root->c][j] = '\0';
	}

	if(root->left != NULL)
	{
		temp[i] = '0';
		generateCodeMap(codeMap, temp, root->left, i + 1);
		temp[i] = '\0';
	}

	if(root->right != NULL)
	{
		temp[i] = '1';
		generateCodeMap(codeMap, temp, root->right, i + 1);
		temp[i] = '\0';
	}
}

void createEmptyTable(unsigned char codeMap[][256])
{
	int i;
	for(i = 0; i < 256; i++)
	{
		codeMap[i][0] = '\0';
	}
}

int trashSize(unsigned char codeMap[][256], int *frequency)
{
	int size = 0;
	int i, trash;

	for(i = 0; i < 256; i++)
	{
		if(frequency[i])
		{
			size += (strlen(codeMap[i]) * frequency[i]) ;
		}
	}

	trash = 8 - (size % 8);

	return trash;
}

int treeSize(node *root)
{
	if(root == NULL) return 0;
	
	if(is_child(root) && (root->c == '*' || root->c == '\\'))
	{
		return 2;
	}
	
	return 1 + treeSize(root->left) + treeSize(root->right);
}

void writeHeader(FILE *output, int tree_size, int trash_size)
{
	unsigned char primeiroByte;
	unsigned char segundoByte;
	rewind(output);

	primeiroByte = tree_size >> 8;
	trash_size = trash_size << 5;
	primeiroByte |= trash_size;
	segundoByte = tree_size;

	fprintf(output, "%c",primeiroByte);
	fprintf(output, "%c",segundoByte);
}

void writeHuffmanTree(FILE *output, node *root)
{
	if(root == NULL) return;
	
	if((root->c == '*' || root->c == '\\') && is_child(root))
	{
		fprintf(output,"\\%c",root->c);
	}

	else
	{
		fprintf(output, "%c",root->c);
	}

	writeHuffmanTree(output, root->left);
	writeHuffmanTree(output, root->right);	
}

void writeFileCompressed(FILE *input, FILE *output, unsigned char codeMap[][256])
{
	unsigned char c;
	unsigned char byte;
	int i, bit;

	byte = 0;
	bit = 7;

	rewind(input);
	while(fscanf(input,"%c",&c) != EOF)
	{
		for(i = 0; codeMap[c][i] != '\0'; i++)
		{
			if(bit < 0)
			{
				fprintf(output,"%c",byte);
				byte = 0;
				bit = 7;
			}

			if(codeMap[c][i] == '1')
			{
				byte = set_bit(byte,bit);
			}
			bit--;
		}
	}

	fprintf(output,"%c",byte);
	
}

int compress(FILE *input)
{
	FILE *output;
	output = fopen("comprimido.huff","wb");

	int frequency[256] = {0};
	unsigned char codeMap[256][256];
	unsigned char temp[256];
	priorityQueue *q  = createQueue();

	temp[0] = '\0';

	getByteFrequency(input, frequency);
	addToQueue(q,frequency);
	createHuffmanTree(q);

	createEmptyTable(codeMap);
	generateCodeMap(codeMap, temp, q->head, 0);
	
	writeHeader(output, treeSize(q->head), trashSize(codeMap, frequency));
	writeHuffmanTree(output, q->head);
	writeFileCompressed(input, output, codeMap);

	fclose(input);
	fclose(output);
}


int main()
{
	FILE *file;
	file = fopen("entrada.txt","rb");
	compress(file);
	fclose(file);	
}