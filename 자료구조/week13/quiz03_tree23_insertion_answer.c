#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int n;
    int keys[2];
    struct Node *child[3];
} Node;

typedef struct {
    int has_split;
    int key;
    Node *right;
} Split;

static Node *make_node(void)
{
    Node *node = (Node *)calloc(1, sizeof(Node));
    if (node == NULL) {
        fprintf(stderr, "allocation failed\n");
        exit(1);
    }
    return node;
}

static int is_leaf(Node *node)
{
    return node->child[0] == NULL;
}

static int child_index(Node *node, int key)
{
    if (key < node->keys[0]) {
        return 0;
    }
    if (node->n == 1 || key < node->keys[1]) {
        return 1;
    }
    return 2;
}

static void insert_into_nonfull(Node *node, int pos, int key, Node *right)
{
    for (int i = node->n; i > pos; i--) {
        node->keys[i] = node->keys[i - 1];
    }
    node->keys[pos] = key;

    if (!is_leaf(node)) {
        for (int i = node->n + 1; i > pos + 1; i--) {
            node->child[i] = node->child[i - 1];
        }
        node->child[pos + 1] = right;
    }
    node->n++;
}

static void split_full_node(Node *node, int pos, int key, Node *right, Split *out)
{
    int temp_keys[3];
    Node *temp_child[4] = { NULL, NULL, NULL, NULL };
    Node *right_node = make_node();

    for (int i = 0, j = 0; i < 3; i++) {
        if (i == pos) {
            temp_keys[i] = key;
        } else {
            temp_keys[i] = node->keys[j++];
        }
    }

    for (int i = 0, j = 0; i < 4; i++) {
        if (i == pos + 1) {
            temp_child[i] = right;
        } else {
            temp_child[i] = node->child[j++];
        }
    }

    node->n = 1;
    node->keys[0] = temp_keys[0];
    node->keys[1] = 0;
    node->child[0] = temp_child[0];
    node->child[1] = temp_child[1];
    node->child[2] = NULL;

    right_node->n = 1;
    right_node->keys[0] = temp_keys[2];
    right_node->child[0] = temp_child[2];
    right_node->child[1] = temp_child[3];

    out->has_split = 1;
    out->key = temp_keys[1];
    out->right = right_node;
}

static Split insert_recursive(Node *node, int key)
{
    Split result = { 0, 0, NULL };

    for (int i = 0; i < node->n; i++) {
        if (key == node->keys[i]) {
            return result;
        }
    }

    if (is_leaf(node)) {
        int pos = 0;
        while (pos < node->n && key > node->keys[pos]) {
            pos++;
        }
        if (node->n < 2) {
            insert_into_nonfull(node, pos, key, NULL);
        } else {
            split_full_node(node, pos, key, NULL, &result);
        }
        return result;
    }

    int pos = child_index(node, key);
    Split child_split = insert_recursive(node->child[pos], key);
    if (!child_split.has_split) {
        return result;
    }

    if (node->n < 2) {
        insert_into_nonfull(node, pos, child_split.key, child_split.right);
    } else {
        split_full_node(node, pos, child_split.key, child_split.right, &result);
    }
    return result;
}

static Node *insert(Node *root, int key)
{
    if (root == NULL) {
        root = make_node();
        root->n = 1;
        root->keys[0] = key;
        return root;
    }

    Split split = insert_recursive(root, key);
    if (split.has_split) {
        Node *new_root = make_node();
        new_root->n = 1;
        new_root->keys[0] = split.key;
        new_root->child[0] = root;
        new_root->child[1] = split.right;
        return new_root;
    }
    return root;
}

static void print_compact(Node *node)
{
    if (node == NULL) {
        return;
    }

    if (node->n == 1) {
        printf("[%d]", node->keys[0]);
    } else {
        printf("[%d %d]", node->keys[0], node->keys[1]);
    }

    if (!is_leaf(node)) {
        printf("(");
        for (int i = 0; i <= node->n; i++) {
            if (i > 0) {
                printf(" ");
            }
            print_compact(node->child[i]);
        }
        printf(")");
    }
}

static void free_tree(Node *node)
{
    if (node == NULL) {
        return;
    }
    for (int i = 0; i <= node->n; i++) {
        free_tree(node->child[i]);
    }
    free(node);
}

int main(void)
{
    int data[] = { 5, 6, 7, 4, 3, 2, 1, 8, 9 };
    int n = (int)(sizeof(data) / sizeof(data[0]));
    Node *root = NULL;

    for (int i = 0; i < n; i++) {
        root = insert(root, data[i]);
        printf("after insert %d: ", data[i]);
        print_compact(root);
        printf("\n");
    }

    free_tree(root);
    return 0;
}
