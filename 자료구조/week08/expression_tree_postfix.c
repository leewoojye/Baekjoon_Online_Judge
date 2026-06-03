#include <stdio.h>
#define MAX_STACK_SIZE 100

typedef int element;

typedef struct {
    element data[MAX_STACK_SIZE];
    int top;
} StackType;

void init_stack(StackType *s)
{
    s->top = -1;
}

int is_empty(StackType *s)
{
    return s->top == -1;
}

int is_full(StackType *s)
{
    return s->top == MAX_STACK_SIZE - 1;
}

void push(StackType *s, element item)
{
    if (is_full(s)) {
        fprintf(stderr, "Stack overflow\n");
        return;
    }
    s->data[++(s->top)] = item;
}

element pop(StackType *s)
{
    if (is_empty(s)) {
        fprintf(stderr, "Stack underflow\n");
        exit(1);
    }
    return s->data[(s->top)--];
}

typedef struct TreeNode {
    int data;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

int is_leaf(TreeNode* node) {
    return node->left==NULL && node->right==NULL;
}

static int evaluate(TreeNode *root)
{
    if (root == NULL) {
        return 0;
    }
    if (root->left == NULL && root->right == NULL) {
        return root->data;
    }

    int op1 = evaluate(root->left);
    int op2 = evaluate(root->right);

    printf("%d %c %d\n", op1, root->data, op2);

    switch (root->data) {
    case '+':
        return op1 + op2;
    case '-':
        return op1 - op2;
    case '*':
        return op1 * op2;
    case '/':
        return op1 / op2;
    default:
        return 0;
    }
}

// 후위순회
int evaluate_with_stack(TreeNode *root, StackType *s) {
    if(root==NULL) return 0;
    if(is_leaf(root)) return root->data;
    if(root->data=='+'||root->data=='-'||root->data=='*'||root->data=='/') {
        int op1=evaluate_with_stack(root->left, s);
    }
}

void print_prefix(TreeNode *root) {
    printf("%c ",root->data);
    if(root->left!=NULL) print_prefix(root->left);
    if(root->right!=NULL) print_prefix(root->right);
}

void print_infix(TreeNode *root) {
    if(root->left!=NULL) print_prefix(root->left);
    printf("%c ",root->data);
    if(root->right!=NULL) print_prefix(root->right);
}

void print_postfix(TreeNode *root) {
    if(root->left!=NULL) print_prefix(root->left);
    if(root->right!=NULL) print_prefix(root->right);
    printf("%c ",root->data);
}

int main(void)
{
    StackType s;
    init_stack(&s);
    TreeNode n1 = { 1, NULL, NULL };
    TreeNode n2 = { 4, NULL, NULL };
    TreeNode n3 = { '*', &n1, &n2 };
    TreeNode n4 = { 16, NULL, NULL };
    TreeNode n5 = { 25, NULL, NULL };
    TreeNode n6 = { '+', &n4, &n5 };
    TreeNode n7 = { '+', &n3, &n6 };
    // TreeNode n1 = { '1', NULL, NULL };
    // TreeNode n2 = { '4', NULL, NULL };
    // TreeNode n3 = { '*', &n1, &n2 };
    // TreeNode n4 = { '16', NULL, NULL };
    // TreeNode n5 = { '25', NULL, NULL };
    // TreeNode n6 = { '+', &n4, &n5 };
    // TreeNode n7 = { '+', &n3, &n6 };

    // printf("value=%d\n", evaluate(&n7));
    print_prefix(&n7);
    return 0;
}
