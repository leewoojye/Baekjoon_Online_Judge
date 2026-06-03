#include <stdio.h>
#include <stdlib.h>

#define BUCKETS 26
#define WORD_LEN 3
#define MAX_QUEUE_SIZE 100

typedef const char *element;

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

static int bucket_index(const char *word, int pos)
{
    if (word[pos] < 'A' || word[pos] > 'Z') {
        error("only uppercase alphabet keys are supported");
    }
    return word[pos] - 'A';
}

static void print_words(const char *list[], int n)
{
    for (int i = 0; i < n; i++) {
        printf("%s ", list[i]);
    }
    printf("\n");
}

static void radix_sort_alphabet(const char *list[], int n)
{
    QueueType queues[BUCKETS];
    int pass = 1;

    for (int pos = WORD_LEN - 1; pos >= 0; pos--) {
        for (int b = 0; b < BUCKETS; b++) {
            init(&queues[b]);
        }

        for (int i = 0; i < n; i++) {
            enqueue(&queues[bucket_index(list[i], pos)], list[i]);
        }

        int i = 0;
        for (int b = 0; b < BUCKETS; b++) {
            while (!is_empty(&queues[b])) {
                list[i++] = dequeue(&queues[b]);
            }
        }

        printf("pass %d: ", pass++);
        print_words(list, n);
    }
}

int main(void)
{
    const char *list[] = { "SUN", "CAT", "DOG", "ANT", "BAT", "COW", "PIG", "APE", "BEE", "ZOO" };
    int n = (int)(sizeof(list) / sizeof(list[0]));

    printf("start : ");
    print_words(list, n);
    radix_sort_alphabet(list, n);

    printf("result: ");
    print_words(list, n);
    return 0;
}
