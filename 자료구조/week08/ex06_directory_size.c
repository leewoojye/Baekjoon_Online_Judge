#include <stdio.h>

typedef struct TreeNode {
    int data;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

static int calc_dir_size(TreeNode *root)
{
    if (root == NULL) {
        return 0;
    }
    return root->data + calc_dir_size(root->left) + calc_dir_size(root->right);
}

int main(void)
{
    TreeNode n4 = { 500, NULL, NULL };
    TreeNode n5 = { 200, NULL, NULL };
    TreeNode n3 = { 100, &n4, &n5 };
    TreeNode n2 = { 50, NULL, NULL };
    TreeNode n1 = { 0, &n2, &n3 };

    printf("directory size=%d\n", calc_dir_size(&n1));
    return 0;
}
