#include <stdio.h>
#include <stdlib.h>

typedef int element;

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

int is_full(LinkedStackType *s)
{
    (void)s;
    return 0;
}

void print_stack(LinkedStackType *s)
{
    StackNode *p;

    for (p = s->top; p != NULL; p = p->link) {
        printf("%d->", p->data);
    }
    printf("NULL\n");
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
        fprintf(stderr, "스택이 비어있음\n");
        exit(1);
    }
    temp = s->top;
    data = temp->data;
    s->top = s->top->link;
    free(temp);
    return data;
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
    push(&s, 1);
    print_stack(&s);
    push(&s, 2);
    print_stack(&s);
    push(&s, 3);
    print_stack(&s);
    pop(&s);
    print_stack(&s);
    pop(&s);
    print_stack(&s);
    pop(&s);
    print_stack(&s);

    destroy_stack(&s);
    return 0;
}
