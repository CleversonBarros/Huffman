#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node node;
typedef struct priorityQueue priorityQueue;

struct node
{
	void *c;
	int frequency;
	node *next;
	node *left;
	node *right;
};

struct priorityQueue
{
	node *head;
};

unsigned char get_item(node *node)
{
	 unsigned char *item = (unsigned char*) node->c;
	 return *item;
}

void printQueue(priorityQueue *q)
{
	node *aux;
	for(aux = q->head; aux != NULL; aux = aux->next)
	{
		printf("%c|%d\n",get_item(aux),aux->frequency);
	}
}

void print_pre_order(node *tree)
{
	if (tree != NULL) {
		printf("%c|%d\n", get_item(tree),tree->frequency);
		print_pre_order(tree->left);
		print_pre_order(tree->right);
	}
}

node *createNode(unsigned char c, int frequency)
{
	unsigned char *item = (unsigned char*) malloc (sizeof(unsigned char));
	*item = c;

	node *new = (node*)malloc(sizeof(node));
	new->c = item;
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

int set_bitInt(int c, int i)
{
	int mask = 1 << i;
	return mask | c;
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
			codeMap[get_item(root)][j] = temp[j];
		}
		codeMap[get_item(root)][j] = '\0';
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
	
	if(is_child(root) && (get_item(root) == '*' || get_item(root) == '\\'))
	{
		return 2;
	}
	
	return 1 + treeSize(root->left) + treeSize(root->right);
}

void writeHeader(FILE *output, int tree_size, int trash_size)
{
	unsigned char firstByte;
	unsigned char secondByte;
	rewind(output);

	firstByte = tree_size >> 8;
	trash_size = trash_size << 5;
	firstByte |= trash_size;
	secondByte = tree_size;

	fprintf(output, "%c",firstByte);
	fprintf(output, "%c",secondByte);
}

void writeHuffmanTree(FILE *output, node *root)
{
	if(root == NULL) return;
	
	if((get_item(root) == '*' || get_item(root) == '\\') && is_child(root))
	{
		fprintf(output,"\\%c", get_item(root));
	}

	else
	{
		fprintf(output, "%c", get_item(root));
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
	
	//print_pre_order(q->head);
	//printf("%d\n",trashSize(codeMap, frequency));

	writeHeader(output, treeSize(q->head), trashSize(codeMap, frequency));
	writeHuffmanTree(output, q->head);
	writeFileCompressed(input, output, codeMap);

	fclose(input);
	fclose(output);
}

int getTrashSize(FILE *input)
{
	unsigned char byte;
	int trashSize;

	fscanf(input,"%c",&byte);
	trashSize = byte >> 5;
	return trashSize;
}

int getTreeSize(FILE *input)
{
	unsigned char byte;
	int treeSize = 0, i;

	fseek(input, 0, SEEK_SET);
	fscanf(input,"%c",&byte);

	for(i = 4; i >= 0; i--)
	{
		if(is_bit_i_set(byte, i))
		{
			treeSize = set_bitInt(treeSize,i + 8);
		}
	}

	fscanf(input,"%c",&byte);

	for(i = 7; i >= 0; i--)
	{
		if(is_bit_i_set(byte,i))
		{
			treeSize = set_bitInt(treeSize, i);
		}
	}
	
	return treeSize;
}

node *rebuildHuffmanTree(FILE *input, int *treeSize)
{
	if(treeSize < 0) return NULL;
	
	unsigned char c;
	unsigned char aux;
	node *root;
	fscanf(input,"%c",&c);

	if(c == '*')
	{
		root = createNode(c,0);
		(*treeSize)--;
		root->left = rebuildHuffmanTree(input,treeSize);
		(*treeSize)--;
		root->right = rebuildHuffmanTree(input,treeSize);
	}
	
	if(c == '\\')
	{
		(*treeSize)--;
		fscanf(input,"%c",&c);
		root = createNode(c,0);
	}

	else if(c != '*')
	{
		(*treeSize)--;
		root = createNode(c,0);
	}

	return root;
}


int size_file(FILE *file)
{
	int p = ftell(file);
	int size;
	fseek(file, 0, SEEK_END);
	size = ftell(file);
	fseek(file, p, SEEK_SET);

	return size;
}

void writeFileDecompressed(FILE *input, FILE *output, node *root, int trashSize, int treeSize)
{
	unsigned char c;
	int sizeFile, bit, i;
	node *rootAux = root;

	sizeFile = size_file(input) - treeSize - 3;

	while(sizeFile--)
	{
		fscanf(input,"%c",&c);
		for(i = 7; i >= 0; i--)
		{
			if(is_bit_i_set(c, i))
			{
				rootAux = rootAux->right;
			}
			else
			{
				rootAux = rootAux->left;
			}

			if(is_child(rootAux))
			{
				fprintf(output, "%c", get_item(rootAux));
				rootAux = root;
			}
		}
	}

	fscanf(input,"%c",&c);
	for(i = 7; i >= trashSize; i--)
	{
		if(is_bit_i_set(c, i))
		{
			rootAux = rootAux->right;
		}
		else
		{
			rootAux = rootAux->left;
		}

		if(is_child(rootAux))
		{
			//printf("%c\n", get_item(rootAux));
			fprintf(output, "%c", get_item(rootAux));
			rootAux = root;
		}
	}
}

int decompress(FILE *input)
{
	int trashSize = getTrashSize(input);
	int treeSize = getTreeSize(input);
	int treeSizeBackup = treeSize;
	FILE *output = fopen("descomprimiu","wb");

	node *root = rebuildHuffmanTree(input,&treeSize);
	writeFileDecompressed(input, output, root, trashSize, treeSizeBackup);

}

int main()
{
	FILE *file; int entry; char path[200];
	
	printf("\n########### HUFFMAN ###########\n\n(1) COMPRESS OR (2) DECOMPRESS\n\nEntry:	");
	
	scanf("%d", &entry);
	
	switch (entry)
	{
		case 1:
			printf("\nEnter a directory or a file name:	");
			scanf("%s", &path);
			file = fopen(path, "rb");
			if(file==NULL) {puts("\nInvalid path.\n\n##### END OF EXECUTION ######\n"); break;}
			compress(file);
			printf("\n##### END OF EXECUTION ######\n");
		break;

		case 2:
			printf("\nEnter a directory or file name:	");
			scanf("%s", &path);
			file = fopen(path, "rb");
			if(file==NULL) {puts("\nInvalid path.\n\n##### END OF EXECUTION ######\n"); break;}
			decompress(file);
			printf("\n##### END OF EXECUTION ######\n");
		break;

		default:
			printf("\nInvalid entry.\n\n##### END OF EXECUTION ######\n");	
		return 0;
	
	}
	
	fclose(file);
}
