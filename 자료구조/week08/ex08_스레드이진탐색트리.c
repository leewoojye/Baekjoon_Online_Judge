#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

typedef struct TreeNode {
    int data;
    struct TreeNode *left;
    struct TreeNode *right;
    int is_thread;
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
    node->is_thread = FALSE;
    return node;
}

static TreeNode *insert_node(TreeNode *root, int data)
{
    if (root == NULL) {
        return make_node(data);
    }

    if (data < root->data) {
        root->left = insert_node(root->left, data);
    } else if (data > root->data) {
        root->right = insert_node(root->right, data);
    }
    return root;
}

// 이진탐색트리를 스레드 트리로 만듦, root를 루트로 하는 서브트리에서 마지막으로 방문한 노드를 반환함(호출부에서 이 노드가 후속노드를 가리키게 해야함)
static TreeNode *make_inorder_threads(TreeNode *root, TreeNode *prev) // prev는 직전에 중위순회로 방문한 노드
{
    if (root == NULL) {
        return prev;
    }

    // 중위순회: 좌 서브트리부터 처리
    prev = make_inorder_threads(root->left, prev); // 좌 서브트리에서 마지막으로 방문한 노드(prev는 루트를 가리켜야함)

    // 중위순회: 다음에 루트 처리
    if (prev != NULL && prev->right == NULL) { // 스레드 포인터는 우측링크에 저장
        prev->right = root;
        prev->is_thread = TRUE;
    }
    root->is_thread = FALSE;
    prev = root;

    return make_inorder_threads(root->right, prev); // root 서브트리에서 마지막으로 방문한 노드를 반환
}

static TreeNode *find_successor(TreeNode *p)
{
    TreeNode *q = p->right;

    if (q == NULL || p->is_thread == 1) {
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
        printf("%d ", q->data);
        q = find_successor(q);
    }
}

static void destroy_threaded_tree(TreeNode *root)
{
    if (root == NULL) {
        return;
    }

    destroy_threaded_tree(root->left);
    if (!root->is_thread) {
        destroy_threaded_tree(root->right);
    }
    free(root);
}

int main(void)
{
    int values[] = { 40, 20, 60, 10, 30, 50, 70 };
    int count = sizeof(values) / sizeof(values[0]);
    TreeNode *root = NULL;

    for (int i = 0; i < count; i++) {
        root = insert_node(root, values[i]);
    }
    make_inorder_threads(root, NULL);

    printf("threaded inorder=");
    thread_inorder(root);
    printf("\n");

    destroy_threaded_tree(root);
    return 0;
}
