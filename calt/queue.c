#include <limits.h>
#include <stdlib.h>

#include "queue.h"

// initializer function
Queue *create_queue(int capacity) {
    Queue *queue = (Queue*)malloc(sizeof(Queue));
    queue->capacity = capacity;
    queue->front = queue->size = 0;

    queue->rear = capacity - 1;
    queue->items = (double*)malloc(queue->capacity * sizeof(double));

    return queue;
}

int is_full(Queue *queue) {
    return (queue->size == queue->capacity);
}

int is_empty(Queue *queue) {
    return (queue->size == 0);
}

// add elements to the rear
void enqueue(Queue *queue, double item) {
    if(is_full(queue))
        return;
    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->items[queue->rear] = item;
    queue->size = queue->size + 1;
}

// remove elements from the front
double dequeue(Queue *queue) {
    if(is_empty(queue))
        return INT_MIN;
    double item = queue->items[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size = queue->size - 1;
    return item;
}
