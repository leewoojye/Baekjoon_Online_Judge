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

// void infix_to_postfix(char exp[])
// {
//     char ch;
//     char top_op;
//     int len = (int)strlen(exp);
//     StackType s;

//     init_stack(&s);
//     for (int i = 0; i < len; i++) {
//         ch = exp[i];
//         switch (ch) {
//         case '+':
//         case '-':
//         case '*':
//         case '/':
//             while (!is_empty(&s) && prec(ch) <= prec(peek(&s))) {
//                 printf("%c", pop(&s));
//             }
//             push(&s, ch);
//             break;
//         case '(':
//             push(&s, ch);
//             break;
//         case ')':
//             top_op = pop(&s);
//             while (top_op != '(') {
//                 printf("%c", top_op);
//                 top_op = pop(&s);
//             }
//             break;
//         default:
//             printf("%c", ch);
//             break;
//         }
//     }
//     while (!is_empty(&s)) {
//         printf("%c", pop(&s));
//     }
// }

void infix_to_postfix(char exp[]) {
    StackType s;
    init_stack(&s);
    char ch;
    char top_ch;
    int n = strlen(exp);
    // printf("%d",n);
    for(int i=0;i<n;i++) {
        ch=exp[i];
        switch(ch) {
            case '*': 
            case '/': 
            case '+': 
            case '-':
            while(!is_empty(&s) && prec(peek(&s))>=prec(ch)) {
                top_ch=pop(&s);
                printf("%c",top_ch);
            }
            push(&s,ch); // push 잊지마 ..
            break;
            case ')':
            top_ch=pop(&s);
            while(top_ch!='(') {
                printf("%c",top_ch);
                top_ch=pop(&s);
            }
            break;
            case '(':
            push(&s,ch);
            break;
            default:
            printf("%c",ch);
            break;
        }
    }
    while(!is_empty(&s)) {
        printf("%c",pop(&s));
    }
}

int main(void)
{
    char *s = "a*(b+c)";

    printf("Infix expression: %s\n", s);
    printf("Postfix expression: ");
    infix_to_postfix(s);
    printf("\n");
    return 0;
}
