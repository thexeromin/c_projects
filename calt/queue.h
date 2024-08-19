#ifndef QUEUE_H 
#define QUEUE_H

typedef struct {
    int rear;       // the end at which elements are added
    int front;      // the end at which elements are removed
    int size;
    int capacity;
    double *items; 
} Queue;

Queue *create_queue(int capacity);
void enqueue(Queue *queue, double item);
double dequeue(Queue *queue);

#endif // QUEUE_H
