#include <stdio.h>
#include <stdlib.h>

typedef struct HeapNode {
int key;
struct HeapNode* left;
struct HeapNode* right;
struct HeapNode* parent;
} HeapNode;

typedef struct {
HeapNode* root;
int heap_size;
} LinkedHeap;

static HeapNode *search_recursive(HeapNode *node, HeapNode* key)
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

static HeapNode *search_iterative(HeapNode *node, HeapNode* key)
{
    while (node != NULL) {
        if (key->key == node->key) {
            return node;
        }
        if (key->key < node->key) {
            node = node->left;
        } else {
            node = node->right;
        }
    }
    return NULL;
}

static HeapNode *new_node(int item)
{
    HeapNode *temp = (HeapNode *)malloc(sizeof(HeapNode));
    if (temp == NULL) {
        fprintf(stderr, "allocation failed\n");
        exit(1);
    }
    temp->key = item;
    temp->left = NULL;
    temp->right = NULL;
    return temp;
}

static HeapNode *insert_node(HeapNode *node, HeapNode* key)
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

static HeapNode *min_value_node(HeapNode *node)
{
    HeapNode *current = node;

    while (current->left != NULL) {
        current = current->left;
    }
    return current;
}

static HeapNode *delete_node(HeapNode *root, HeapNode* key)
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
            HeapNode *temp = root->right;
            free(root);
            return temp;
        }
        if (root->right == NULL) {
            HeapNode *temp = root->left;
            free(root);
            return temp;
        }

        HeapNode *temp = min_value_node(root->right);
        root->key = temp->key;
        root->right = delete_node(root->right, temp->key);
    }
    return root;
}

static void inorder(HeapNode *root)
{
    if (root != NULL) {
        inorder(root->left);
        printf("[%d] ", root->key);
        inorder(root->right);
    }
}

static void free_tree(HeapNode *root)
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
    LinkedHeap *root;
    root->heap_size=0;
    root->root=NULL;
    int data[8] = {15,3,27,8,20,1,30,12};
    for(int i=0;i<8;i++) {
      HeapNode *node=new_node(data[i]);
      insert_node(root,node);
    }
    return 0;
}
