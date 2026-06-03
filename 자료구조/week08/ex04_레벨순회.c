#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 100

// 8장 원형큐 levelorder
typedef struct TreeNode {
    int data;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

typedef TreeNode *element;

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

static void init_queue(QueueType *q)
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

static void level_order(TreeNode *ptr)
{
    QueueType q;

    init_queue(&q);
    if (ptr == NULL) {
        return;
    }
    enqueue(&q, ptr);
    while (!is_empty(&q)) {
        ptr = dequeue(&q);
        printf("[%d] ", ptr->data);
        if (ptr->left != NULL) {
            enqueue(&q, ptr->left);
        }
        if (ptr->right != NULL) {
            enqueue(&q, ptr->right);
        }
    }
}

int main(void)
{
    TreeNode n1 = { 1, NULL, NULL };
    TreeNode n2 = { 4, &n1, NULL };
    TreeNode n3 = { 16, NULL, NULL };
    TreeNode n4 = { 25, NULL, NULL };
    TreeNode n5 = { 20, &n3, &n4 };
    TreeNode n6 = { 15, &n2, &n5 };

    printf("level order=");
    level_order(&n6);
    printf("\n");
    return 0;
}
