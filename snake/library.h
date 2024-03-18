#include "raylib.h"

#ifndef LIBRARY_H
#define LIBRARY_H

typedef struct node {
    Vector2 data;
    struct node* next;
} node_t;

void print_list(node_t* head);
void push_end(node_t* head, Vector2 data);
void push_start(node_t** head, Vector2 data);
int pop(node_t** head);
int remove_last(node_t* head);

#endif // LIBRARY_H