#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

typedef struct TreeNode {
    int data;
    struct TreeNode *left;
    struct TreeNode *right;
    int is_thread;
} TreeNode;

static TreeNode *make_node(int data)
{
    TreeNode *node = (TreeNode *)malloc(sizeof(TreeNode));

    if (node == NULL) {
        fprintf(stderr, "allocation failed\n");
        exit(1);
    }
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    node->is_thread = FALSE;
    return node;
}

static TreeNode *insert_node(TreeNode *root, int data)
{
    if (root == NULL) {
        return make_node(data);
    }

    if (data < root->data) {
        root->left = insert_node(root->left, data);
    } else if (data > root->data) {
        root->right = insert_node(root->right, data);
    }
    return root;
}

static void clear_threads(TreeNode *root)
{
    if (root == NULL) {
        return;
    }
    clear_threads(root->left);
    if (root->is_thread) {
        root->right = NULL;
        root->is_thread = FALSE;
    } else {
        clear_threads(root->right);
    }
}

static TreeNode *make_preorder_threads(TreeNode *root, TreeNode *prev)
{
    TreeNode *left;
    TreeNode *right;

    if (root == NULL) {
        return prev;
    }

    left = root->left;
    right = root->right;

    if (prev != NULL && prev->right == NULL) {
        prev->right = root;
        prev->is_thread = TRUE;
    }
    root->is_thread = FALSE;
    prev = root;

    prev = make_preorder_threads(left, prev);
    prev = make_preorder_threads(right, prev);
    return prev;
}

static void thread_preorder(TreeNode *root)
{
    TreeNode *node = root;

    while (node != NULL) {
        printf("%d ", node->data);
        if (node->left != NULL) {
            node = node->left;
        } else {
            node = node->right;
        }
    }
}

static TreeNode *find_first_postorder(TreeNode *root)
{
    while (root != NULL &&
           (root->left != NULL || (root->right != NULL && !root->is_thread))) {
        if (root->left != NULL) {
            root = root->left;
        } else {
            root = root->right;
        }
    }
    return root;
}

static TreeNode *make_postorder_threads(TreeNode *root, TreeNode *prev)
{
    if (root == NULL) {
        return prev;
    }

    prev = make_postorder_threads(root->left, prev);
    prev = make_postorder_threads(root->right, prev);

    if (prev != NULL && prev->right == NULL) {
        prev->right = root;
        prev->is_thread = TRUE;
    }
    root->is_thread = FALSE;
    return root;
}

static TreeNode *find_parent(TreeNode *root, TreeNode *node)
{
    TreeNode *parent = NULL;

    while (root != NULL && root != node) {
        parent = root;
        if (node->data < root->data) {
            root = root->left;
        } else if (!root->is_thread) {
            root = root->right;
        } else {
            root = NULL;
        }
    }

    if (root == node) {
        return parent;
    }
    return NULL;
}

static TreeNode *find_postorder_successor(TreeNode *root, TreeNode *node)
{
    TreeNode *parent;

    if (node == root) {
        return NULL;
    }
    if (node->is_thread) {
        return node->right;
    }

    parent = find_parent(root, node);
    if (parent == NULL) {
        return NULL;
    }

    if (parent->right == node || parent->right == NULL || parent->is_thread) {
        return parent;
    }
    return find_first_postorder(parent->right);
}

static void thread_postorder(TreeNode *root)
{
    TreeNode *node = find_first_postorder(root);

    while (node != NULL) {
        printf("%d ", node->data);
        node = find_postorder_successor(root, node);
    }
}

static void destroy_threaded_tree(TreeNode *root)
{
    if (root == NULL) {
        return;
    }
    destroy_threaded_tree(root->left);
    if (!root->is_thread) {
        destroy_threaded_tree(root->right);
    }
    free(root);
}

int main(void)
{
    int values[] = { 40, 20, 60, 10, 30, 50, 70 };
    int count = sizeof(values) / sizeof(values[0]);
    TreeNode *root = NULL;
    TreeNode *prev = NULL;

    for (int i = 0; i < count; i++) {
        root = insert_node(root, values[i]);
    }

    prev = make_preorder_threads(root, prev);
    printf("threaded preorder=");
    thread_preorder(root);
    printf("\n");

    clear_threads(root);
    prev = NULL;

    prev = make_postorder_threads(root, prev);
    printf("threaded postorder=");
    thread_postorder(root);
    printf("\n");

    destroy_threaded_tree(root);
    return 0;
}
