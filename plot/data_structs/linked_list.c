#include "linked_list.h"

struct node
{
	int item;
	struct node *next;
};

node* create_linked_list ()
{
	return NULL;
}

node* add_list(node *head, int item)
{
	node *new_node = (node*)malloc(sizeof(node));
	new_node -> item = item;
	new_node -> next = head;
	return new_node;
}

int is_empty (node *head)
{
	return (head == NULL);
}

int search_list (node *head, int item)
{
	int counter=0;
	while(head!=NULL)
	{
		if (head->item==item)
		{
			return counter;
		}
		counter++;
		head=head->next;
	}
	/*
	if (is_empty(head) || item==head->item)
	{
		return 1;
	}
	else
	{
		return 1 + search_list(head->next, item);
	}*/
	
}


void print_linked_list_last_to_first (node *head)
{
	while (head != NULL)
	{
		printf("%d\n", head->item);
		head = head->next;
	}
}

void print_linked_list_first_to_last(node *head)
{
	if (head != NULL)
	{
		print_linked_list_first_to_last(head->next);
		printf("%d\n", head->item);
	}
}