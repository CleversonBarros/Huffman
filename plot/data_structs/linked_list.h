#include <stdio.h>
#include <stdlib.h>

typedef struct node node;

node* create_linked_list ();

node* add_list (node *head, int item);

int is_empty (node *head);

int search_list (node *head, int item);

void print_linked_list_last_to_first (node *head);

void print_linked_list_first_to_last(node *head);