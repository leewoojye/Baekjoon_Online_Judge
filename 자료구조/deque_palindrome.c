#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_DEQUE_SIZE 101 // 최대 100문자 수용가능, 나머지 한 칸은 널문자

typedef char element;

typedef struct deque {
  int front,rear;
  element data[MAX_DEQUE_SIZE];
} deque;

void init_deque(deque *d) {
  d->front=d->rear=0;
}

int is_empty(deque *d) {
  return d->front==d->rear;
}

int is_full(deque *d) {
  return d->front==0 && d->rear==MAX_DEQUE_SIZE-1;
  // or 원소개수에 대한 필드 추가해서 판별
}

void print_deque(deque *d) {
  printf("DEQUE(front=%d rear=%d) = ",d->front,d->rear);
  for(int i=d->front;i!=d->rear;i++) {
    printf("%c | ",d->data[i]);
  }
  printf("\n");
}

void push_rear(deque *d, element e) {
  if(d->rear==MAX_DEQUE_SIZE-1) {
    printf("push error");
    return;
  }
  d->data[(d->rear)++]=e;
  return;
}

element pop_front(deque *d) {
  if(is_empty(&d)) {
    printf("pop error");
    return 0;
  }
  return d->data[(d->front)++];
}

element pop_rear(deque *d) {
  if(is_empty(&d)) {
    printf("pop error");
    return 0;
  }
  return d->data[--(d->rear)];
}

int main() {
  deque d;
  init_deque(&d);

  char in[MAX_DEQUE_SIZE];
  scanf("%s",in);

  int len=strlen(in);
  char ch1,ch2;

  for(int i=0;i<len;i++) {
    push_rear(&d,in[i]);
    print_deque(&d);
  }
  for(int i=0;i<len/2;i++) {
    ch1=pop_front(&d);
    print_deque(&d);
    ch2=pop_rear(&d);
    print_deque(&d);
    if(ch1!=ch2) {
      printf("회문이 아님");
      return 0;
    }
  }
  printf("회문임");
  return 0;
}