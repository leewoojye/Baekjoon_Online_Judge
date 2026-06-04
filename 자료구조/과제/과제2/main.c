#include <stdio.h>

#define MAX 100

typedef struct {
    int data[MAX];
    int top;
} StackType;

void print_2stacks(const StackType *stack1, const StackType *stack2);

// 스택을 빈 상태로 초기화한다.
void init_Stack(StackType *s) {
    s->top = -1;
}

// 스택이 비어 있는지 확인한다.
int is_empty(const StackType *s) {
    return s->top == -1;
}

// 스택이 가득 찼는지 확인한다.
int is_full(const StackType *s) {
    return s->top == MAX - 1;
}

// 스택 top에 값을 삽입하고 성공 여부를 반환한다.
int push(StackType *s, int value) {
    if (is_full(s)) {
        printf("push error\n");
        return 0;
    }
    s->data[++(s->top)] = value;
    return 1;
}

// 스택 top 값을 꺼내 value에 저장하고 성공 여부를 반환한다.
int pop(StackType *s, int *value) {
    if (is_empty(s)) {
        return 0;
    }
    *value = s->data[(s->top)--];
    return 1;
}

// 큐의 삽입 연산처럼 새 값을 입력 스택 stack1에 쌓는다.
void enqueue(StackType *stack1, StackType *stack2, int value) {
    push(stack1, value);

    printf("[ENQUEUE] %d\n", value);
    print_2stacks(stack1, stack2);
}

// 출력 스택이 비었을 때만 stack1의 값을 뒤집어 stack2로 옮긴 뒤 삭제한다.
int dequeue(StackType *stack1, StackType *stack2) {
    int value;

    printf("[DEQUEUE]\n");

    // stack1의 값을 stack2로 옮기면 가장 먼저 들어온 값이 stack2의 top에 온다.
    if (is_empty(stack2)) {
        while (!is_empty(stack1)) {
            pop(stack1, &value);
            push(stack2, value);
        }
    }

    // stack2에서 pop하면 큐의 front 삭제와 같은 결과가 된다.
    if (pop(stack2, &value)) {
        printf("Returned: %d\n", value);
    } else {
        printf("queue is empty\n");
        value = -1;
    }

    print_2stacks(stack1, stack2);
    return value;
}

// 스택 하나의 내용을 bottom부터 top까지 출력한다.
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

// 두 스택의 현재 상태를 함께 출력한다.
void print_2stacks(const StackType *stack1, const StackType *stack2) {
    print_stack("stack1", stack1);
    print_stack("stack2", stack2);
    printf("\n");
}

// operations 배열을 순서대로 처리하며 두 스택 큐의 동작을 시연한다.
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

    // 양수는 enqueue, -1은 dequeue로 해석해 순서대로 실행한다.
    for (int i = 0; i < size; i++) {
        if (operations[i] > 0) {
            enqueue(&stack1, &stack2, operations[i]);
        } else if (operations[i] == -1) {
            dequeue(&stack1, &stack2);
        }
    }

    return 0;
}
