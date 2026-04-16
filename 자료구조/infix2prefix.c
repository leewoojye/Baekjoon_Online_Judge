#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// <ctype.h> 제거됨

#define MAX 100

// 스택 구조체
typedef struct {
    char data[MAX];
    int top;
} Stack;

void init(Stack* s) { s->top = -1; }
int isEmpty(Stack* s) { return s->top == -1; }
void push(Stack* s, char c) { s->data[++(s->top)] = c; }
char pop(Stack* s) { return s->data[(s->top)--]; }
char peek(Stack* s) { return s->data[s->top]; }

// 💡 커스텀 피연산자 확인 함수 (isalnum 대체)
int isOperand(char c) {
    return ((c >= 'A' && c <= 'Z') || 
            (c >= 'a' && c <= 'z') || 
            (c >= '0' && c <= '9'));
}

// 연산자 우선순위 반환
int precedence(char op) {
    if (op == '*' || op == '/') return 2;
    if (op == '+' || op == '-') return 1;
    return 0;
}

// 문자열 뒤집기 및 괄호 방향 전환
void reverse_and_swap_brackets(char* exp) {
    int len = strlen(exp);
    for (int i = 0; i < len / 2; i++) {
        char temp = exp[i];
        exp[i] = exp[len - i - 1];
        exp[len - i - 1] = temp;
    }
    for (int i = 0; i < len; i++) {
        if (exp[i] == '(') exp[i] = ')';
        else if (exp[i] == ')') exp[i] = '(';
    }
}

// 문자열 단순 뒤집기
void reverse(char* exp) {
    int len = strlen(exp);
    for (int i = 0; i < len / 2; i++) {
        char temp = exp[i];
        exp[i] = exp[len - i - 1];
        exp[len - i - 1] = temp;
    }
}

// 중위를 전위로 변환
void infixToPrefix(char* infix, char* prefix) {
    Stack s;
    init(&s);
    int p_idx = 0;
    
    reverse_and_swap_brackets(infix);
    
    for (int i = 0; infix[i] != '\0'; i++) {
        char c = infix[i];
        
        // 💡 isalnum(c) 대신 직접 만든 isOperand(c) 사용
        if (isOperand(c)) {
            prefix[p_idx++] = c;
        } 
        else if (c == '(') {
            push(&s, c);
        } 
        else if (c == ')') {
            while (!isEmpty(&s) && peek(&s) != '(') {
                prefix[p_idx++] = pop(&s);
            }
            pop(&s);
        } 
        else {
            while (!isEmpty(&s) && precedence(peek(&s)) > precedence(c)) {
                prefix[p_idx++] = pop(&s);
            }
            push(&s, c);
        }
    }
    
    while (!isEmpty(&s)) {
        prefix[p_idx++] = pop(&s);
    }
    prefix[p_idx] = '\0';
    
    reverse(prefix);
}

int main() {
    char infix[MAX] = "A+B*C-D/E"; 
    char prefix[MAX];
    
    infixToPrefix(infix, prefix);
    
    printf("중위 표기식(Infix): A+B*C-D/E\n"); 
    printf("전위 표기식(Prefix): %s\n", prefix);
    
    return 0;
}