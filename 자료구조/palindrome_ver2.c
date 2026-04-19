#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> // tolower() 함수를 사용하기 위한 헤더

#define MAX_STACK_SIZE 100

typedef char element; // 문자열을 다루므로 char형으로 설정

typedef struct {
    element data[MAX_STACK_SIZE];
    int top;
} StackType;

// 스택 초기화 함수
void init_stack(StackType *s) {
    s->top = -1;
}

// 공백 상태 검출 함수
int is_empty(StackType *s) {
    return (s->top == -1);
}

// 포화 상태 검출 함수
int is_full(StackType *s) {
    return (s->top == (MAX_STACK_SIZE - 1));
}

// 삽입 함수
void push(StackType *s, element item) {
    if (is_full(s)) {
        fprintf(stderr, "스택 포화 에러\n");
        return;
    }
    else s->data[++(s->top)] = item;
}

// 삭제 함수
element pop(StackType *s) {
    if (is_empty(s)) {
        fprintf(stderr, "스택 공백 에러\n");
        exit(1);
    }
    else return s->data[(s->top)--];
}

// 회문 판별 함수
int check_palindrome(char *str) {
    StackType s;
    init_stack(&s);
    
    // strlen 없이 널 문자를 만날 때까지 처리하는 방식 적용
    int i = 0;
    
    // 1. 모든 문자를 소문자로 변경하면서 스택에 삽입
    while (str[i] != '\0') {
        str[i] = tolower(str[i]); // 대문자를 소문자로 변환
        push(&s, str[i]);
        i++;
    }
    
    // 2. 스택에서 하나씩 꺼내면서 앞에서부터 다시 비교
    i = 0;
    while (str[i] != '\0') {
        if (pop(&s) != str[i]) {
            return 0; // 한 글자라도 다르면 회문이 아님 (거짓 반환)
        }
        i++;
    }
    
    return 1; // 끝까지 모두 통과하면 회문임 (참 반환)
}

int main(void) {
    char str[MAX_STACK_SIZE];

    printf("문자열을 입력하시오: ");
    scanf("%s", str); // 공백 없는 단어 입력 받기

    if (check_palindrome(str)) {
        printf("회문입니다.\n");
    } else {
        printf("회문이 아닙니다.\n");
    }

    return 0;
}