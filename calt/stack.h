#include <stdbool.h>

#ifndef STACK_H
#define STACK_H

typedef struct {
    double *items;
    int top;
    int capacity;
} Stack;

Stack *create_stack(int capacity);
bool push(Stack *st, double item);
double pop(Stack *st);
double peek(Stack *st);

#endif // STACK_H
