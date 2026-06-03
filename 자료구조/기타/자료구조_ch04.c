#include <stdio.h>
#include <stdlib.h>

#define MAX_LENGTH 51 
typedef char element;
typedef struct {
  int top;
  element data[MAX_LENGTH];
} stack;

void init_stack(stack *s) {
  s->top = -1;
  for(int i=0;i<51;++i) {
    s->data[i] = '\0';
  }
  return;
}

void push_stack(stack *s, element value) {
  s->data[++(s->top)] = value;
  return;
}

element pop_stack(stack *s) {
  if (s->top == -1) return '\0';
  element backoff;
  backoff = s->data[s->top];
  s->data[(s->top)--] = '\0'; // stack, queue는 변수 front, rear가 데이터 범위를 알려주므로 범위를 널문자로 판단할 이유는 없음
  return backoff;
}

int main()
{
  int num, idx;
  scanf("%d", &num);
  stack s; // 스택 영역에 구조체 선언
  for(int i=0;i<num;++i) {
    int flag = 1;
    char arr[MAX_LENGTH] = {'\0'};
    init_stack(&s);
    // fgets(s.data, sizeof(s.data), stdin) != NULL // 입력이 끝날 때까지 문자열(줄 단위)을 입력받으며 종료를 위해 EOF 신호를 줘야함
    scanf("%s", arr);
    for(int idx=0;arr[idx]!='\0';++idx) {
      char current_c = arr[idx];
      char pop_c;
      if(current_c == '(') push_stack(&s, current_c);
      else if(current_c == ')') {
        pop_c = pop_stack(&s);
        if (pop_c == '\0') { flag = 0; break; }
      }
    }
    if(s.top != -1) flag = 0;
    (flag == 0) ? printf("NO\n") : printf("YES\n");
  }
  return 0;
}