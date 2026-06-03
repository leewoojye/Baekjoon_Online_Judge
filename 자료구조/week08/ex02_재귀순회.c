#include <stdio.h>

typedef struct TreeNode {
    int data;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

static TreeNode n1 = { 1, NULL, NULL };
static TreeNode n2 = { 4, &n1, NULL };
static TreeNode n3 = { 16, NULL, NULL };
static TreeNode n4 = { 25, NULL, NULL };
static TreeNode n5 = { 20, &n3, &n4 };
static TreeNode n6 = { 15, &n2, &n5 };
static TreeNode *root = &n6;

static void inorder(TreeNode *root)
{
    if (root != NULL) {
        inorder(root->left);
        printf("[%d] ", root->data);
        inorder(root->right);
    }
}

static void preorder(TreeNode *root)
{
    if (root != NULL) {
        printf("[%d] ", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}

static void postorder(TreeNode *root)
{
    if (root != NULL) {
        postorder(root->left);
        postorder(root->right);
        printf("[%d] ", root->data);
    }
}

int main(void)
{
    printf("inorder=");
    inorder(root);
    printf("\n");

    printf("preorder=");
    preorder(root);
    printf("\n");

    printf("postorder=");
    postorder(root);
    printf("\n");
    return 0;
}
