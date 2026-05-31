#include <stdio.h>

typedef struct TreeNode {
    int data;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

static TreeNode n22 = { 22, NULL, NULL };
static TreeNode n05 = { 5, NULL, NULL };
static TreeNode n35 = { 35, &n22, NULL };
static TreeNode n95 = { 95, NULL, NULL };
static TreeNode n15 = { 15, &n05, NULL };
static TreeNode n93 = { 93, &n35, &n95 };
static TreeNode n17 = { 17, &n15, &n93 };

static void preorder(TreeNode *root)
{
    if (root != NULL) {
        printf("%d ", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}

static void inorder(TreeNode *root)
{
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

static void postorder(TreeNode *root)
{
    if (root != NULL) {
        postorder(root->left);
        postorder(root->right);
        printf("%d ", root->data);
    }
}

int main(void)
{
    printf("preorder : ");
    preorder(&n17);
    printf("\n");

    printf("inorder  : ");
    inorder(&n17);
    printf("\n");

    printf("postorder: ");
    postorder(&n17);
    printf("\n");
    return 0;
}
