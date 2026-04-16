/*
Quiz
다음과 같은 수식이 스택을 이용하여서 어떻게 처리되는지 설명하라.
1. (a+b)*k[2+3*n]
2. [(2+10)*u]/3 ]

예시 답안
- 1번 식은 괄호와 대괄호가 모두 올바르게 짝지어져 있으므로 valid 이다.
- 2번 식은 마지막에 ']' 가 하나 더 있으므로 invalid 이다.
- 아래 코드는 스택 기반 괄호 검사 예시이다.
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_STACK_SIZE 100

typedef struct {
    char data[MAX_STACK_SIZE];
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

void push(StackType *s, char item)
{
    s->data[++(s->top)] = item;
}

char pop(StackType *s)
{
    return s->data[(s->top)--];
}

int check_matching(const char *expr)
{
    StackType s;

    init_stack(&s);
    for (int i = 0; expr[i] != '\0'; i++) {
        char ch = expr[i];

        switch (ch) {
        case '(':
        case '[':
        case '{':
            push(&s, ch);
            break;
        case ')':
        case ']':
        case '}':
            if (is_empty(&s)) {
                return 0;
            }
            {
                char open = pop(&s);
                if ((open == '(' && ch != ')') ||
                    (open == '[' && ch != ']') ||
                    (open == '{' && ch != '}')) {
                    return 0;
                }
            }
            break;
        }
    }
    return is_empty(&s);
}

int main(void)
{
    const char *expr1 = "(a+b)*k[2+3*n]";
    const char *expr2 = "[(2+10)*u]/3 ]";

    printf("%s -> %s\n", expr1, check_matching(expr1) ? "valid" : "invalid");
    printf("%s -> %s\n", expr2, check_matching(expr2) ? "valid" : "invalid");
    return 0;
}
