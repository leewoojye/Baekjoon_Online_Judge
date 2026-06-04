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

static void preorder_iter(TreeNode *root)
{
    // 이전 순회에서 남은 값이 없도록 전역 스택을 비운 상태로 시작한다.
    top = -1;
    if (root != NULL) {
        push(root); // 루트부터 방문해야 하므로 루트를 먼저 넣는다.
    }

    while (top >= 0) {
        // 전위 순회는 root -> left -> right 순서이므로 꺼내자마자 출력한다.
        root = pop();
        printf("[%d] ", root->data);

        // 스택은 나중에 넣은 값이 먼저 나오므로 right를 먼저 넣는다.
        if (root->right != NULL) {
            push(root->right);
        }
        // left를 나중에 넣으면 다음 pop에서 left가 먼저 방문된다.
        if (root->left != NULL) {
            push(root->left);
        }
    }
}

static void postorder_iter(TreeNode *root)
{
    // out_stack은 root -> right -> left 순서를 뒤집어 출력하기 위한 보조 스택이다.
    TreeNode *out_stack[STACK_SIZE];
    int out_top = -1;

    // 첫 번째 스택은 아직 방문할 노드를 저장한다.
    top = -1;
    if (root != NULL) {
        push(root);
    }

    while (top >= 0) {
        // 먼저 root -> right -> left 순서로 노드를 꺼내 out_stack에 저장한다.
        root = pop();
        if (out_top < STACK_SIZE - 1) {
            out_stack[++out_top] = root;
        }

        // left를 먼저 넣고 right를 나중에 넣으면 pop할 때 right가 먼저 나온다.
        if (root->left != NULL) {
            push(root->left);
        }
        if (root->right != NULL) {
            push(root->right);
        }
    }

    // out_stack에서 거꾸로 꺼내면 left -> right -> root, 즉 후위 순회가 된다.
    while (out_top >= 0) {
        root = out_stack[out_top--];
        printf("[%d] ", root->data);
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
