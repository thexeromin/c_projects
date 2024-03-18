#include <stdio.h>
#include <stdlib.h>
#include "library.h"

// print_list: print the linked list
void print_list(node_t* head) {
    node_t* current = head;

    while (current != NULL) {
        printf("x: %f, y: %f\n", current->data.x, current->data.y);
        current = current->next;
    }
}

// push_end: push data at the end of head
void push_end(node_t* head, Vector2 data) {
    node_t* current = head;
    while(current->next != NULL) {
        current = current->next;
    }

    current->next = (node_t*) malloc(sizeof(node_t));
    current->next->data = data;
    current->next->next = NULL;
}

// push_start: push data at the start of head
void push_start(node_t** head, Vector2 data) {
    node_t* new_node;
    new_node = (node_t*) malloc(sizeof(node_t));

    new_node->data = data;
    new_node->next = *head;
    *head = new_node;
}

// pop: remove first item from head
int pop(node_t** head) {
    node_t* next_node = NULL;

    if(*head == NULL) return -1;

    next_node = (*head)->next;
    free(*head);
    *head = next_node;

    return 0;
}

// remove_last: remove last item from head
int remove_last(node_t* head) {
    if(head->next == NULL) {
        free(head);
        return 0;
    }

    node_t* current = head;
    while(current->next->next != NULL) {
        current = current->next;
    }

    free(current->next);
    current->next = NULL;
    return 0;
}