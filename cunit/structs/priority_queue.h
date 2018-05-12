#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


typedef struct node node;

typedef struct priority_queue priority_queue;

struct node;

struct priority_queue;

priority_queue* create_empty_priority_queue();

priority_queue *create_queue();

node* create_node(int item, int frequency);

void enqueue(priority_queue *q, node *new_node);

void dequeue(priority_queue *q);

void add_queue(priority_queue *q, int *frequency);

int size_queue(priority_queue *q);

int is_empty(priority_queue *q);

void print_queue(priority_queue *q);