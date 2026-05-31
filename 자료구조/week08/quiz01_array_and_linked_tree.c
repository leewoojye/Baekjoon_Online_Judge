#include <stdio.h>
#include <stdlib.h>

#define MAX_TREE_SIZE 32

typedef struct TreeNode {
    int data;
    struct TreeNode *left;
    struct TreeNode *right;
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
    return node;
}

static void print_array_tree(const int tree[], int size)
{
    for (int i = 1; i < size; i++) {
        if (tree[i] != 0) {
            printf("index %2d: %d\n", i, tree[i]);
        }
    }
}

static void preorder(TreeNode *root)
{
    if (root == NULL) {
        return;
    }
    printf("%d ", root->data);
    preorder(root->left);
    preorder(root->right);
}

static void free_tree(TreeNode *root)
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
    int tree[MAX_TREE_SIZE] = { 0 };

    tree[1] = 10;
    tree[3] = 20;
    tree[7] = 30;
    tree[14] = 25;

    printf("Array representation answer:\n");
    print_array_tree(tree, MAX_TREE_SIZE);

    TreeNode *root = make_node(10);
    root->right = make_node(20);
    root->right->right = make_node(30);
    root->right->right->left = make_node(25);

    printf("\nLinked representation preorder: ");
    preorder(root);
    printf("\n");

    free_tree(root);
    return 0;
}
