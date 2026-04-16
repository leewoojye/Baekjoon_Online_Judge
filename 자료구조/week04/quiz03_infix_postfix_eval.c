/*
Quiz
스택을 사용하여 다음 중위 수식을 후위 수식으로 변경하고 수식의 값을 계산하라.
5*(10+2)/2

예시 답안
- 후위 수식: 5 10 2 + * 2 /
- 계산 결과: 30
- 아래 코드는 다자리 정수를 처리할 수 있는 간단한 변환/계산 예시이다.
*/

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EXPR_SIZE 256
#define MAX_STACK_SIZE 100

typedef struct {
    char data[MAX_STACK_SIZE];
    int top;
} OpStack;

typedef struct {
    int data[MAX_STACK_SIZE];
    int top;
} IntStack;

void init_op_stack(OpStack *s)
{
    s->top = -1;
}

void init_int_stack(IntStack *s)
{
    s->top = -1;
}

int is_op_empty(OpStack *s)
{
    return s->top == -1;
}

void push_op(OpStack *s, char item)
{
    s->data[++(s->top)] = item;
}

char pop_op(OpStack *s)
{
    return s->data[(s->top)--];
}

char peek_op(OpStack *s)
{
    return s->data[s->top];
}

void push_int(IntStack *s, int item)
{
    s->data[++(s->top)] = item;
}

int pop_int(IntStack *s)
{
    return s->data[(s->top)--];
}

int precedence(char op)
{
    switch (op) {
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
        return 2;
    default:
        return 0;
    }
}

void append_token(char *postfix, int *pos, const char *token)
{
    int len = (int)strlen(token);

    memcpy(postfix + *pos, token, (size_t)len);
    *pos += len;
    postfix[(*pos)++] = ' ';
    postfix[*pos] = '\0';
}

void infix_to_postfix(const char *infix, char *postfix)
{
    OpStack s;
    int pos = 0;

    init_op_stack(&s);
    postfix[0] = '\0';

    for (int i = 0; infix[i] != '\0';) {
        if (isspace((unsigned char)infix[i])) {
            i++;
        } else if (isdigit((unsigned char)infix[i])) {
            char number[32];
            int j = 0;

            while (isdigit((unsigned char)infix[i])) {
                number[j++] = infix[i++];
            }
            number[j] = '\0';
            append_token(postfix, &pos, number);
        } else if (infix[i] == '(') {
            push_op(&s, infix[i++]);
        } else if (infix[i] == ')') {
            while (!is_op_empty(&s) && peek_op(&s) != '(') {
                char op[2] = {pop_op(&s), '\0'};
                append_token(postfix, &pos, op);
            }
            pop_op(&s);
            i++;
        } else {
            char current = infix[i++];

            while (!is_op_empty(&s) && precedence(current) <= precedence(peek_op(&s))) {
                char op[2] = {pop_op(&s), '\0'};
                append_token(postfix, &pos, op);
            }
            push_op(&s, current);
        }
    }

    while (!is_op_empty(&s)) {
        char op[2] = {pop_op(&s), '\0'};
        append_token(postfix, &pos, op);
    }
}

int eval_postfix(const char *postfix)
{
    IntStack s;
    char buffer[MAX_EXPR_SIZE];
    char *token;

    init_int_stack(&s);
    strncpy(buffer, postfix, sizeof(buffer) - 1);
    buffer[sizeof(buffer) - 1] = '\0';

    token = strtok(buffer, " ");
    while (token != NULL) {
        if (isdigit((unsigned char)token[0])) {
            push_int(&s, atoi(token));
        } else {
            int op2 = pop_int(&s);
            int op1 = pop_int(&s);

            switch (token[0]) {
            case '+':
                push_int(&s, op1 + op2);
                break;
            case '-':
                push_int(&s, op1 - op2);
                break;
            case '*':
                push_int(&s, op1 * op2);
                break;
            case '/':
                push_int(&s, op1 / op2);
                break;
            }
        }
        token = strtok(NULL, " ");
    }
    return pop_int(&s);
}

int main(void)
{
    const char *infix = "5*(10+2)/2";
    char postfix[MAX_EXPR_SIZE];

    infix_to_postfix(infix, postfix);
    printf("infix   : %s\n", infix);
    printf("postfix : %s\n", postfix);
    printf("result  : %d\n", eval_postfix(postfix));
    return 0;
}
