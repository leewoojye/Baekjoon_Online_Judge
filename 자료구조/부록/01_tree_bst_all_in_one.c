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

static void error(const char *message)
{
    fprintf(stderr, "%s\n", message);
    exit(1);
}

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

static TreeNode *min_value_node(TreeNode *root)
{
    TreeNode *current = root;

    while (current != NULL && current->left != NULL) {
        current = current->left;
    }
    return current;
}

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

static void preorder(TreeNode *root)
{
    if (root == NULL) {
        return;
    }
    printf("%d ", root->key);
    preorder(root->left);
    preorder(root->right);
}

static void inorder(TreeNode *root)
{
    if (root == NULL) {
        return;
    }
    inorder(root->left);
    printf("%d ", root->key);
    inorder(root->right);
}

static void postorder(TreeNode *root)
{
    if (root == NULL) {
        return;
    }
    postorder(root->left);
    postorder(root->right);
    printf("%d ", root->key);
}

static int get_node_count(TreeNode *root)
{
    if (root == NULL) {
        return 0;
    }
    return get_node_count(root->left) + get_node_count(root->right) + 1;
}

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

static int abs_int(int value)
{
    return value < 0 ? -value : value;
}

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

static void enqueue(QueueType *q, q_element item)
{
    if (is_full(q)) {
        error("queue is full");
    }
    q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
    q->data[q->rear] = item;
}

static q_element dequeue(QueueType *q)
{
    if (is_empty(q)) {
        error("queue is empty");
    }
    q->front = (q->front + 1) % MAX_QUEUE_SIZE;
    return q->data[q->front];
}

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

static void destroy_tree(TreeNode *root)
{
    if (root == NULL) {
        return;
    }
    destroy_tree(root->left);
    destroy_tree(root->right);
    free(root);
}

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
