#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Operation {
    char url[50];
    char timestamp[50];
} Op;

typedef struct Stack {
    Op *ops;
    int top;
    int cap;
} Stack;

Stack *createStack(int capacity) {
    Stack *stack = (Stack *) malloc(sizeof(Stack));
    stack->ops = (Op *) malloc(sizeof(Op) * capacity);
    stack->top = -1;;
    stack->cap = capacity;
    return stack;
}


Op createOp() {
    Op op;
    fflush(stdin);
    printf("Enter Op url: ");
    fgets(op.url, sizeof(op.url), stdin);
    op.url[strcspn(op.url, "\n")] = '\0';
    printf("Enter Op timestamp: ");
    fgets(op.timestamp, sizeof(op.timestamp), stdin);
    op.timestamp[strcspn(op.timestamp, "\n")] = '\0';
    return op;
}

void push(Stack *stack, Op op) {
    if (stack->top == stack->cap - 1) {
        printf("Stack is full");
        return;
    }
    stack->top++;
    stack->ops[stack->top] = op;
}

Op pop(Stack *stack) {
    if (stack->top == -1) {
        printf("Stack is empty");
        exit(0);
    }
    Op curr = stack->ops[stack->top];
    stack->top--;
    return curr;
}

void showCurrent(Stack *stack) {
    if (stack->top == -1) {
        printf("Stack is empty");
        return;
    }
    printf("URL: %s\nTimestamp: %s\n", stack->ops[stack->top].url, stack->ops[stack->top].timestamp);
}

int main(void) {
    int choice;
    Stack *Back = createStack(10);
    Stack *Forward = createStack(10);
    do {
        printf("1. Visit\n");
        printf("2. Backward\n");
        printf("3. Forward\n");
        printf("4. Current\n");
        printf("0. Exit\n");
        printf("Your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                push(Back, createOp());
                break;
            case 2:
                push(Forward, pop(Back));
                break;
            case 3:
                push(Back, pop(Forward));
                break;
            case 4:
                showCurrent(Back);
                break;
        }
    } while (choice != 0);
    exit(0);
}