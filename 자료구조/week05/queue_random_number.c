#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MAX_QUEUE_SIZE 101 // 최대 100문자 수용가능, 나머지 한 칸은 널문자

typedef int element;
typedef struct circular_queue {
  element data[MAX_QUEUE_SIZE];
  int front;
  int rear;
} circular_queue;

void init_circular_queue(circular_queue *q) {
  q->front=q->rear=0;
}

int is_empty(circular_queue *q) {
  return q->front==q->rear;
}

int is_full(circular_queue *q) {
  return q->front==(q->rear+1)%MAX_QUEUE_SIZE;
}

void push(circular_queue *q, element e) {
  if(is_full(q)) return;
  q->rear=(q->rear+1)%MAX_QUEUE_SIZE;
  q->data[q->rear]=e;
  return;
}

element pop(circular_queue *q) {
  if(is_empty(q)) return 0;
  element data;
  q->front=(q->front+1)%MAX_QUEUE_SIZE;
  return q->data[q->front];
}

void print_queue(circular_queue *q) {
  printf("QUEUE(front=%d rear=%d) = ",q->front,q->rear);
  if(is_empty(q)) {
    printf("empty\n");
    return;
  }
  for(int i=q->front+1;i<=q->rear;i++) {
    printf("%d | ",q->data[i]);
  }
  printf("\n");
  return;
}

int main() {
  circular_queue q;
  init_circular_queue(&q);
  srand(time(NULL));
  for(int i=0;i<100;i++) {
    if(rand()%5==0) {
      push(&q,rand()%100);
      print_queue(&q);
    }
    if(rand()%10==0) {
      element data = pop(&q);
      print_queue(&q);
    }
  }
  return 0;
}