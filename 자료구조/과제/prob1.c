#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_EXPR_SIZE 100
#define MAX_STACK_SIZE 100

typedef struct {
    char data[MAX_STACK_SIZE];
    int top;
} CharStack;

typedef struct {
    int data[MAX_STACK_SIZE];
    int top;
} IntStack;

static void error(const char *message)
{
    fprintf(stderr, "%s\n", message);
    exit(1);
}

static int is_operator(char ch)
{
    return ch == '+' || ch == '-' || ch == '*' || ch == '/';
}

static int precedence(char op)
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

static void init_char_stack(CharStack *s)
{
    s->top = -1;
}

static int is_empty_char(CharStack *s)
{
    return s->top == -1;
}

static int is_full_char(CharStack *s)
{
    return s->top == MAX_STACK_SIZE - 1;
}

static void push_char(CharStack *s, char item)
{
    if (is_full_char(s)) {
        error("char stack overflow");
    }
    s->data[++s->top] = item;
}

static char pop_char(CharStack *s)
{
    if (is_empty_char(s)) {
        error("char stack underflow");
    }
    return s->data[s->top--];
}

static char peek_char(CharStack *s)
{
    if (is_empty_char(s)) {
        error("char stack is empty");
    }
    return s->data[s->top];
}

static void init_int_stack(IntStack *s)
{
    s->top = -1;
}

static int is_empty_int(IntStack *s)
{
    return s->top == -1;
}

static int is_full_int(IntStack *s)
{
    return s->top == MAX_STACK_SIZE - 1;
}

static void push_int(IntStack *s, int item)
{
    if (is_full_int(s)) {
        error("int stack overflow");
    }
    s->data[++s->top] = item;
}

static int pop_int(IntStack *s)
{
    if (is_empty_int(s)) {
        error("int stack underflow");
    }
    return s->data[s->top--];
}

static void infix_to_postfix(const char input[], char postfix[])
{
    CharStack s;
    int j = 0;

    init_char_stack(&s);

    for (int i = 0; input[i] != '\0'; i++) {
        char ch = input[i];

        if (isdigit((unsigned char)ch)) {
            postfix[j++] = ch;
        } else if (ch == '(') {
            push_char(&s, ch);
        } else if (ch == ')') {
            while (!is_empty_char(&s) && peek_char(&s) != '(') {
                postfix[j++] = pop_char(&s);
            }
            if (is_empty_char(&s)) {
                error("wrong expression");
            }
            pop_char(&s);
        } else if (is_operator(ch)) {
            while (!is_empty_char(&s) && precedence(peek_char(&s)) >= precedence(ch)) {
                postfix[j++] = pop_char(&s);
            }
            push_char(&s, ch);
        }
    }

    while (!is_empty_char(&s)) {
        char op = pop_char(&s);

        if (op == '(') {
            error("wrong expression");
        }
        postfix[j++] = op;
    }
    postfix[j] = '\0';
}

static int calculate_postfix(const char postfix[])
{
    IntStack s;

    init_int_stack(&s);

    for (int i = 0; postfix[i] != '\0'; i++) {
        char ch = postfix[i];

        if (isdigit((unsigned char)ch)) {
            push_int(&s, ch - '0');
        } else if (is_operator(ch)) {
            int op2 = pop_int(&s);
            int op1 = pop_int(&s);

            switch (ch) {
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
                if (op2 == 0) {
                    error("division by zero");
                }
                push_int(&s, op1 / op2);
                break;
            }
        }
    }
    return pop_int(&s);
}

int main(void)
{
    char input[] = "7+8*(3-1)/2";
    char postfix[MAX_EXPR_SIZE];
    int result;

    infix_to_postfix(input, postfix);
    result = calculate_postfix(postfix);

    printf("Infix Expression: %s\n", input);
    printf("Postfix Expression: %s\n", postfix);
    printf("Calculation Result: %d\n", result);
    return 0;
}
