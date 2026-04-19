#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STACK_SIZE 101

typedef char element;
typedef struct stacktype {
  element data[MAX_STACK_SIZE];
  int top;
} stacktype;

void init_stack(stacktype *s) {
  s->top=-1;
}

int is_empty(stacktype *s) {
  return s->top==-1;
}

int is_full(stacktype *s) {
  return s->top==MAX_STACK_SIZE-1;
}

void push(stacktype *s, element e) {
  if(is_full(&s)) return;
  s->data[++(s->top)]=e;
}

element pop(stacktype *s) {
  if(is_empty(&s)) return 0;
  return s->data[(s->top)--];
}

int main() {
  char input[MAX_STACK_SIZE];
  scanf("%s",input);
  stacktype s;
  init_stack(&s);
  int n=strlen(input);
  for(int i=0;i<n/2;i++) {
    push(&s,input[i]);
  }
  for(int i=(n+1)/2;i<n;i++) {
    if(pop(&s)!=input[i]) {
      printf("회문이 아님");
      return 0;
    }
  }
  if(!is_empty(&s)) {
    printf("회문이 아님");
    return 0;
  }
  printf("회문임");
  return 0;
}