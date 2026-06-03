#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// <ctype.h> 제거됨

#define MAX 100

// 문자열 스택 구조체
typedef struct {
    char data[MAX][MAX];
    int top;
} StringStack;

void init(StringStack* s) { s->top = -1; }
int isEmpty(StringStack* s) { return s->top == -1; }

void push(StringStack* s, char* str) {
    strcpy(s->data[++(s->top)], str);
}

void pop(StringStack* s, char* target) {
    strcpy(target, s->data[(s->top)--]);
}

// 💡 커스텀 피연산자 확인 함수 (isalnum 대체)
int isOperand(char c) {
    return ((c >= 'A' && c <= 'Z') || 
            (c >= 'a' && c <= 'z') || 
            (c >= '0' && c <= '9'));
}

// 연산자인지 확인
int isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

// 후위를 전위로 변환
void postfixToPrefix(char* postfix) {
    StringStack s;
    init(&s);
    
    for (int i = 0; postfix[i] != '\0'; i++) {
        char c = postfix[i];
        
        // 💡 isalnum(c) 대신 직접 만든 isOperand(c) 사용
        if (isOperand(c)) {
            char temp[2] = {c, '\0'};
            push(&s, temp);
        }
        else if (isOperator(c)) {
            char op1[MAX], op2[MAX], result[MAX];
            
            pop(&s, op1);
            pop(&s, op2);
            
            result[0] = c;
            result[1] = '\0';
            strcat(result, op2);
            strcat(result, op1);
            
            push(&s, result);
        }
    }
    
    char prefix[MAX];
    pop(&s, prefix);
    printf("전위 표기식(Prefix): %s\n", prefix);
}

int main() {
    char postfix[MAX] = "ABC*+DE/-"; 
    
    printf("후위 표기식(Postfix): %s\n", postfix);
    postfixToPrefix(postfix); 
    
    return 0;
}