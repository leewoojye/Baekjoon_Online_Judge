#include <stdio.h>
#include <stdlib.h>

typedef int element;

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

void print_queue(LinkedQueueType *q)
{
    QueueNode *p;

    for (p = q->front; p != NULL; p = p->link) {
        printf("%d->", p->data);
    }
    printf("NULL\n");
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
    QueueNode *temp = q->front;
    element data;

    if (is_empty(q)) {
        fprintf(stderr, "큐가 비어있음\n");
        exit(1);
    }
    data = temp->data;
    q->front = q->front->link;
    if (q->front == NULL) {
        q->rear = NULL;
    }
    free(temp);
    return data;
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
    enqueue(&q, 1);
    print_queue(&q);
    enqueue(&q, 2);
    print_queue(&q);
    enqueue(&q, 3);
    print_queue(&q);
    dequeue(&q);
    print_queue(&q);
    dequeue(&q);
    print_queue(&q);
    dequeue(&q);
    print_queue(&q);

    destroy_queue(&q);
    return 0;
}
