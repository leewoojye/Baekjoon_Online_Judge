#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_STACK_SIZE 100

// 수식트리 생성
// 전위,중위,후위 순회 출력
// 트리 재귀 평가
typedef struct TreeNode {
    int data;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

typedef TreeNode *element;

typedef struct {
    element data[MAX_STACK_SIZE];
    int top;
} StackType;

static void error(const char *message)
{
    fprintf(stderr, "%s\n", message);
    exit(1);
}

static void init_stack(StackType *s)
{
    s->top = -1;
}

static int is_empty(StackType *s)
{
    return s->top == -1;
}

static int is_full(StackType *s)
{
    return s->top == MAX_STACK_SIZE - 1;
}

static void push(StackType *s, element item)
{
    if (is_full(s)) {
        error("Stack overflow");
    }
    s->data[++(s->top)] = item;
}

static element pop(StackType *s)
{
    if (is_empty(s)) {
        error("Stack underflow");
    }
    return s->data[(s->top)--];
}

static TreeNode *make_node(int data)
{
    TreeNode *node = (TreeNode *)malloc(sizeof(TreeNode));

    if (node == NULL) {
        error("allocation failed");
    }
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

static int is_leaf(TreeNode *node)
{
    return node->left == NULL && node->right == NULL;
}

static int is_operator(int ch)
{
    return ch == '+' || ch == '-' || ch == '*' || ch == '/';
}

static TreeNode *make_expression_tree(const char *postfix)
{
    StackType s;
    const char *p = postfix;

    init_stack(&s);

    while (*p != '\0') {
        while (isspace((unsigned char)*p)) {
            p++;
        }
        if (*p == '\0') {
            break;
        }

        if (is_operator(*p) && (p[1] == '\0' || isspace((unsigned char)p[1]))) {
            TreeNode *right = pop(&s);
            TreeNode *left = pop(&s);
            TreeNode *node = make_node(*p);

            node->left = left;
            node->right = right;
            push(&s, node);
            p++;
        } else {
            char *endptr;
            long value = strtol(p, &endptr, 10);

            if (p == endptr) {
                error("invalid postfix token");
            }
            push(&s, make_node((int)value));
            p = endptr;
        }
    }

    if (is_empty(&s)) {
        error("empty postfix expression");
    }

    TreeNode *root = pop(&s);
    if (!is_empty(&s)) {
        error("invalid postfix expression");
    }
    return root;
}

static int evaluate(TreeNode *root)
{
    if (root == NULL) {
        return 0;
    }
    if (is_leaf(root)) {
        return root->data;
    }

    int op1 = evaluate(root->left);
    int op2 = evaluate(root->right);

    switch (root->data) {
    case '+':
        return op1 + op2;
    case '-':
        return op1 - op2;
    case '*':
        return op1 * op2;
    case '/':
        if (op2 == 0) {
            error("division by zero");
        }
        return op1 / op2;
    default:
        error("unknown operator");
    }
    return 0;
}

static void print_node(TreeNode *root)
{
    if (is_leaf(root)) {
        printf("%d ", root->data);
    } else {
        printf("%c ", root->data);
    }
}

static void print_prefix(TreeNode *root)
{
    if (root == NULL) {
        return;
    }
    print_node(root);
    print_prefix(root->left);
    print_prefix(root->right);
}

static void print_infix(TreeNode *root)
{
    if (root == NULL) {
        return;
    }

    if (!is_leaf(root)) {
        printf("( ");
    }
    print_infix(root->left);
    print_node(root);
    print_infix(root->right);
    if (!is_leaf(root)) {
        printf(") ");
    }
}

static void print_postfix(TreeNode *root)
{
    if (root == NULL) {
        return;
    }
    print_postfix(root->left);
    print_postfix(root->right);
    print_node(root);
}

static void destroy_tree(TreeNode *root)
{
    if (root == NULL) {
        return;
    }
    destroy_tree(root->left);
    destroy_tree(root->right);
    free(root);
}

int main(void)
{
    const char postfix[] = "1 4 * 16 25 + +";
    TreeNode *root = make_expression_tree(postfix);

    printf("postfix input: %s\n", postfix);

    printf("prefix : ");
    print_prefix(root);
    printf("\n");

    printf("infix  : ");
    print_infix(root);
    printf("\n");

    printf("postfix: ");
    print_postfix(root);
    printf("\n");

    printf("value=%d\n", evaluate(root));

    destroy_tree(root);
    return 0;
}
