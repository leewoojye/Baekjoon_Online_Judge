#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ELEMENT 200
#define MAX_CODE_LEN 100
#define MAX_ENCODED_LEN 1000
#define ASCII_SIZE 128

typedef struct TreeNode {
    int weight;
    char ch;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

typedef struct {
    TreeNode *ptree;
    int key;
    int order;
} element;

typedef struct {
    element heap[MAX_ELEMENT];
    int heap_size;
} HeapType;

typedef struct {
    char code[MAX_CODE_LEN];
} CodeTable;

// 오류 메시지를 출력하고 프로그램을 종료한다.
static void error(const char *message)
{
    fprintf(stderr, "%s\n", message);
    exit(1);
}

// 허프만 노드를 저장할 최소 힙을 초기화한다.
static void init_heap(HeapType *h)
{
    h->heap_size = 0;
}

// 힙 원소의 빈도와 삽입 순서를 기준으로 우선순위를 비교한다.
static int less_element(element a, element b)
{
    if (a.key != b.key) {
        return a.key < b.key;
    }
    return a.order < b.order;
}

// 최소 힙에 허프만 노드 원소를 삽입한다.
static void insert_min_heap(HeapType *h, element item)
{
    int i;

    if (h->heap_size >= MAX_ELEMENT - 1) {
        error("heap is full");
    }

    i = ++h->heap_size;
    while (i != 1 && less_element(item, h->heap[i / 2])) {
        h->heap[i] = h->heap[i / 2];
        i /= 2;
    }
    h->heap[i] = item;
}

// 최소 힙에서 가장 작은 빈도의 원소를 삭제해 반환한다.
static element delete_min_heap(HeapType *h)
{
    int parent;
    int child;
    element item;
    element temp;

    if (h->heap_size == 0) {
        error("heap is empty");
    }

    item = h->heap[1];
    temp = h->heap[h->heap_size--];
    parent = 1;
    child = 2;

    while (child <= h->heap_size) {
        if (child < h->heap_size && less_element(h->heap[child + 1], h->heap[child])) {
            child++;
        }
        if (!less_element(h->heap[child], temp)) {
            break;
        }
        h->heap[parent] = h->heap[child];
        parent = child;
        child *= 2;
    }
    h->heap[parent] = temp;
    return item;
}

// 주어진 자식 노드로 새 허프만 트리 노드를 생성한다.
static TreeNode *make_node(TreeNode *left, TreeNode *right)
{
    TreeNode *node = (TreeNode *)malloc(sizeof(TreeNode));

    if (node == NULL) {
        error("allocation failed");
    }
    node->weight = 0;
    node->ch = '\0';
    node->left = left;
    node->right = right;
    return node;
}

// 허프만 트리의 모든 노드를 후위 순회로 해제한다.
static void destroy_tree(TreeNode *root)
{
    if (root == NULL) {
        return;
    }
    destroy_tree(root->left);
    destroy_tree(root->right);
    free(root);
}

// 노드가 리프 노드인지 확인한다.
static int is_leaf(TreeNode *root)
{
    return root != NULL && root->left == NULL && root->right == NULL;
}

// 허프만 코드를 출력하고 문자별 코드 테이블에 저장한다.
static void store_and_print_codes(TreeNode *root, int codes[], int top, CodeTable table[])
{
    if (root == NULL) {
        return;
    }

    if (root->left != NULL) {
        codes[top] = 1;
        store_and_print_codes(root->left, codes, top + 1, table);
    }
    if (root->right != NULL) {
        codes[top] = 0;
        store_and_print_codes(root->right, codes, top + 1, table);
    }

    if (is_leaf(root)) {
        printf("%c: ", root->ch);
        for (int i = 0; i < top; i++) {
            printf("%d", codes[i]);
            table[(int)root->ch].code[i] = (char)('0' + codes[i]);
        }
        table[(int)root->ch].code[top] = '\0';
        printf("\n");
    }
}

// 빈도 배열로 허프만 트리를 만들고 코드 테이블을 채운다.
static TreeNode *huffman_tree(int freq[], char ch_list[], int n, CodeTable table[])
{
    HeapType heap;
    int order = 0;
    int codes[MAX_CODE_LEN];

    init_heap(&heap);

    for (int i = 0; i < ASCII_SIZE; i++) {
        table[i].code[0] = '\0';
    }

    for (int i = 0; i < n; i++) {
        TreeNode *node = make_node(NULL, NULL);
        element item;

        node->ch = ch_list[i];
        node->weight = freq[i];
        item.ptree = node;
        item.key = freq[i];
        item.order = order++;
        insert_min_heap(&heap, item);
    }

    printf("Merge Process\n");
    for (int i = 1; i < n; i++) {
        element e1 = delete_min_heap(&heap);
        element e2 = delete_min_heap(&heap);
        TreeNode *node = make_node(e1.ptree, e2.ptree);
        element item;

        node->weight = e1.key + e2.key;
        item.ptree = node;
        item.key = node->weight;
        item.order = order++;

        printf("%d+%d->%d\n", e1.key, e2.key, item.key);
        insert_min_heap(&heap, item);
    }

    element root = delete_min_heap(&heap);
    printf("\nHuffman Codes\n");
    store_and_print_codes(root.ptree, codes, 0, table);
    return root.ptree;
}

// 코드 테이블을 이용해 문자열을 이진 코드 문자열로 인코딩한다.
static void encode_message(const char message[], CodeTable table[], char encoded[])
{
    encoded[0] = '\0';

    for (int i = 0; message[i] != '\0'; i++) {
        char *code = table[(int)message[i]].code;

        if (code[0] == '\0') {
            error("missing character code");
        }
        strcat(encoded, code);
    }
}

// 허프만 트리를 따라 이진 코드 문자열을 원문으로 디코딩한다.
static void decode_message(const char encoded[], TreeNode *root, char decoded[])
{
    int j = 0;
    TreeNode *current = root;

    for (int i = 0; encoded[i] != '\0'; i++) {
        if (encoded[i] == '1') {
            current = current->left;
        } else if (encoded[i] == '0') {
            current = current->right;
        } else {
            continue;
        }

        if (is_leaf(current)) {
            decoded[j++] = current->ch;
            current = root;
        }
    }
    decoded[j] = '\0';
}

// 허프만 트리 생성, 인코딩, 디코딩 예제를 실행한다.
int main(void)
{
    char ch_list[] = { 's', 'i', 'n', 't', 'e' };
    int freq[] = { 4, 6, 8, 12, 15 };
    char message[] = "sent";
    char encoded[MAX_ENCODED_LEN];
    char decoded[MAX_ENCODED_LEN];
    int n = (int)(sizeof(freq) / sizeof(freq[0]));
    CodeTable table[ASCII_SIZE];
    TreeNode *root = huffman_tree(freq, ch_list, n, table);

    encode_message(message, table, encoded);
    decode_message(encoded, root, decoded);

    printf("\nMessage: %s\n", message);
    printf("Encoded: %s\n", encoded);
    printf("Decoded: %s\n", decoded);

    destroy_tree(root);
    return 0;
}
