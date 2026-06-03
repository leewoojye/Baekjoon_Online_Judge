#include <stdio.h>
#include <stdlib.h>

typedef int element;

typedef struct {
    element *data;
    int front;
    int rear;
    int size;
    int capacity;
} QueueType;

static void error(const char *message)
{
    fprintf(stderr, "%s\n", message);
    exit(1);
}

static void init_queue(QueueType *q, int capacity)
{
    if (capacity < 1) {
        capacity = 1;
    }

    q->data = (element *)malloc(sizeof(element) * capacity);
    if (q->data == NULL) {
        error("allocation failed");
    }

    q->front = 0;
    q->rear = -1;
    q->size = 0;
    q->capacity = capacity;
}

static void destroy_queue(QueueType *q)
{
    free(q->data);
    q->data = NULL;
    q->front = 0;
    q->rear = -1;
    q->size = 0;
    q->capacity = 0;
}

static int is_empty(QueueType *q)
{
    return q->size == 0;
}

static int is_full(QueueType *q)
{
    return q->size == q->capacity;
}

static void resize_queue(QueueType *q)
{
    int old_capacity = q->capacity;
    int new_capacity = old_capacity * 2;
    element *new_data = (element *)malloc(sizeof(element) * new_capacity);

    if (new_data == NULL) {
        error("allocation failed");
    }

    for (int i = 0; i < q->size; i++) {
        int idx = (q->front + 1 + i) % old_capacity;
        new_data[i] = q->data[idx];
    }

    free(q->data);
    q->data = new_data;
    q->capacity = new_capacity;
    q->front = new_capacity - 1;
    q->rear = q->size - 1;
}

static void enqueue(QueueType *q, element item)
{
    if (is_full(q)) {
        resize_queue(q);
    }

    q->rear = (q->rear + 1) % q->capacity;
    q->data[q->rear] = item;
    q->size++;
}

static element dequeue(QueueType *q)
{
    if (is_empty(q)) {
        error("queue is empty");
    }

    q->front = (q->front + 1) % q->capacity;
    q->size--;
    return q->data[q->front];
}

static void print_queue(QueueType *q)
{
    printf("[ ");
    for (int i = 0; i < q->size; i++) {
        int idx = (q->front + 1 + i) % q->capacity;
        printf("%d ", q->data[idx]);
    }
    printf("]");
}

static void print_operations(int operations[], int n)
{
    printf("operations: ");
    for (int i = 0; i < n; i++) {
        printf("%d", operations[i]);
        if (i + 1 < n) {
            printf(", ");
        }
    }
    printf("\n");
}

int main(void)
{
    int operations[] = { 1, 2, 3, -1, 4, 5, 6, 7, 8, -1 };
    int n = (int)(sizeof(operations) / sizeof(operations[0]));
    QueueType q;

    init_queue(&q, 1);
    print_operations(operations, n);

    for (int i = 0; i < n; i++) {
        if (operations[i] > 0) {
            enqueue(&q, operations[i]);
            printf("enqueue %d: ", operations[i]);
            print_queue(&q);
            printf(" capacity=%d\n", q.capacity);
        } else if (operations[i] == -1) {
            printf("dequeue %d: ", dequeue(&q));
            print_queue(&q);
            printf(" capacity=%d\n", q.capacity);
        }
    }

    destroy_queue(&q);
    return 0;
}
