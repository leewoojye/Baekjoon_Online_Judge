#include <stdio.h>

#define MAX 100

typedef struct {
    int data[MAX];
    int top;
} Stack;

void initStack(Stack *s) {
    s->top = -1;
}

int isEmpty(const Stack *s) {
    return s->top == -1;
}

int isFull(const Stack *s) {
    return s->top == MAX - 1;
}

int push(Stack *s, int value) {
    if (isFull(s)) {
        printf("push error\n");
        return 0;
    }
    s->data[++(s->top)] = value;
    return 1;
}

int pop(Stack *s, int *value) {
    if (isEmpty(s)) {
        return 0;
    }
    *value = s->data[(s->top)--];
    return 1;
}

void printStack(const char *name, const Stack *s) {
    printf("%s [bottom -> top]: ", name);

    if (isEmpty(s)) {
        printf("(empty)");
    } else {
        for (int i = 0; i <= s->top; i++) {
            printf("%d", s->data[i]);
            if (i < s->top) {
                printf(" ");
            }
        }
    }
    printf("\n");
}

void printQueueState(const Stack *stack1, const Stack *stack2) {
    printStack("stack1", stack1);
    printStack("stack2", stack2);
    printf("\n");
}

void enqueue(Stack *stack1, Stack *stack2, int value) {
    push(stack1, value);

    printf("[ENQUEUE] %d\n", value);
    printQueueState(stack1, stack2);
}

int dequeue(Stack *stack1, Stack *stack2) {
    int value;

    printf("[DEQUEUE]\n");

    if (isEmpty(stack2)) {
        while (!isEmpty(stack1)) {
            pop(stack1, &value);
            push(stack2, value);
        }
    }

    if (pop(stack2, &value)) {
        printf("Returned: %d\n", value);
    } else {
        printf("Returned: Queue is empty\n");
        value = -1;
    }

    printQueueState(stack1, stack2);
    return value;
}

void printOperations(const int operations[], int size) {
    printf("입력값 (양의 정수: enqueue, -1: dequeue): { ");
    for (int i = 0; i < size; i++) {
        printf("%d", operations[i]);
        if (i < size - 1) {
            printf(" ");
        }
    }
    printf(" }\n\n");
}

int main(void) {
    Stack stack1;
    Stack stack2;
    int operations[] = { 10, 20, 30, -1, 40, 50, -1, -1, 60, -1, -1, -1 };
    int size = (int)(sizeof(operations) / sizeof(operations[0]));

    initStack(&stack1);
    initStack(&stack2);

    printOperations(operations, size);

    for (int i = 0; i < size; i++) {
        if (operations[i] > 0) {
            enqueue(&stack1, &stack2, operations[i]);
        } else if (operations[i] == -1) {
            dequeue(&stack1, &stack2);
        }
    }

    return 0;
}
