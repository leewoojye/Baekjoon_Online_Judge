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

// 오류 메시지를 출력하고 프로그램을 종료한다.
static void error(const char *message)
{
    fprintf(stderr, "%s\n", message);
    exit(1);
}

// 큐를 지정한 초기 용량으로 초기화한다.
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

// 큐가 사용 중인 동적 메모리를 해제한다.
static void destroy_queue(QueueType *q)
{
    free(q->data);
    q->data = NULL;
    q->front = 0;
    q->rear = -1;
    q->size = 0;
    q->capacity = 0;
}

// 큐가 비어 있는지 확인한다.
static int is_empty(QueueType *q)
{
    return q->size == 0;
}

// 큐가 가득 찼는지 확인한다.
static int is_full(QueueType *q)
{
    return q->size == q->capacity;
}

// 큐 용량을 두 배로 늘리고 기존 원형 순서를 보존한다.
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

// 큐의 rear에 새 원소를 삽입한다.
static void enqueue(QueueType *q, element item)
{
    if (is_full(q)) {
        resize_queue(q);
    }

    q->rear = (q->rear + 1) % q->capacity;
    q->data[q->rear] = item;
    q->size++;
}

// 큐의 front에서 원소를 삭제해 반환한다.
static element dequeue(QueueType *q)
{
    if (is_empty(q)) {
        error("queue is empty");
    }

    q->front = (q->front + 1) % q->capacity;
    q->size--;
    return q->data[q->front];
}

// 현재 큐에 들어 있는 원소들을 순서대로 출력한다.
static void print_queue(QueueType *q)
{
    printf("[ ");
    for (int i = 0; i < q->size; i++) {
        int idx = (q->front + 1 + i) % q->capacity;
        printf("%d ", q->data[idx]);
    }
    printf("]");
}

// 큐 연산 입력 배열을 출력한다.
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

// 동적 원형 큐의 삽입, 삭제, 자동 확장을 시연한다.
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
