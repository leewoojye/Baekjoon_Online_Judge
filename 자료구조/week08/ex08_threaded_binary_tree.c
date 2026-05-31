#include <stdio.h>

#define TRUE 1
#define FALSE 0

typedef struct TreeNode {
    char data;
    struct TreeNode *left;
    struct TreeNode *right;
    int is_thread;
} TreeNode;

static TreeNode *find_successor(TreeNode *p)
{
    TreeNode *q = p->right;

    if (q == NULL || p->is_thread == TRUE) {
        return q;
    }

    while (q->left != NULL) {
        q = q->left;
    }
    return q;
}

static void thread_inorder(TreeNode *t)
{
    TreeNode *q = t;

    while (q != NULL && q->left != NULL) {
        q = q->left;
    }

    while (q != NULL) {
        printf("%c ", q->data);
        q = find_successor(q);
    }
}

int main(void)
{
    TreeNode n_d = { 'D', NULL, NULL, TRUE };
    TreeNode n_e = { 'E', NULL, NULL, TRUE };
    TreeNode n_f = { 'F', NULL, NULL, TRUE };
    TreeNode n_b = { 'B', &n_d, &n_e, FALSE };
    TreeNode n_c = { 'C', &n_f, NULL, TRUE };
    TreeNode n_a = { 'A', &n_b, &n_c, FALSE };

    n_d.right = &n_b;
    n_e.right = &n_a;
    n_f.right = &n_c;

    printf("threaded inorder=");
    thread_inorder(&n_a);
    printf("\n");
    return 0;
}
