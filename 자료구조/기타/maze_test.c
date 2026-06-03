#include <stdio.h>
#include <stdlib.h>

#define MAX_STACK_SIZE 100
#define MAZE_SIZE 6

typedef struct {
  int r;
  int c;
} element;

int MAZE[MAZE_SIZE][MAZE_SIZE]={
  {1,1,1,1,1,1},
  {0,0,0,0,1,1},
  {1,1,0,1,1,1},
  {1,1,0,1,1,1},
  {1,0,0,0,0,3},
  {1,1,1,1,1,1}
};

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

void push_loc(StackType *s, int r, int c) {
  if(r<0 || c<0 || r>5 || c>5) return;
  if(MAZE[r][c]==2 || MAZE[r][c]==1) return;
  element e={r,c};
  push(s,e);
  return;
}

int main() {
  StackType s;
  init_stack(&s);
  element here={1,0};
  push(&s,here);
  int r,c;
  while(!is_empty(&s)&&MAZE[r][c]!=3) {
    here=pop(&s);
    r=here.r; c=here.c;
    MAZE[r][c]=2;
    push_loc(&s,r+1,c);
    push_loc(&s,r,c+1);
    push_loc(&s,r,c-1);
    push_loc(&s,r-1,c);
    printf("here:(%d,%d)\n",r,c);
  }
  return 0;
}