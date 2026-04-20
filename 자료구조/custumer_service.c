#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef int element;

// 고객 구조체
typedef struct customer {
  int id;
  int arrival_time;
  int service_time;
} customer;

typedef struct QueueType { // 선형 동적큐
  int front,rear;
  int capacity;
  customer *data;
} QueueType;

void init_queue(QueueType *q) {
  q->front=q->rear=-1;
  q->capacity=1;
  q->data=(customer*)malloc(q->capacity*sizeof(customer));
  return;
}

int is_empty(QueueType *q) {
  return q->front==q->rear;
}

int is_full(QueueType *q) {
  return q->rear==q->capacity-1;
}

void push(QueueType *q, customer data) {
  if(is_full(q)) {
    q->capacity*=2;
    q->data=(customer*)realloc(q->data,q->capacity*sizeof(customer)); // 중요
  }
  q->data[++(q->rear)]=data;
  return;
}

int pop(QueueType *q) { // pop시 q->data에서도 제거? 제거안해도 상관없음 우리는 front만 알면 됨 물론 메모리 효율을 위해 제거하면 좋은데 복잡함..
  if(is_empty(q)) {
    printf("pop error");
    return 0;
  }
  return q->data[++(q->front)].id;
}

void print_queue(QueueType *q) {
  if(is_empty(q)) {
    printf("print error");
    return;
  }
  printf("(front=%d,rear=%d) ",q->front,q->rear);
  for(element p=q->front+1;p<=q->rear;p++) {
    printf("%d->",q->data[p].id);
  }
  printf(" (capacity=%d)\n",q->capacity);
  return;
}

customer peek_front(QueueType *q) {
  if(is_empty(q)) {
    printf("peek error");
    exit(1);
  }
  return q->data[q->front+1];
}

customer peek_rear(QueueType *q) {
  if(is_empty(q)) {
    printf("peek error");
    exit(1);
  }
  return q->data[q->rear];
}

// 교안 풀이는 내 풀이와 달리 큐를 대기 중인 고객들만 넣어 둠
int main(void)
{
    int minutes = 60;
    int total_wait = 0;
    int total_customers = 0;
    int service_time = 0;
    int service_customer = -1;
    srand(time(NULL));
    QueueType queue;
    init_queue(&queue);
    int clock=0;
    for(int i=0;i<minutes;i++) {
      if(!is_empty(&queue)) service_customer=peek_front(&queue).id;
      if(rand()%10<3) {
        if(is_empty(&queue)) {
          customer c; c.id=(total_customers++); c.arrival_time=clock; c.service_time=(rand()%3+1);
          service_customer=c.id;
          service_time=c.service_time;
          push(&queue,c);
        } else {
          customer c; c.id=(total_customers++); c.arrival_time=clock; c.service_time=(rand()%3+1);
          push(&queue,c);
        }
      }
      service_time--;
      clock++;
      if(service_time==0) {
        int out=pop(&queue);
        if(!is_empty(&queue)) {
          service_customer=peek_rear(&queue).id;
          service_time=peek_rear(&queue).service_time;
          total_wait+=(clock-peek_rear(&queue).arrival_time);
        }
      }
      if(!is_empty(&queue)) print_queue(&queue);
    }
    // print_queue(&queue);
    return 0;
}