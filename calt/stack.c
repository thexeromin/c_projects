#include <limits.h>
#include <stdlib.h>
#include <stdbool.h>
#include "./stack.h"

// create_stack: returns a stack based on capacity
Stack *create_stack(int capacity) {
    Stack *st = (Stack*)malloc(sizeof(Stack));

    st->items = (double*)malloc(capacity * sizeof(double));
    st->top = -1;
    st->capacity = capacity;

    return st;
}


bool push(Stack *st, double item) {
    if(st->top == st->capacity - 1) {
        return false;
    }
    
    st->items[++st->top] = item;
    return true;
}

double pop(Stack *st) {
    if(st->top == -1) {
        return INT_MIN;
    }

    return st->items[st->top--];
}

double peek(Stack *st) {
    if(st->top == -1) {
        return INT_MIN;
    }

    return st->items[st->top];
}
