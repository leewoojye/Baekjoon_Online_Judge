/*
Quiz
1. 연결된 큐에서 다음과 같은 연산 후의 상태를 그림으로 그려라
   Enqueue(a), enqueue(b), enqueue(c), dequeue(), enqueue(d)
2. 연결된 큐가 공백 상태일 때 front 와 rear의 값은?

예시 답안
1. 연산 추적
   enqueue(a) -> a
   enqueue(b) -> a -> b
   enqueue(c) -> a -> b -> c
   dequeue()  -> a 제거, b -> c
   enqueue(d) -> b -> c -> d
2. 공백 상태에서는 front == NULL, rear == NULL 이다.
*/

#include <stdio.h>
#include <stdlib.h>

typedef char element;

typedef struct QueueNode {
    element data;
    struct QueueNode *link;
} QueueNode;

typedef struct {
    QueueNode *front;
    QueueNode *rear;
} LinkedQueueType;

void init(LinkedQueueType *q)
{
    q->front = NULL;
    q->rear = NULL;
}

int is_empty(LinkedQueueType *q)
{
    return q->front == NULL;
}

void enqueue(LinkedQueueType *q, element data)
{
    QueueNode *temp = (QueueNode *)malloc(sizeof(QueueNode));

    if (temp == NULL) {
        fprintf(stderr, "Memory allocation error\n");
        exit(1);
    }
    temp->data = data;
    temp->link = NULL;

    if (is_empty(q)) {
        q->front = temp;
        q->rear = temp;
    } else {
        q->rear->link = temp;
        q->rear = temp;
    }
}

element dequeue(LinkedQueueType *q)
{
    QueueNode *temp;
    element data;

    if (is_empty(q)) {
        fprintf(stderr, "queue underflow\n");
        exit(1);
    }
    temp = q->front;
    data = temp->data;
    q->front = temp->link;
    if (q->front == NULL) {
        q->rear = NULL;
    }
    free(temp);
    return data;
}

void print_queue(LinkedQueueType *q, const char *label)
{
    QueueNode *p;

    printf("%-12s front=%p rear=%p | ", label, (void *)q->front, (void *)q->rear);
    for (p = q->front; p != NULL; p = p->link) {
        printf("%c -> ", p->data);
    }
    printf("NULL\n");
}

void destroy_queue(LinkedQueueType *q)
{
    while (!is_empty(q)) {
        dequeue(q);
    }
}

int main(void)
{
    LinkedQueueType q;

    init(&q);
    printf("공백 큐 상태: front=%p rear=%p\n\n", (void *)q.front, (void *)q.rear);

    enqueue(&q, 'a');
    print_queue(&q, "enqueue(a)");
    enqueue(&q, 'b');
    print_queue(&q, "enqueue(b)");
    enqueue(&q, 'c');
    print_queue(&q, "enqueue(c)");
    printf("dequeue() -> %c\n", dequeue(&q));
    print_queue(&q, "after deq");
    enqueue(&q, 'd');
    print_queue(&q, "enqueue(d)");

    destroy_queue(&q);
    return 0;
}
