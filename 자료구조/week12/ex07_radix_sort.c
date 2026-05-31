#include <stdio.h>

#define BUCKETS 10
#define DIGITS 4
#define MAX_QUEUE_SIZE 100
#define SIZE 10

typedef int element;

typedef struct {
    element data[MAX_QUEUE_SIZE];
    int front;
    int rear;
} QueueType;

static void init(QueueType *q)
{
    q->front = 0;
    q->rear = 0;
}

static int is_empty(QueueType *q)
{
    return q->front == q->rear;
}

static void enqueue(QueueType *q, element item)
{
    q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
    q->data[q->rear] = item;
}

static element dequeue(QueueType *q)
{
    q->front = (q->front + 1) % MAX_QUEUE_SIZE;
    return q->data[q->front];
}

static void radix_sort(int list[], int n)
{
    QueueType queues[BUCKETS];
    int factor = 1;

    for (int b = 0; b < BUCKETS; b++) {
        init(&queues[b]);
    }

    for (int d = 0; d < DIGITS; d++) {
        for (int i = 0; i < n; i++) {
            enqueue(&queues[(list[i] / factor) % 10], list[i]);
        }
        int i = 0;
        for (int b = 0; b < BUCKETS; b++) {
            while (!is_empty(&queues[b])) {
                list[i++] = dequeue(&queues[b]);
            }
        }
        factor *= 10;
    }
}

int main(void)
{
    int list[SIZE] = { 52, 87, 42, 77, 53, 47, 85, 72, 100, 3 };

    radix_sort(list, SIZE);
    for (int i = 0; i < SIZE; i++) {
        printf("%d ", list[i]);
    }
    printf("\n");
    return 0;
}
