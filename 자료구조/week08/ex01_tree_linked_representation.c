#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    int data;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

int main(void)
{
    TreeNode *n1 = (TreeNode *)malloc(sizeof(TreeNode));
    TreeNode *n2 = (TreeNode *)malloc(sizeof(TreeNode));
    TreeNode *n3 = (TreeNode *)malloc(sizeof(TreeNode));

    if (n1 == NULL || n2 == NULL || n3 == NULL) {
        fprintf(stderr, "allocation failed\n");
        free(n1);
        free(n2);
        free(n3);
        return 1;
    }

    n1->data = 10;
    n1->left = n2;
    n1->right = n3;

    n2->data = 20;
    n2->left = NULL;
    n2->right = NULL;

    n3->data = 30;
    n3->left = NULL;
    n3->right = NULL;

    printf("root=%d, left=%d, right=%d\n", n1->data, n1->left->data, n1->right->data);

    free(n1);
    free(n2);
    free(n3);
    return 0;
}
