#include <stdio.h>

typedef struct TreeNode {
    int data;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

static int max_int(int a, int b)
{
    return a > b ? a : b;
}

static int get_node_count(TreeNode *node)
{
    if (node == NULL) {
        return 0;
    }
    return 1 + get_node_count(node->left) + get_node_count(node->right);
}

static int get_height(TreeNode *node)
{
    if (node == NULL) {
        return 0;
    }
    return 1 + max_int(get_height(node->left), get_height(node->right));
}

static int get_leaf_count(TreeNode *node)
{
    if (node == NULL) {
        return 0;
    }
    if (node->left == NULL && node->right == NULL) {
        return 1;
    }
    return get_leaf_count(node->left) + get_leaf_count(node->right);
}

int main(void)
{
    TreeNode n1 = { 1, NULL, NULL };
    TreeNode n2 = { 4, &n1, NULL };
    TreeNode n3 = { 16, NULL, NULL };
    TreeNode n4 = { 25, NULL, NULL };
    TreeNode n5 = { 20, &n3, &n4 };
    TreeNode n6 = { 15, &n2, &n5 };

    printf("node count=%d\n", get_node_count(&n6));
    printf("height=%d\n", get_height(&n6));
    printf("leaf count=%d\n", get_leaf_count(&n6));
    return 0;
}
