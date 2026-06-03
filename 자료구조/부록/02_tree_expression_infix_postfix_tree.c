#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_STACK_SIZE 200

typedef struct TreeNode {
    char data;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

typedef struct {
    char data[MAX_STACK_SIZE];
    int top;
} CharStack;

typedef struct {
    TreeNode *data[MAX_STACK_SIZE];
    int top;
} NodeStack;

static void error(const char *message)
{
    fprintf(stderr, "%s\n", message);
    exit(1);
}

static int is_operator(char ch)
{
    return ch == '+' || ch == '-' || ch == '*' || ch == '/';
}

static int precedence(char op)
{
    switch (op) {
    case '(':
    case ')':
        return 0;
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
        return 2;
    default:
        return -1;
    }
}

static void init_char_stack(CharStack *s)
{
    s->top = -1;
}

static int is_empty_char(CharStack *s)
{
    return s->top == -1;
}

static void push_char(CharStack *s, char item)
{
    if (s->top >= MAX_STACK_SIZE - 1) {
        error("char stack is full");
    }
    s->data[++s->top] = item;
}

static char pop_char(CharStack *s)
{
    if (is_empty_char(s)) {
        error("char stack is empty");
    }
    return s->data[s->top--];
}

static char peek_char(CharStack *s)
{
    if (is_empty_char(s)) {
        error("char stack is empty");
    }
    return s->data[s->top];
}

static void infix_to_postfix(const char *input, char postfix[])
{
    CharStack s;
    int j = 0;

    init_char_stack(&s);

    for (int i = 0; input[i] != '\0'; i++) {
        char ch = input[i];

        if (isdigit((unsigned char)ch)) {
            postfix[j++] = ch;
        } else if (ch == '(') {
            push_char(&s, ch);
        } else if (ch == ')') {
            while (!is_empty_char(&s) && peek_char(&s) != '(') {
                postfix[j++] = pop_char(&s);
            }
            if (!is_empty_char(&s)) {
                pop_char(&s);
            }
        } else if (is_operator(ch)) {
            while (!is_empty_char(&s) && precedence(peek_char(&s)) >= precedence(ch)) {
                postfix[j++] = pop_char(&s);
            }
            push_char(&s, ch);
        }
    }

    while (!is_empty_char(&s)) {
        postfix[j++] = pop_char(&s);
    }
    postfix[j] = '\0';
}

static void init_node_stack(NodeStack *s)
{
    s->top = -1;
}

static int is_empty_node(NodeStack *s)
{
    return s->top == -1;
}

static void push_node(NodeStack *s, TreeNode *item)
{
    if (s->top >= MAX_STACK_SIZE - 1) {
        error("node stack is full");
    }
    s->data[++s->top] = item;
}

static TreeNode *pop_node(NodeStack *s)
{
    if (is_empty_node(s)) {
        error("node stack is empty");
    }
    return s->data[s->top--];
}

static TreeNode *make_node(char data, TreeNode *left, TreeNode *right)
{
    TreeNode *node = (TreeNode *)malloc(sizeof(TreeNode));

    if (node == NULL) {
        error("allocation failed");
    }
    node->data = data;
    node->left = left;
    node->right = right;
    return node;
}

static TreeNode *make_expression_tree(const char *postfix)
{
    NodeStack s;

    init_node_stack(&s);

    for (int i = 0; postfix[i] != '\0'; i++) {
        char ch = postfix[i];

        if (isdigit((unsigned char)ch)) {
            push_node(&s, make_node(ch, NULL, NULL));
        } else if (is_operator(ch)) {
            TreeNode *right = pop_node(&s);
            TreeNode *left = pop_node(&s);
            push_node(&s, make_node(ch, left, right));
        }
    }
    return pop_node(&s);
}

static void preorder(TreeNode *root)
{
    if (root == NULL) {
        return;
    }
    printf("%c ", root->data);
    preorder(root->left);
    preorder(root->right);
}

static void inorder_expression(TreeNode *root)
{
    int op;

    if (root == NULL) {
        return;
    }

    op = is_operator(root->data);
    if (op) {
        printf("(");
    }
    inorder_expression(root->left);
    printf("%c", root->data);
    inorder_expression(root->right);
    if (op) {
        printf(")");
    }
}

static void postorder(TreeNode *root)
{
    if (root == NULL) {
        return;
    }
    postorder(root->left);
    postorder(root->right);
    printf("%c ", root->data);
}

static int evaluate(TreeNode *root)
{
    int op1;
    int op2;

    if (root == NULL) {
        return 0;
    }
    if (root->left == NULL && root->right == NULL) {
        return root->data - '0';
    }

    op1 = evaluate(root->left);
    op2 = evaluate(root->right);

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

static int get_height(TreeNode *root)
{
    int left_height;
    int right_height;

    if (root == NULL) {
        return 0;
    }

    left_height = get_height(root->left);
    right_height = get_height(root->right);
    return (left_height > right_height ? left_height : right_height) + 1;
}

static int get_leaf_count(TreeNode *root)
{
    if (root == NULL) {
        return 0;
    }
    if (root->left == NULL && root->right == NULL) {
        return 1;
    }
    return get_leaf_count(root->left) + get_leaf_count(root->right);
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
    char input[] = "((8/2)+(3*4))-5";
    char postfix[MAX_STACK_SIZE];
    TreeNode *root;

    infix_to_postfix(input, postfix);
    root = make_expression_tree(postfix);

    printf("infix expression  : %s\n", input);
    printf("postfix expression: %s\n\n", postfix);

    printf("preorder : ");
    preorder(root);
    printf("\n");
    printf("inorder  : ");
    inorder_expression(root);
    printf("\n");
    printf("postorder: ");
    postorder(root);
    printf("\n\n");

    printf("height    : %d\n", get_height(root));
    printf("leaf count: %d\n", get_leaf_count(root));
    printf("value     : %d\n", evaluate(root));

    destroy_tree(root);
    return 0;
}
