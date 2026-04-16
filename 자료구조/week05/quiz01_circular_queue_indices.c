/*
Quiz
1. 원형 큐에서 front와 rear가 가리키는 것은 무엇인가?
2. 크기가 10인 원형큐에서 front와 rear가 모두 0으로 초기화되었을 때
   enqueue(a), enqueue(b), enqueue(c), dequeue(), enqueue(d)
   연산 후 front와 rear 값을 말하라.

예시 답안
1. 이 구현에서 front는 첫 번째 원소 "바로 앞"의 위치를 가리키고,
   rear는 마지막 원소의 위치를 가리킨다.
2. 연산 결과
   - enqueue(a)  -> front=0, rear=1
   - enqueue(b)  -> front=0, rear=2
   - enqueue(c)  -> front=0, rear=3
   - dequeue()   -> front=1, rear=3
   - enqueue(d)  -> front=1, rear=4
   최종 값은 front=1, rear=4
*/

#include <stdio.h>

#define MAX_QUEUE_SIZE 10

typedef struct {
    char data[MAX_QUEUE_SIZE];
    int front;
    int rear;
} QueueType;

void init_queue(QueueType *q)
{
    q->front = q->rear = 0;
}

void enqueue(QueueType *q, char item)
{
    q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
    q->data[q->rear] = item;
}

char dequeue(QueueType *q)
{
    q->front = (q->front + 1) % MAX_QUEUE_SIZE;
    return q->data[q->front];
}

int main(void)
{
    QueueType q;

    init_queue(&q);
    printf("initial      -> front=%d rear=%d\n", q.front, q.rear);
    enqueue(&q, 'a');
    printf("enqueue(a)   -> front=%d rear=%d\n", q.front, q.rear);
    enqueue(&q, 'b');
    printf("enqueue(b)   -> front=%d rear=%d\n", q.front, q.rear);
    enqueue(&q, 'c');
    printf("enqueue(c)   -> front=%d rear=%d\n", q.front, q.rear);
    printf("dequeue()=%c -> ", dequeue(&q));
    printf("front=%d rear=%d\n", q.front, q.rear);
    enqueue(&q, 'd');
    printf("enqueue(d)   -> front=%d rear=%d\n", q.front, q.rear);
    return 0;
}
