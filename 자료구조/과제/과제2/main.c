#include <stdio.h>

#define MAX 100

typedef struct {
    int data[MAX];
    int top;
} StackType;

void print_2stacks(const StackType *stack1, const StackType *stack2);

void init_Stack(StackType *s) {
    s->top = -1;
}

int is_empty(const StackType *s) {
    return s->top == -1;
}

int is_full(const StackType *s) {
    return s->top == MAX - 1;
}

int push(StackType *s, int value) {
    if (is_full(s)) {
        printf("push error\n");
        return 0;
    }
    s->data[++(s->top)] = value;
    return 1;
}

int pop(StackType *s, int *value) {
    if (is_empty(s)) {
        return 0;
    }
    *value = s->data[(s->top)--];
    return 1;
}

void enqueue(StackType *stack1, StackType *stack2, int value) {
    push(stack1, value);

    printf("[ENQUEUE] %d\n", value);
    print_2stacks(stack1, stack2);
}

int dequeue(StackType *stack1, StackType *stack2) {
    int value;

    printf("[DEQUEUE]\n");

    if (is_empty(stack2)) {
        while (!is_empty(stack1)) {
            pop(stack1, &value);
            push(stack2, value);
        }
    }

    if (pop(stack2, &value)) {
        printf("Returned: %d\n", value);
    } else {
        printf("queue is empty\n");
        value = -1;
    }

    print_2stacks(stack1, stack2);
    return value;
}

void print_stack(const char *name, const StackType *s) {
    printf("%s [bottom -> top]: ", name);

    if (is_empty(s)) {
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

void print_2stacks(const StackType *stack1, const StackType *stack2) {
    print_stack("stack1", stack1);
    print_stack("stack2", stack2);
    printf("\n");
}

int main(void) {
    StackType stack1;
    StackType stack2;
    int operations[] = { 10, 20, 30, -1, 40, 50, -1, -1, 60, -1, -1, -1 };
    int size = (int)(sizeof(operations) / sizeof(operations[0]));

    init_Stack(&stack1);
    init_Stack(&stack2);

    printf("입력값 (양의 정수: enqueue, -1: dequeue): { ");
    for (int i = 0; i < size; i++) {
        printf("%d", operations[i]);
        if (i < size - 1) {
            printf(" ");
        }
    }
    printf(" }\n\n");

    for (int i = 0; i < size; i++) {
        if (operations[i] > 0) {
            enqueue(&stack1, &stack2, operations[i]);
        } else if (operations[i] == -1) {
            dequeue(&stack1, &stack2);
        }
    }

    return 0;
}
