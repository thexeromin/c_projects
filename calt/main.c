#include <stdio.h>
#include <ctype.h>
#include <limits.h>

#include "stack.h"
#include "queue.h"

#define RIGHT_ASSOCIATE 0
#define LEFT_ASSOCIATE 1

int get_operator_precedence(char operator);
int get_operator_associativity(char operator);

int main(int argc, char *argv[]) {
    Queue *output_queue = create_queue(10);
    Stack *operator_stack = create_stack(10);
    Stack *result_stack = create_stack(10);
    double token;

    if(argc != 2) {
        fprintf(stderr, "missing argument: expression");
        return 1;
    }

    for(int i = 0; argv[1][i]; i++) {
        // parse numbers
        double flag = 1;
        if(i == 0 && argv[1][i] == '-' && isdigit(argv[1][++i])) {
            flag = -1;
        }
        if(isdigit(argv[1][i])) {
            double number = (argv[1][i] - '0');
            while(isdigit(argv[1][++i])) {
                number = (10 * number) + (argv[1][i] - '0');
            }
            // parse fraction part
            if(argv[1][i] == '.') {
                double e = 1;
                while(isdigit(argv[1][++i])) {
                    e = e * 10;
                    number = ((e * number) + (argv[1][i] - '0')) / e;
                }
            }
            enqueue(output_queue, number * flag);
        }

        // break if end of string reached early
        if(argv[1][i] == '\0')
            break;
        
        // prase operators
        switch (argv[1][i]) {
            case '+':
            case '-':
            case '*':
            case '/':
                char op1 = argv[1][i];
                char op2;
                int op1_precedence = get_operator_precedence(op1);
                int op1_associativity = get_operator_associativity(op1);

                while((op2 = peek(operator_stack)) != INT_MIN) {
                    bool higher_precedence = (get_operator_precedence(op2) > op1_precedence);
                    bool same_precedence_left_associative = 
                        (op1_precedence == get_operator_precedence(op2)) && 
                        (op1_associativity == LEFT_ASSOCIATE);

                    if(higher_precedence || same_precedence_left_associative)
                        enqueue(output_queue, pop(operator_stack));
                    else
                        break;
                }
                push(operator_stack, op1);
                break;
        }
    }
    
    // pop operators and add to queue
    while((token = pop(operator_stack)) != INT_MIN) 
        enqueue(output_queue, token);
    
    // evaluation logic
    while((token = dequeue(output_queue)) != INT_MIN) {
        switch((int)token) {
            case '+':
                double op1 = pop(result_stack);
                double op2 = pop(result_stack);
                push(result_stack, op1 + op2);
                break;
            case '-':
                op1 = pop(result_stack);
                op2 = pop(result_stack);
                push(result_stack, op2 - op1);
                break;
            case '*':
                op1 = pop(result_stack);
                op2 = pop(result_stack);
                push(result_stack, op1 * op2);
                break;
            case '/':
                op1 = pop(result_stack);
                op2 = pop(result_stack);
                push(result_stack, op2 / op1);
                break;
            default:
                push(result_stack, token);
                break;
        }
    }

    printf("%lf\n", pop(result_stack));
    return 0;
}

int get_operator_precedence(char operator) {
    switch(operator) {
        case '+':
        case '-':
            return 2;
        case '*':
            return 3;
        case '/':
            return 3;
        case '^':
            return 4;
    }
}

int get_operator_associativity(char operator) {
    switch(operator) {
        case '+':
        case '-':
        case '*':
        case '/':
            return LEFT_ASSOCIATE;
        case '^':
            return RIGHT_ASSOCIATE;
    }
}