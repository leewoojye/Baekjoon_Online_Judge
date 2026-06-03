#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define BUCKETS 256
#define BYTE_BITS 8
#define PASSES 4
#define MAX_QUEUE_SIZE 100

typedef uint32_t element;

typedef struct {
    element data[MAX_QUEUE_SIZE];
    int front;
    int rear;
} QueueType;

static void error(const char *message)
{
    fprintf(stderr, "%s\n", message);
    exit(1);
}

static void init(QueueType *q)
{
    q->front = 0;
    q->rear = 0;
}

static int is_empty(QueueType *q)
{
    return q->front == q->rear;
}

static int is_full(QueueType *q)
{
    return (q->rear + 1) % MAX_QUEUE_SIZE == q->front;
}

static void enqueue(QueueType *q, element item)
{
    if (is_full(q)) {
        error("queue is full");
    }
    q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
    q->data[q->rear] = item;
}

static element dequeue(QueueType *q)
{
    if (is_empty(q)) {
        error("queue is empty");
    }
    q->front = (q->front + 1) % MAX_QUEUE_SIZE;
    return q->data[q->front];
}

static void print_array(const uint32_t list[], int n)
{
    for (int i = 0; i < n; i++) {
        printf("0x%08" PRIX32 " ", list[i]);
    }
    printf("\n");
}

static void radix_sort_32bit(uint32_t list[], int n)
{
    QueueType queues[BUCKETS];

    for (int pass = 0; pass < PASSES; pass++) {
        int shift = pass * BYTE_BITS;

        for (int b = 0; b < BUCKETS; b++) {
            init(&queues[b]);
        }

        for (int i = 0; i < n; i++) {
            int bucket = (int)((list[i] >> shift) & 0xFFu);

            enqueue(&queues[bucket], list[i]);
        }

        int i = 0;
        for (int b = 0; b < BUCKETS; b++) {
            while (!is_empty(&queues[b])) {
                list[i++] = dequeue(&queues[b]);
            }
        }

        printf("pass %d: ", pass + 1);
        print_array(list, n);
    }
}

int main(void)
{
    uint32_t list[] = {
        0x12345678u,
        0x00000005u,
        0x00FF0010u,
        0x7FFFFFFFu,
        0x01020304u,
        0xFFFFFFFFu,
        0x00010000u,
        0x80000000u
    };
    int n = (int)(sizeof(list) / sizeof(list[0]));

    printf("start : ");
    print_array(list, n);
    radix_sort_32bit(list, n);

    printf("result: ");
    print_array(list, n);
    return 0;
}
