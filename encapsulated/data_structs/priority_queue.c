#include "priority_queue.h"


typedef struct priority_queue priority_queue;

struct priority_queue
{
	node *head;
};

priority_queue *create_queue()
{
	priority_queue *new_q = (priority_queue*)malloc(sizeof(priority_queue));
	new_q->head = NULL;
	return new_q;
}

void queue(priority_queue *q, node *new_node)
{
	if(is_empty(q) || new_node->frequency < q->head->frequency)
	{
		new_node->next = q->head;
		q->head = new_node;
	}

	else
	{
		node *current = q->head;
		while((current->next != NULL) && (current->next->frequency < new_node->frequency))
		{
			current = current->next;
		}
		new_node->next = current->next;
		current->next = new_node;
	}
}

void dequeue(priority_queue *q)
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

void add_queue(priority_queue *q, int *frequency) //(falta colocar void aq)
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

int size_queue(priority_queue *q)
{
	int size;
	node *aux = q->head;

	for(size = 0; aux != NULL; size++)
	{
		aux = aux->next;
	}

	return size;
}

int is_empty(priority_queue *q)
{
	return (q->head == NULL);
}

void print_queue(priority_queue *q)
{
	node *aux;
	for(aux = q->head; aux != NULL; aux = aux->next)
	{
		printf("%c|%d\n",aux->c,aux->frequency);
	}
}

