#include <stdio.h>
#include <stdlib.h>

#define MAX_ELEMENT 200

typedef struct TreeNode {
    int weight;
    char ch;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

typedef struct {
    TreeNode *ptree;
    char ch;
    int key;
} element;

typedef struct {
    element heap[MAX_ELEMENT];
    int heap_size;
} HeapType;

static HeapType *create(void)
{
    return (HeapType *)malloc(sizeof(HeapType));
}

static void init(HeapType *h)
{
    h->heap_size = 0;
}

static void insert_min_heap(HeapType *h, element item)
{
    int i = ++h->heap_size;

    while (i != 1 && item.key < h->heap[i / 2].key) {
        h->heap[i] = h->heap[i / 2];
        i /= 2;
    }
    h->heap[i] = item;
}

static element delete_min_heap(HeapType *h)
{
    int parent = 1;
    int child = 2;
    element item = h->heap[1];
    element temp = h->heap[h->heap_size--];

    while (child <= h->heap_size) {
        if (child < h->heap_size && h->heap[child].key > h->heap[child + 1].key) {
            child++;
        }
        if (temp.key < h->heap[child].key) {
            break;
        }
        h->heap[parent] = h->heap[child];
        parent = child;
        child *= 2;
    }
    h->heap[parent] = temp;
    return item;
}

static TreeNode *make_tree(TreeNode *left, TreeNode *right)
{
    TreeNode *node = (TreeNode *)malloc(sizeof(TreeNode));
    if (node == NULL) {
        fprintf(stderr, "allocation failed\n");
        exit(1);
    }
    node->left = left;
    node->right = right;
    node->weight = 0;
    node->ch = '\0';
    return node;
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

static int is_leaf(TreeNode *root)
{
    return root->left == NULL && root->right == NULL;
}

static void print_array(int codes[], int n)
{
    for (int i = 0; i < n; i++) {
        printf("%d", codes[i]);
    }
    printf("\n");
}

static void print_codes(TreeNode *root, int codes[], int top)
{
    if (root->left != NULL) {
        codes[top] = 1;
        print_codes(root->left, codes, top + 1);
    }
    if (root->right != NULL) {
        codes[top] = 0;
        print_codes(root->right, codes, top + 1);
    }
    if (is_leaf(root)) {
        printf("%c: ", root->ch);
        print_array(codes, top);
    }
}

static void huffman_tree(int freq[], char ch_list[], int n)
{
    HeapType *heap = create();
    element e;
    int codes[100];
    int top = 0;

    if (heap == NULL) {
        fprintf(stderr, "allocation failed\n");
        exit(1);
    }
    init(heap);

    for (int i = 0; i < n; i++) {
        TreeNode *node = make_tree(NULL, NULL);
        e.ch = ch_list[i];
        node->ch = ch_list[i];
        e.key = freq[i];
        node->weight = freq[i];
        e.ptree = node;
        insert_min_heap(heap, e);
    }

    for (int i = 1; i < n; i++) {
        element e1 = delete_min_heap(heap);
        element e2 = delete_min_heap(heap);
        TreeNode *x = make_tree(e1.ptree, e2.ptree);

        e.key = e1.key + e2.key;
        x->weight = e.key;
        e.ptree = x;
        printf("%d+%d->%d\n", e1.key, e2.key, e.key);
        insert_min_heap(heap, e);
    }

    e = delete_min_heap(heap);
    print_codes(e.ptree, codes, top);
    destroy_tree(e.ptree);
    free(heap);
}

int main(void)
{
    char ch_list[] = { 's', 'i', 'n', 't', 'e' };
    int freq[] = { 4, 6, 8, 12, 15 };

    huffman_tree(freq, ch_list, 5);
    return 0;
}
