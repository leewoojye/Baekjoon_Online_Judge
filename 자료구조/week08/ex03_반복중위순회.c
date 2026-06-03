#include <stdio.h>

#define STACK_SIZE 100

typedef struct TreeNode {
    int data;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

static int top = -1;
static TreeNode *stack[STACK_SIZE];

static void push(TreeNode *p)
{
    if (top < STACK_SIZE - 1) {
        stack[++top] = p;
    }
}

static TreeNode *pop(void)
{
    if (top >= 0) {
        return stack[top--];
    }
    return NULL;
}

static void inorder_iter(TreeNode *root)
{
    while (1) {
        for (; root != NULL; root = root->left) {
            push(root);
        }
        root = pop();
        if (root == NULL) {
            break;
        }
        printf("[%d] ", root->data);
        root = root->right; // 더 이상 좌 자식이 없는 노드의 우측서브트리를 순회
    }
}

int main(void)
{
    TreeNode n1 = { 1, NULL, NULL };
    TreeNode n2 = { 4, &n1, NULL };
    TreeNode n3 = { 16, NULL, NULL };
    TreeNode n4 = { 25, NULL, NULL };
    TreeNode n5 = { 20, &n3, &n4 };
    TreeNode n6 = { 15, &n2, &n5 };

    printf("inorder=");
    inorder_iter(&n6);
    printf("\n");
    return 0;
}
