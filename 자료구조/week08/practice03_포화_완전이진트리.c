#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 100

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

static int max_int(int a, int b)
{
    return a > b ? a : b;
}

static int height(TreeNode *root)
{
    if (root == NULL) {
        return 0;
    }
    return max_int(height(root->left), height(root->right)) + 1;
}

// 포화이진트리 검사
static int is_perfect_binary_tree(TreeNode *root)
{
    if (root == NULL) {
        return 1;
    }
    if (root->left == NULL && root->right == NULL) {
        return 1;
    }
    if (root->left == NULL || root->right == NULL) {
        return 0;
    }
    return height(root->left) == height(root->right) &&
           is_perfect_binary_tree(root->left) &&
           is_perfect_binary_tree(root->right);
}

// 완전이진트리 검사
static int is_complete_binary_tree(TreeNode *root)
{
    QueueType q;
    TreeNode *node;
    int empty_child_seen = 0;

    if (root == NULL) {
        return 1;
    }

    init_queue(&q);
    enqueue(&q, root);
    while (!is_empty(&q)) {
        node = dequeue(&q);

        if (node->left != NULL) {
            if (empty_child_seen) {
                return 0;
            }
            enqueue(&q, node->left);
        } else {
            empty_child_seen = 1;
        }

        if (node->right != NULL) {
            if (empty_child_seen) {
                return 0;
            }
            enqueue(&q, node->right);
        } else {
            empty_child_seen = 1;
        }
    }
    return 1;
}

static void print_result(const char *name, TreeNode *root)
{
    printf("[%s]\n", name);
    printf("perfect binary tree: %s\n",
           is_perfect_binary_tree(root) ? "yes" : "no");
    printf("complete binary tree: %s\n",
           is_complete_binary_tree(root) ? "yes" : "no");
}

int main(void)
{
    TreeNode p1 = { 4, NULL, NULL };
    TreeNode p2 = { 5, NULL, NULL };
    TreeNode p3 = { 6, NULL, NULL };
    TreeNode p4 = { 7, NULL, NULL };
    TreeNode p5 = { 2, &p1, &p2 };
    TreeNode p6 = { 3, &p3, &p4 };
    TreeNode perfect = { 1, &p5, &p6 };

    TreeNode c1 = { 4, NULL, NULL };
    TreeNode c2 = { 5, NULL, NULL };
    TreeNode c3 = { 6, NULL, NULL };
    TreeNode c4 = { 2, &c1, &c2 };
    TreeNode c5 = { 3, &c3, NULL };
    TreeNode complete = { 1, &c4, &c5 };

    TreeNode n1 = { 4, NULL, NULL };
    TreeNode n2 = { 2, NULL, &n1 };
    TreeNode n3 = { 3, NULL, NULL };
    TreeNode not_complete = { 1, &n2, &n3 };

    print_result("perfect sample", &perfect);
    printf("\n");
    print_result("complete sample", &complete);
    printf("\n");
    print_result("not complete sample", &not_complete);
    return 0;
}
