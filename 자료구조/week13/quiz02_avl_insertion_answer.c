#include <stdio.h>
#include <stdlib.h>

typedef struct AVLNode {
    int key;
    int height;
    struct AVLNode *left;
    struct AVLNode *right;
} AVLNode;

static int max_int(int a, int b)
{
    return a > b ? a : b;
}

static int height(AVLNode *node)
{
    return node == NULL ? 0 : node->height;
}

static AVLNode *new_node(int key)
{
    AVLNode *node = (AVLNode *)malloc(sizeof(AVLNode));
    if (node == NULL) {
        fprintf(stderr, "allocation failed\n");
        exit(1);
    }
    node->key = key;
    node->height = 1;
    node->left = NULL;
    node->right = NULL;
    return node;
}

static AVLNode *rotate_right(AVLNode *y)
{
    AVLNode *x = y->left;
    AVLNode *t2 = x->right;

    x->right = y;
    y->left = t2;

    y->height = max_int(height(y->left), height(y->right)) + 1;
    x->height = max_int(height(x->left), height(x->right)) + 1;
    return x;
}

static AVLNode *rotate_left(AVLNode *x)
{
    AVLNode *y = x->right;
    AVLNode *t2 = y->left;

    y->left = x;
    x->right = t2;

    x->height = max_int(height(x->left), height(x->right)) + 1;
    y->height = max_int(height(y->left), height(y->right)) + 1;
    return y;
}

static int get_balance(AVLNode *node)
{
    if (node == NULL) {
        return 0;
    }
    return height(node->left) - height(node->right);
}

static AVLNode *insert(AVLNode *node, int key)
{
    int balance;

    if (node == NULL) {
        return new_node(key);
    }

    if (key < node->key) {
        node->left = insert(node->left, key);
    } else if (key > node->key) {
        node->right = insert(node->right, key);
    } else {
        return node;
    }

    node->height = 1 + max_int(height(node->left), height(node->right));
    balance = get_balance(node);

    if (balance > 1 && key < node->left->key) {
        return rotate_right(node);
    }
    if (balance < -1 && key > node->right->key) {
        return rotate_left(node);
    }
    if (balance > 1 && key > node->left->key) {
        node->left = rotate_left(node->left);
        return rotate_right(node);
    }
    if (balance < -1 && key < node->right->key) {
        node->right = rotate_right(node->right);
        return rotate_left(node);
    }

    return node;
}

static void print_tree(AVLNode *root, int depth)
{
    if (root == NULL) {
        return;
    }
    print_tree(root->right, depth + 1);
    for (int i = 0; i < depth; i++) {
        printf("    ");
    }
    printf("%d(bf=%d)\n", root->key, get_balance(root));
    print_tree(root->left, depth + 1);
}

static void free_tree(AVLNode *root)
{
    if (root == NULL) {
        return;
    }
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}

int main(void)
{
    int data[] = { 1, 4, 2, 5, 6, 3 };
    int n = (int)(sizeof(data) / sizeof(data[0]));
    AVLNode *root = NULL;

    for (int i = 0; i < n; i++) {
        root = insert(root, data[i]);
        printf("after insert %d:\n", data[i]);
        print_tree(root, 0);
        printf("\n");
    }

    free_tree(root);
    return 0;
}
