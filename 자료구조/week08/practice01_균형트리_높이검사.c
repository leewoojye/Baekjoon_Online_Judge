#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    int data;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

static TreeNode *make_node(int data)
{
    TreeNode *node = (TreeNode *)malloc(sizeof(TreeNode));

    if (node == NULL) {
        fprintf(stderr, "allocation failed\n");
        exit(1);
    }
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

static int max_int(int a, int b)
{
    return a > b ? a : b;
}

static int abs_int(int x)
{
    return x < 0 ? -x : x;
}

static int height(TreeNode *root)
{
    if (root == NULL) {
        return 0;
    }
    return max_int(height(root->left), height(root->right)) + 1;
}

int s_balanced(TreeNode *root)
{
    int left_height;
    int right_height;

    if (root == NULL) {
        return 1;
    }

    left_height = height(root->left);
    right_height = height(root->right);

    return abs_int(left_height - right_height) <= 1 &&
           s_balanced(root->left) &&
           s_balanced(root->right);
}

// 트리 높이 구하면서 균형 여부 검사
static int check_height(TreeNode *root)
{
    int left_height;
    int right_height;

    if (root == NULL) {
        return 0;
    }

    left_height = check_height(root->left);
    if (left_height == -1) {
        return -1;
    }

    right_height = check_height(root->right);
    if (right_height == -1) {
        return -1;
    }

    if (abs_int(left_height - right_height) > 1) { // 균형 여부 검사
        return -1;
    }
    return max_int(left_height, right_height) + 1;
}

int s_balanced_fast(TreeNode *root)
{
    return check_height(root) != -1;
}

static void inorder(TreeNode *root)
{
    if (root == NULL) {
        return;
    }
    inorder(root->left);
    printf("%d ", root->data);
    inorder(root->right);
}

static void print_balance_result(TreeNode *root)
{
    printf("[balance check] ");
    if (s_balanced_fast(root)) {
        printf("tree is balanced.\n");
    } else {
        printf("tree is not balanced.\n");
    }
}

static void free_tree(TreeNode *root)
{
    if (root == NULL) {
        return;
    }
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}

static TreeNode *make_balanced_sample(void)
{
    TreeNode *root = make_node(35);

    root->left = make_node(18);
    root->right = make_node(68);
    root->left->left = make_node(7);
    root->left->right = make_node(26);
    root->right->right = make_node(99);
    root->left->left->left = make_node(3);
    root->left->left->right = make_node(12);
    root->left->right->left = make_node(22);
    root->left->right->right = make_node(30);

    return root;
}

static TreeNode *make_unbalanced_sample(void)
{
    TreeNode *root = make_node(35);

    root->left = make_node(18);
    root->right = make_node(99);
    root->left->left = make_node(7);
    root->left->right = make_node(26);
    root->left->left->left = make_node(3);
    root->left->left->right = make_node(12);
    root->left->right->left = make_node(22);
    root->left->right->right = make_node(30);

    return root;
}

int main(void)
{
    TreeNode *balanced = make_balanced_sample();
    TreeNode *unbalanced = make_unbalanced_sample();

    printf("balanced sample inorder: ");
    inorder(balanced);
    printf("\n");
    print_balance_result(balanced);

    printf("\nunbalanced sample inorder: ");
    inorder(unbalanced);
    printf("\n");
    print_balance_result(unbalanced);

    free_tree(balanced);
    free_tree(unbalanced);
    return 0;
}
