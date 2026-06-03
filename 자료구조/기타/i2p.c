#include <stdio.h>
#include <stdlib.h>

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
        return;
    }
    s->data[++(s->top)] = item;
}

element pop(StackType *s) {
    if (is_empty(s)) {
        fprintf(stderr, "Stack underflow\n");
        exit(1);
    }
    return s->data[(s->top)--];
}

element peek(StackType *s) {
    if (is_empty(s)) {
        fprintf(stderr, "Stack underflow\n");
        exit(1);
    }
    return s->data[s->top];
}

int pri(char ch) {
  switch(ch) {
    case '(': case ')':
    return 0; break;
    case '+': case '-':
    return 1;
    case '*': case '/':
    return 2;
  }
  return 0;
}

int main() {
  StackType s;
  init_stack(&s);
  char *in="a+b*c";
  char pop_c;
  for(int i=0;in[i]!='\0';i++)
  {
    char current_c=in[i];
    switch(current_c) {
      case '+': case '-': case '*': case '/':
      while(!is_empty(&s) && pri(peek(&s))>=pri(current_c)) {
        pop_c=pop(&s);
        printf("%c",pop_c);
      }
      push(&s,current_c);
      break;
      case '(':
      push(&s,current_c);
      break;
      case ')':
      do {
        pop_c=pop(&s);
        printf("%c",pop_c);
      } while(pop_c!='(');
      break;
      default:
      printf("%c",current_c);
      break;
    }
  }
  while(!is_empty(&s)) {
    char pop_c=pop(&s);
    printf("%c",pop_c);
  }
  return 0;
}