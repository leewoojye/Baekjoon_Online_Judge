#include <stdio.h>

#define TRUE 1
#define FALSE 0

typedef enum {
    TWO_NODE,
    THREE_NODE
} NodeType;

typedef struct Tree23Node {
    NodeType type;
    int key1;
    int key2;
    struct Tree23Node *left;
    struct Tree23Node *middle;
    struct Tree23Node *right;
} Tree23Node;

static int tree23_search(Tree23Node *root, int key)
{
    if (root == NULL) {
        return FALSE;
    }
    if (key == root->key1) {
        return TRUE;
    }

    if (root->type == TWO_NODE) {
        if (key < root->key1) {
            return tree23_search(root->left, key);
        }
        return tree23_search(root->right, key);
    }

    if (key == root->key2) {
        return TRUE;
    }
    if (key < root->key1) {
        return tree23_search(root->left, key);
    }
    if (key > root->key2) {
        return tree23_search(root->right, key);
    }
    return tree23_search(root->middle, key);
}

int main(void)
{
    Tree23Node n1 = { TWO_NODE, 1, 0, NULL, NULL, NULL };
    Tree23Node n3 = { TWO_NODE, 3, 0, NULL, NULL, NULL };
    Tree23Node n5 = { TWO_NODE, 5, 0, NULL, NULL, NULL };
    Tree23Node n7 = { TWO_NODE, 7, 0, NULL, NULL, NULL };
    Tree23Node root = { THREE_NODE, 2, 6, &n1, &n3, &n7 };

    n7.left = &n5;

    printf("search 3: %s\n", tree23_search(&root, 3) ? "found" : "not found");
    printf("search 4: %s\n", tree23_search(&root, 4) ? "found" : "not found");
    return 0;
}
