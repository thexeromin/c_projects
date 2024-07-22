#ifndef LIBRARY_H
#define LIBRARY_H

typedef struct node {
    char data[100];
    struct node* next;
} node_t;

int push(node_t** head, char data[100]);
node_t* delete(node_t* head, char* data);

#endif // LIBRARY_H
