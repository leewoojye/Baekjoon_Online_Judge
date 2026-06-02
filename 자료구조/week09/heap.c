#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ELEMENT 200
#define swap(a,b,t) ((t)=(a), (a)=(b), (b)=(t)) // swap macro

typedef struct {
    int key;
} element;

typedef struct {
    element heap[MAX_ELEMENT];
    int heap_size;
} HeapType;

typedef struct TreeNode {
  TreeNode* left;
  TreeNode* right;
  int data;
} TreeNode;

void init_heap(HeapType *h) {
  h->heap_size=0;
  return;
}

void init_node(TreeNode* node) {
  node->left=NULL;
  node->right=NULL;
  node->data='\0';
  return;
}

void insert_max_heap(HeapType *h, element e) { // bottom-up
  int tmp;
  int item=e.key;
  int child_idx=++h->heap_size; // h->heap_size++ (X) 첫 인덱스는 1부터 시작해야
  int parent_idx=child_idx/2;
  while(parent_idx>0 && h->heap[parent_idx].key<item) {
    swap(h->heap[parent_idx].key, h->heap[child_idx].key, tmp);
    child_idx=parent_idx;
    parent_idx /= 2;
  }
  h->heap[child_idx].key=item;
  return;
}

void insert_min_heap(HeapType *h, element e) { // bottom-up
  int tmp;
  int item=e.key;
  int child_idx=++h->heap_size; // h->heap_size++ (X) 첫 인덱스는 1부터 시작해야
  int parent_idx=child_idx/2;
  while(parent_idx>0 && h->heap[parent_idx].key>item) {
    swap(h->heap[parent_idx].key, h->heap[child_idx].key, tmp);
    child_idx=parent_idx;
    parent_idx /= 2;
  }
  h->heap[child_idx].key=item;
  return;
}

TreeNode* insert_treenode(TreeNode *root, int item) {
  if(!root) return;
  int tmp;
  // TreeNode *p=NULL; // 순회 포인터
  TreeNode *node=malloc(sizeof(TreeNode));
  init_node(node);
  node->data=item;
  node->left=root;
  node->right=root->right;
  root=node;

  while(node!=NULL && (item<node->left->data || item>node->right->data)) {
    if(item<node->left->data) {
      swap(node->data, node->left->data, tmp);
      node=node->left;
    }
    else if(item>node->right->data){
      swap(node->data, node->right->data, tmp);
      node=node->right;
    }
  }
  return root;
}

int delete_max_heap(HeapType *h) { // root에 마지막 노드 배치->top-down comparision
  int tmp;
  int idx=1; // top-down 순회 인덱스 (last key가 있는 노드 인덱스)
  int root_key=h->heap[1].key;
  int last_key=h->heap[h->heap_size--].key;
  h->heap[1].key=last_key; // root 삭제 효과

  while(idx*2<=h->heap_size) { // 1. top-down으로 순회하는 idx가 리프노드거나 
    // idx: 더 큰 자식노드를 넣을 현재 인덱스
    if(last_key>=h->heap[idx*2].key && last_key>=h->heap[idx*2+1].key) break; // 2. 현재 max heap을 만족하면 종료
    if(h->heap[idx*2].key>h->heap[idx*2+1].key) {
      swap(h->heap[idx].key,h->heap[idx*2].key, tmp);
      idx=idx*2;
    }
    else { 
      swap(h->heap[idx].key,h->heap[idx*2+1].key, tmp);
      idx=idx*2+1;
    }
  }
  return root_key;
}

void destroy_tree(TreeNode *root) {
  if(root==NULL) return;
  destroy_tree(root->left);
  destroy_tree(root->right);
  free(root);
  return;
}

int delete_min_heap(HeapType *h) { // root에 마지막 노드 배치->top-down comparision
  int tmp;
  int idx=1; // top-down 순회 인덱스 (last key가 있는 노드 인덱스)
  int root_key=h->heap[1].key;
  int last_key=h->heap[h->heap_size--].key;
  h->heap[1].key=last_key; // root 삭제 효과

  while(idx*2<=h->heap_size) { // 1. top-down으로 순회하는 idx가 리프노드거나 
    // idx: 더 큰 자식노드를 넣을 현재 인덱스
    if(last_key<=h->heap[idx*2].key && last_key<=h->heap[idx*2+1].key) break; // 2. 현재 max heap을 만족하면 종료
    if(h->heap[idx*2].key<h->heap[idx*2+1].key) {
      swap(h->heap[idx].key,h->heap[idx*2].key, tmp);
      idx=idx*2;
    }
    else { 
      swap(h->heap[idx].key,h->heap[idx*2+1].key, tmp);
      idx=idx*2+1;
    }
  }
  return root_key;
}

void print_heap_arr(HeapType *h) {
  for(int i=1;i<=h->heap_size;i++) printf("%d ", h->heap[i].key);
  printf("\n");
}

void print_max_heap(HeapType *h) { // heap 출력은 delete heap 사용
  int key;
  int size=h->heap_size;
  for(int i=1;i<=size;i++) { // i<=h->heap_size; (X) 힙 삭제연산마다 크기가 줄어서 절반만 출력됨
    key=delete_max_heap(h);
    printf("%d ", key);
    // print_heap_arr(h);
  }
  printf("\n");
  return;
}

void print_min_heap(HeapType *h) { // heap 출력은 delete heap 사용
  int key;
  int size=h->heap_size;
  for(int i=1;i<=size;i++) { // i<=h->heap_size; (X) 힙 삭제연산마다 크기가 줄어서 절반만 출력됨
    key=delete_min_heap(h);
    printf("%d ", key);
  }
  printf("\n");
  return;
}

void heap_sort_main() {
  srand(time(NULL));
  element e;
  HeapType h;
  init_heap(&h);
  for(int i=0;i<10;i++) {
    e.key=rand()%100+1;
    insert_min_heap(&h, e);
  }
  // print_max_heap(&h);
  print_min_heap(&h);
  return;
}

void LPT_main() {
  return;
}

void huffman_main() {
  char ch_list[] = { 's', 'i', 'n', 't', 'e' };
  int freq[] = { 4, 6, 8, 12, 15 };
  return;
}

int main() {
  heap_sort_main();
  return 0;
}