#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ELEMENT 100
#define swap(a,b,t) ((t)=(a), (a)=(b), (b)=(t)) // swap macro

typedef struct TreeNode {
  struct TreeNode* left;
  struct TreeNode* right;
  char ch;
  int data; // data = element key = weight
} TreeNode;

typedef struct { // node wrapper: 래퍼에 data 필드도 정의하면 원소 자료형과 무관하게 힙 사용 가능
    TreeNode *node;
    char ch;
    int key;
} element;

typedef struct {
    element heap[MAX_ELEMENT];
    int heap_size;
} HeapType;

void init_heap(HeapType *h) {
  h->heap_size=0;
  return;
}

void init_node(TreeNode* node) {
  node->left=NULL;
  node->right=NULL;
  node->ch='\0';
  node->data=0;
  return;
}

int is_leaf(TreeNode* node) {
  return node->left==NULL && node->right==NULL;
}

// int has_child(TreeNode* node) {
//   return !(node->left==NULL && node->right==NULL);
// }

void insert_max_heap(HeapType *h, element e) { // bottom-up
  element tmp;
  int item=e.key;
  int child_idx=++h->heap_size; // h->heap_size++ (X) 첫 인덱스는 1부터 시작해야
  int parent_idx=child_idx/2;
  while(parent_idx>0 && h->heap[parent_idx].key<item) {
    swap(h->heap[parent_idx], h->heap[child_idx], tmp);
    child_idx=parent_idx;
    parent_idx /= 2;
  }
  h->heap[child_idx]=e;
  return;
}

void insert_min_heap(HeapType *h, element e) { // bottom-up
  element tmp;
  int item=e.key;
  int child_idx=++h->heap_size; // h->heap_size++ (X) 첫 인덱스는 1부터 시작해야
  int parent_idx=child_idx/2;
  while(parent_idx>0 && h->heap[parent_idx].key>item) {
    swap(h->heap[parent_idx], h->heap[child_idx], tmp);
    child_idx=parent_idx;
    parent_idx /= 2;
  }
  h->heap[child_idx]=e;
  return;
}

TreeNode* insert_treenode(TreeNode *root, element item) {
  // if(!root) return NULL;
  TreeNode* tmp;
  TreeNode *node=item.node;
  node->left=root;
  node->right=root->right;
  root=node;

  while(!is_leaf(node) && (node->data<node->left->data || node->data>node->right->data)) {
    if(node->data<node->left->data) {
      swap(node->right, node->right->right, tmp); // pointer swap
      swap(node->left, node->left->left, tmp);
      // node=node->left;
      if(is_leaf(node)) break;
    }
    else if(node->data>node->right->data){
      swap(node->left, node->left->left, tmp);
      swap(node->right, node->right->right, tmp);
      // node=node->right;
      if(is_leaf(node)) break;
    }
  }
  return root;
}

element delete_max_heap(HeapType *h) { // root에 마지막 노드 배치->top-down comparision
  element tmp;
  int idx=1; // top-down 순회 인덱스 (last key가 있는 노드 인덱스)
  element removed=h->heap[1];
  int last_key=h->heap[h->heap_size--].key;
  h->heap[1].key=last_key; // root 삭제 효과

  while(idx*2<=h->heap_size) { // 1. top-down으로 순회하는 idx가 리프노드거나 
    // idx: 더 큰 자식노드를 넣을 현재 인덱스
    if(last_key>=h->heap[idx*2].key && last_key>=h->heap[idx*2+1].key) break; // 2. 현재 max heap을 만족하면 종료
    if(h->heap[idx*2].key>h->heap[idx*2+1].key) {
      swap(h->heap[idx],h->heap[idx*2], tmp);
      idx=idx*2;
    }
    else { 
      swap(h->heap[idx],h->heap[idx*2+1], tmp);
      idx=idx*2+1;
    }
  }
  return removed;
}

void destroy_tree(TreeNode *root) {
  if(root==NULL) return;
  destroy_tree(root->left);
  destroy_tree(root->right);
  free(root);
  return;
}

element delete_min_heap(HeapType *h) { // root에 마지막 노드 배치->top-down comparision
  element tmp;
  element removed=h->heap[1];
  element last_e=h->heap[h->heap_size--];
  h->heap[1]=last_e; // root 삭제 효과
  // int idx=1; // top-down 순회 인덱스 (last key가 있는 노드 인덱스)
  int parent=1;
  int child=2;

  while(child<=h->heap_size) { 
    if(child<h->heap_size && h->heap[child].key>h->heap[child+1].key) child++; // 더 작은 자식 선택
    if(last_e.key<=h->heap[child].key) break;
    swap(h->heap[parent],h->heap[child],tmp);
    parent=child;
    child *= 2;
    // if(h->heap[child].key<h->heap[idx*2+1].key) {
    //   swap(h->heap[idx],h->heap[idx*2],tmp);
    //   idx=idx*2;
    // }
    // else { 
    //   swap(h->heap[idx],h->heap[idx*2+1],tmp);
    //   idx=idx*2+1;
    // }
  }
  return removed;
}

void print_heap_arr(HeapType *h) {
  for(int i=1;i<=h->heap_size;i++) printf("%d ", h->heap[i].key);
  printf("\n");
}

void print_max_heap(HeapType *h) { // heap 출력은 delete heap 사용
  element e;
  int size=h->heap_size;
  for(int i=1;i<=size;i++) { // i<=h->heap_size; (X) 힙 삭제연산마다 크기가 줄어서 절반만 출력됨
    e=delete_max_heap(h);
    printf("%d ", e.key);
  }
  printf("\n");
  return;
}

void print_min_heap(HeapType *h) { // heap 출력은 delete heap 사용
  element e;
  int size=h->heap_size;
  for(int i=1;i<=size;i++) { // i<=h->heap_size; (X) 힙 삭제연산마다 크기가 줄어서 절반만 출력됨
    e=delete_min_heap(h);
    printf("%d ", e.key);
  }
  printf("\n");
  return;
}

static void print_array(int codes[], int n)
{
    for (int i = 0; i < n; i++) {
        printf("%d", codes[i]);
    }
    printf("\n");
}

TreeNode* make_tree(HeapType *h) {
  int size=h->heap_size;
  element e1,e2;

  while(h->heap_size!=1) {
    e1=delete_min_heap(h);
    e2=delete_min_heap(h);

    element e;
    e.node=malloc(sizeof(TreeNode));
    init_node(e.node);
    e.ch='\0';
    e.node->left=e1.node;
    e.node->right=e2.node;
    e.key=e1.key+e2.key;
    insert_min_heap(h, e);
    // root=insert_treenode(e.node, e); // 허프만에서는 treenode 삽입연산 불필요
  }
  return h->heap[1].node;
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

void huffman_main() {
  int codes[100];
  HeapType h;
  init_heap(&h);
  char ch_list[] = { 's', 'i', 'n', 't', 'e' };
  int freq[] = { 4, 6, 8, 12, 15 };
  srand(time(NULL));

  for(int i=0;i<5;i++) {
    element e;
    e.node=malloc(sizeof(TreeNode));
    init_node(e.node);
    e.node->data=e.key=freq[i]; // treenode, element 동시에 초기화
    e.node->ch=e.ch=ch_list[i];

    insert_min_heap(&h, e);
  }
  TreeNode *root=make_tree(&h);
  print_codes(root, codes, 0);
  return;
}

int main() {
  // heap_sort_main();
  huffman_main();
  return 0;
}