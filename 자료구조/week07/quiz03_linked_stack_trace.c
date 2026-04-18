/*
Quiz
1. 연결 리스트로 스택을 구현하는 경우의 장점은?
2. 연결 리스트로 구현된 스택의 경우 top 변수의 의미는 무엇인가?
3. push(a), push(b), push(c), pop(), push(d)

예시 답안
1. 미리 큰 배열을 잡아둘 필요가 없고, 필요한 만큼 동적으로 노드를 늘릴 수 있다.
2. top은 스택의 가장 위 노드를 가리키는 포인터이다.
3. 연산 결과
   push(a) -> a
   push(b) -> b -> a
   push(c) -> c -> b -> a
   pop()   -> c 제거, b -> a
   push(d) -> d -> b -> a
*/

#include <stdio.h>
#include <stdlib.h>

typedef char element;

typedef struct StackNode {
    element data;
    struct StackNode *link;
} StackNode;

typedef struct {
    StackNode *top;
} LinkedStackType;

void init(LinkedStackType *s)
{
    s->top = NULL;
}

int is_empty(LinkedStackType *s)
{
    return s->top == NULL;
}

void push(LinkedStackType *s, element item)
{
    StackNode *temp = (StackNode *)malloc(sizeof(StackNode));

    if (temp == NULL) {
        fprintf(stderr, "Memory allocation error\n");
        exit(1);
    }
    temp->data = item;
    temp->link = s->top;
    s->top = temp;
}

element pop(LinkedStackType *s)
{
    StackNode *temp;
    element data;

    if (is_empty(s)) {
        fprintf(stderr, "stack underflow\n");
        exit(1);
    }
    temp = s->top;
    data = temp->data;
    s->top = temp->link;
    free(temp);
    return data;
}

void print_stack(LinkedStackType *s, const char *label)
{
    StackNode *p;

    printf("%-12s top=%p | ", label, (void *)s->top);
    for (p = s->top; p != NULL; p = p->link) {
        printf("%c -> ", p->data);
    }
    printf("NULL\n");
}

void destroy_stack(LinkedStackType *s)
{
    while (!is_empty(s)) {
        pop(s);
    }
}

int main(void)
{
    LinkedStackType s;

    init(&s);
    printf("장점: 필요한 만큼만 동적 할당하므로 배열 크기를 미리 고정할 필요가 없습니다.\n");
    printf("top 의미: 가장 위 노드를 가리키는 포인터입니다.\n\n");

    push(&s, 'a');
    print_stack(&s, "push(a)");
    push(&s, 'b');
    print_stack(&s, "push(b)");
    push(&s, 'c');
    print_stack(&s, "push(c)");
    printf("pop() -> %c\n", pop(&s));
    print_stack(&s, "after pop");
    push(&s, 'd');
    print_stack(&s, "push(d)");

    destroy_stack(&s);
    return 0;
}
