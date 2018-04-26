#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "binary_tree.h"

typedef struct priority_queue priority_queue;

struct priority_queue;

priority_queue *create_queue();

void queue(priority_queue *q, node *new_node);

void dequeue(priority_queue *q);

void add_queue(priority_queue *q, int *frequency); //(falta colocar void aq)

int size_queue(priority_queue *q);

int is_empty(priority_queue *q);

void print_queue(priority_queue *q);