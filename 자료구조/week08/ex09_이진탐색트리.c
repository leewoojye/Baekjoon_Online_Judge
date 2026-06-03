#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    int key;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

static TreeNode *search_recursive(TreeNode *node, int key)
{
    if (node == NULL) {
        return NULL;
    }
    if (key == node->key) {
        return node;
    }
    if (key < node->key) {
        return search_recursive(node->left, key);
    }
    return search_recursive(node->right, key);
}

static TreeNode *search_iterative(TreeNode *node, int key)
{
    while (node != NULL) {
        if (key == node->key) {
            return node;
        }
        if (key < node->key) {
            node = node->left;
        } else {
            node = node->right;
        }
    }
    return NULL;
}

static TreeNode *new_node(int item)
{
    TreeNode *temp = (TreeNode *)malloc(sizeof(TreeNode));
    if (temp == NULL) {
        fprintf(stderr, "allocation failed\n");
        exit(1);
    }
    temp->key = item;
    temp->left = NULL;
    temp->right = NULL;
    return temp;
}

static TreeNode *insert_node(TreeNode *node, int key)
{
    if (node == NULL) {
        return new_node(key);
    }

    if (key < node->key) {
        node->left = insert_node(node->left, key);
    } else if (key > node->key) {
        node->right = insert_node(node->right, key);
    }
    return node;
}

static TreeNode *min_value_node(TreeNode *node)
{
    TreeNode *current = node;

    while (current->left != NULL) {
        current = current->left;
    }
    return current;
}

static TreeNode *delete_node(TreeNode *root, int key)
{
    if (root == NULL) {
        return root;
    }

    if (key < root->key) {
        root->left = delete_node(root->left, key);
    } else if (key > root->key) {
        root->right = delete_node(root->right, key);
    } else {
        if (root->left == NULL) {
            TreeNode *temp = root->right;
            free(root);
            return temp;
        }
        if (root->right == NULL) {
            TreeNode *temp = root->left;
            free(root);
            return temp;
        }

        TreeNode *temp = min_value_node(root->right);
        root->key = temp->key;
        root->right = delete_node(root->right, temp->key);
    }
    return root;
}

static void inorder(TreeNode *root)
{
    if (root != NULL) {
        inorder(root->left);
        printf("[%d] ", root->key);
        inorder(root->right);
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

int main(void)
{
    TreeNode *root = NULL;
    int keys[] = { 30, 20, 10, 40, 50, 60 };
    int n = (int)(sizeof(keys) / sizeof(keys[0]));

    for (int i = 0; i < n; i++) {
        root = insert_node(root, keys[i]);
    }

    printf("inorder: ");
    inorder(root);
    printf("\n");

    printf("recursive search 30: %s\n", search_recursive(root, 30) != NULL ? "found" : "not found");
    printf("iterative search 45: %s\n", search_iterative(root, 45) != NULL ? "found" : "not found");

    root = delete_node(root, 30);
    printf("after deleting 30: ");
    inorder(root);
    printf("\n");

    free_tree(root);
    return 0;
}
