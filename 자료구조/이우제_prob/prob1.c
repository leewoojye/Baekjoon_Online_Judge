#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STACK_SIZE 100

typedef char element;

typedef struct {
    element data[MAX_STACK_SIZE];
    int top;
} StackType;

void init_stack(StackType *s)
{
    s->top = -1;
}

int is_empty(StackType *s)
{
    return s->top == -1;
}

int is_full(StackType *s)
{
    return s->top == MAX_STACK_SIZE - 1;
}

void push(StackType *s, element item)
{
    if (is_full(s)) {
        fprintf(stderr, "Stack overflow\n");
        exit(1);
    }
    s->data[++(s->top)] = item;
}

element pop(StackType *s)
{
    if (is_empty(s)) {
        fprintf(stderr, "Stack underflow\n");
        exit(1);
    }
    return s->data[(s->top)--];
}

element peek(StackType *s)
{
    if (is_empty(s)) {
        fprintf(stderr, "Stack is empty\n");
        exit(1);
    }
    return s->data[s->top];
}

int prec(char op)
{
    switch (op) {
    case '(':
    case ')':
        return 0;
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
        return 2;
    }
    return -1;
}

char result[101] = {'\0'};
int idx = 0;

void infix_to_postfix(char exp[])
{
    char ch;
    char top_op;
    int len = (int)strlen(exp);
    StackType s;

    init_stack(&s);
    for (int i = 0; i < len; i++) {
        ch = exp[i];
        switch (ch) {
        case '+':
        case '-':
        case '*':
        case '/':
            while (!is_empty(&s) && prec(ch) <= prec(peek(&s))) {
                char pop_1 = pop(&s); // 수정
                printf("%c", pop_1);
                result[idx++] = pop_1;
            }
            push(&s, ch);
            break;
        case '(':
            push(&s, ch);
            break;
        case ')':
            top_op = pop(&s);
            while (top_op != '(') {
                printf("%c", top_op);
                result[idx++] = top_op; // 수정
                top_op = pop(&s);
            }
            break;
        default:
            printf("%c", ch);
            result[idx++] = ch; // 수정
            break;
        }
    }
    while (!is_empty(&s)) {
        char pop_2 = pop(&s); // 수정
        printf("%c", pop_2);
        result[idx++] = pop_2;
    }
}

int eval(char exp[])
{
    int op1;
    int op2;
    int value;
    int len = (int)strlen(exp);
    char ch;
    StackType s;

    init_stack(&s);
    for (int i = 0; i < len; i++) {
        ch = exp[i];
        if (ch != '+' && ch != '-' && ch != '*' && ch != '/') {
            value = ch - '0';
            push(&s, value);
        } else {
            op2 = pop(&s);
            op1 = pop(&s);
            switch (ch) {
            case '+':
                push(&s, op1 + op2);
                break;
            case '-':
                push(&s, op1 - op2);
                break;
            case '*':
                push(&s, op1 * op2);
                break;
            case '/':
                push(&s, op1 / op2);
                break;
            }
        }
    }
    return pop(&s);
}

int main(void)
{
    char *input = "7+8*(3-1)/2";

    printf("출력 : \n\n");
    printf("Infix expression: %s\n", input);
    printf("Postfix expression: ");
    infix_to_postfix(input);
    printf("\n");
    int final_result = eval(&result);
    printf("Calculation Result: %d\n", final_result);
    return 0;
}
