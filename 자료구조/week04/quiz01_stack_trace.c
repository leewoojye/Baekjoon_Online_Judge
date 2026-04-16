/*
Quiz
1. 스택을 사용하여서 a,b,c,d,e를 입력하여서 b,c,e,d,a와 같은 출력을
   얻으려면 입력과 출력의 순서를 어떻게 해야 하는가?
2. 크기가 5인 배열로 구현된 스택 A에서 다음과 같이 삽입과 삭제가
   되풀이되었을 경우 각 단계에서의 스택의 내용과 top의 값을 나타내시오.
   Push(A,1), Push(A,2), Push(A,3), Pop(A), Push(A,4), Push(A,5), Pop(A)

예시 답안
1. 가능한 연산 순서
   push(a), push(b), pop()->b,
   push(c), pop()->c,
   push(d), push(e), pop()->e, pop()->d, pop()->a
2. 아래 코드가 각 단계의 배열 상태와 top 값을 출력한다.
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_STACK_SIZE 5

typedef struct {
    char data[MAX_STACK_SIZE];
    int top;
} CharStack;

typedef struct {
    int data[MAX_STACK_SIZE];
    int top;
} IntStack;

void init_char_stack(CharStack *s)
{
    s->top = -1;
}

void push_char(CharStack *s, char item)
{
    s->data[++(s->top)] = item;
}

char pop_char(CharStack *s)
{
    return s->data[(s->top)--];
}

void init_int_stack(IntStack *s)
{
    s->top = -1;
}

void print_int_stack_state(const char *label, IntStack *s)
{
    printf("%-10s top=%d | ", label, s->top);
    for (int i = 0; i < MAX_STACK_SIZE; i++) {
        if (i <= s->top) {
            printf("%d ", s->data[i]);
        } else {
            printf("_ ");
        }
    }
    printf("\n");
}

void push_int(IntStack *s, int item, const char *label)
{
    s->data[++(s->top)] = item;
    print_int_stack_state(label, s);
}

int pop_int(IntStack *s, const char *label)
{
    int value = s->data[(s->top)--];

    print_int_stack_state(label, s);
    return value;
}

int main(void)
{
    CharStack q1;
    IntStack q2;

    init_char_stack(&q1);
    push_char(&q1, 'a');
    push_char(&q1, 'b');
    printf("Q1 output: %c", pop_char(&q1));
    push_char(&q1, 'c');
    printf("%c", pop_char(&q1));
    push_char(&q1, 'd');
    push_char(&q1, 'e');
    printf("%c%c%c\n", pop_char(&q1), pop_char(&q1), pop_char(&q1));

    init_int_stack(&q2);
    print_int_stack_state("initial", &q2);
    push_int(&q2, 1, "push 1");
    push_int(&q2, 2, "push 2");
    push_int(&q2, 3, "push 3");
    printf("pop -> %d\n", pop_int(&q2, "after pop"));
    push_int(&q2, 4, "push 4");
    push_int(&q2, 5, "push 5");
    printf("pop -> %d\n", pop_int(&q2, "after pop"));
    return 0;
}
