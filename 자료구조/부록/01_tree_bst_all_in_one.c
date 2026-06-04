#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define MAX_QUEUE_SIZE 200

typedef struct TreeNode {
    int key;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

typedef TreeNode *q_element;

typedef struct {
    q_element data[MAX_QUEUE_SIZE];
    int front;
    int rear;
} QueueType;

// 오류 메시지를 출력하고 프로그램을 종료한다.
static void error(const char *message)
{
    fprintf(stderr, "%s\n", message);
    exit(1);
}

// 주어진 key를 저장하는 새 트리 노드를 생성한다.
static TreeNode *make_node(int key)
{
    TreeNode *node = (TreeNode *)malloc(sizeof(TreeNode));

    if (node == NULL) {
        error("allocation failed");
    }
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// 이진 탐색 트리에 key를 삽입하고 루트를 반환한다.
static TreeNode *insert_node(TreeNode *root, int key)
{
    if (root == NULL) {
        return make_node(key);
    }

    if (key < root->key) {
        root->left = insert_node(root->left, key);
    } else if (key > root->key) {
        root->right = insert_node(root->right, key);
    }
    return root;
}

// 이진 탐색 트리에서 key를 가진 노드를 찾는다.
static TreeNode *search_node(TreeNode *root, int key)
{
    while (root != NULL) {
        if (key == root->key) {
            return root;
        }
        if (key < root->key) {
            root = root->left;
        } else {
            root = root->right;
        }
    }
    return NULL;
}

// 서브트리에서 가장 작은 key를 가진 노드를 찾는다.
static TreeNode *min_value_node(TreeNode *root)
{
    TreeNode *current = root;

    while (current != NULL && current->left != NULL) {
        current = current->left;
    }
    return current;
}

// 이진 탐색 트리에서 key를 삭제하고 루트를 반환한다.
static TreeNode *delete_node(TreeNode *root, int key)
{
    if (root == NULL) {
        return NULL;
    }

    if (key < root->key) {
        root->left = delete_node(root->left, key);
    } else if (key > root->key) {
        root->right = delete_node(root->right, key);
    } else {
        if (root->left == NULL) {
            TreeNode *temp = root->right;
            free(root);
            return temp;
        }
        if (root->right == NULL) {
            TreeNode *temp = root->left;
            free(root);
            return temp;
        }

        TreeNode *temp = min_value_node(root->right);
        root->key = temp->key;
        root->right = delete_node(root->right, temp->key);
    }
    return root;
}

// 트리를 전위 순회하며 key를 출력한다.
static void preorder(TreeNode *root)
{
    if (root == NULL) {
        return;
    }
    printf("%d ", root->key);
    preorder(root->left);
    preorder(root->right);
}

// 트리를 중위 순회하며 key를 출력한다.
static void inorder(TreeNode *root)
{
    if (root == NULL) {
        return;
    }
    inorder(root->left);
    printf("%d ", root->key);
    inorder(root->right);
}

// 트리를 후위 순회하며 key를 출력한다.
static void postorder(TreeNode *root)
{
    if (root == NULL) {
        return;
    }
    postorder(root->left);
    postorder(root->right);
    printf("%d ", root->key);
}

// 트리에 포함된 전체 노드 수를 계산한다.
static int get_node_count(TreeNode *root)
{
    if (root == NULL) {
        return 0;
    }
    return get_node_count(root->left) + get_node_count(root->right) + 1;
}

// 트리의 높이를 계산한다.
static int get_height(TreeNode *root)
{
    int left_height;
    int right_height;

    if (root == NULL) {
        return 0;
    }

    left_height = get_height(root->left);
    right_height = get_height(root->right);
    return (left_height > right_height ? left_height : right_height) + 1;
}

// 트리에 포함된 리프 노드 수를 계산한다.
static int get_leaf_count(TreeNode *root)
{
    if (root == NULL) {
        return 0;
    }
    if (root->left == NULL && root->right == NULL) {
        return 1;
    }
    return get_leaf_count(root->left) + get_leaf_count(root->right);
}

// 정수의 절댓값을 반환한다.
static int abs_int(int value)
{
    return value < 0 ? -value : value;
}

// 모든 노드의 좌우 서브트리 높이 차이가 1 이하인지 확인한다.
static int is_balanced(TreeNode *root)
{
    int left_height;
    int right_height;

    if (root == NULL) {
        return TRUE;
    }

    left_height = get_height(root->left);
    right_height = get_height(root->right);
    if (abs_int(left_height - right_height) > 1) {
        return FALSE;
    }
    return is_balanced(root->left) && is_balanced(root->right);
}

// 레벨 순회에 사용할 원형 큐를 초기화한다.
static void init_queue(QueueType *q)
{
    q->front = 0;
    q->rear = 0;
}

// 원형 큐가 비어 있는지 확인한다.
static int is_empty(QueueType *q)
{
    return q->front == q->rear;
}

// 원형 큐가 가득 찼는지 확인한다.
static int is_full(QueueType *q)
{
    return (q->rear + 1) % MAX_QUEUE_SIZE == q->front;
}

// 원형 큐에 트리 노드를 삽입한다.
static void enqueue(QueueType *q, q_element item)
{
    if (is_full(q)) {
        error("queue is full");
    }
    q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
    q->data[q->rear] = item;
}

// 원형 큐에서 트리 노드를 삭제해 반환한다.
static q_element dequeue(QueueType *q)
{
    if (is_empty(q)) {
        error("queue is empty");
    }
    q->front = (q->front + 1) % MAX_QUEUE_SIZE;
    return q->data[q->front];
}

// 트리를 레벨 순서로 순회하며 key를 출력한다.
static void level_order(TreeNode *root)
{
    QueueType q;

    if (root == NULL) {
        return;
    }

    init_queue(&q);
    enqueue(&q, root);

    while (!is_empty(&q)) {
        TreeNode *node = dequeue(&q);
        printf("%d ", node->key);
        if (node->left != NULL) {
            enqueue(&q, node->left);
        }
        if (node->right != NULL) {
            enqueue(&q, node->right);
        }
    }
}

// 트리의 순회 결과와 기본 통계 정보를 출력한다.
static void print_tree_info(const char *title, TreeNode *root)
{
    printf("%s\n", title);
    printf("inorder   : ");
    inorder(root);
    printf("\n");
    printf("preorder  : ");
    preorder(root);
    printf("\n");
    printf("postorder : ");
    postorder(root);
    printf("\n");
    printf("levelorder: ");
    level_order(root);
    printf("\n");
    printf("node count: %d\n", get_node_count(root));
    printf("height    : %d\n", get_height(root));
    printf("leaf count: %d\n", get_leaf_count(root));
    printf("balanced  : %s\n\n", is_balanced(root) ? "YES" : "NO");
}

// 트리의 모든 노드를 후위 순회로 해제한다.
static void destroy_tree(TreeNode *root)
{
    if (root == NULL) {
        return;
    }
    destroy_tree(root->left);
    destroy_tree(root->right);
    free(root);
}

// 이진 탐색 트리의 삽입, 삭제, 검색, 순회 기능을 시연한다.
int main(void)
{
    int insert_keys[] = { 35, 18, 68, 7, 26, 99, 3, 12, 22, 30 };
    int delete_keys[] = { 68, 18, 35 };
    int search_keys[] = { 22, 68, 35 };
    int insert_size = (int)(sizeof(insert_keys) / sizeof(insert_keys[0]));
    int delete_size = (int)(sizeof(delete_keys) / sizeof(delete_keys[0]));
    int search_size = (int)(sizeof(search_keys) / sizeof(search_keys[0]));
    TreeNode *root = NULL;

    for (int i = 0; i < insert_size; i++) {
        root = insert_node(root, insert_keys[i]);
    }

    print_tree_info("initial tree", root);

    for (int i = 0; i < delete_size; i++) {
        char title[80];
        root = delete_node(root, delete_keys[i]);
        sprintf(title, "after delete %d", delete_keys[i]);
        print_tree_info(title, root);
    }

    printf("search result\n");
    for (int i = 0; i < search_size; i++) {
        printf("%d: %s\n", search_keys[i], search_node(root, search_keys[i]) != NULL ? "FOUND" : "NOT FOUND");
    }

    destroy_tree(root);
    return 0;
}
