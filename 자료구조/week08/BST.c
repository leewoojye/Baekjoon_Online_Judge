#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct TreeNode {
    int data;
    struct TreeNode *left;
    struct TreeNode *right;
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
    return node;
}

int min_value_search(TreeNode* node) {
  if(node->left==NULL) return node->data;
  return min_value_search(node->left);
}

// 변경된 루트 반환
// TreeNode* insert_node(TreeNode* root, int item) {
//   TreeNode* new_node=make_node(item);
//   if(!root) return new_node; // 빈 트리면 새 노드를 반환
//   TreeNode* parent=root;
//   TreeNode* child;
//   if()
// }

// 이진탐색트리 연산을 순환구조로 구현
TreeNode* insert_node(TreeNode* node, int item) {
  TreeNode* new_node=make_node(item);
  if(!node) return new_node; // 빈 트리면 새 노드를 반환
  if(node->data<item) {
    node->right=insert_node(node->right, item); // 순환구조->node를 직접 갱신하지 않고 순환호출
  }
  else {
    node->left=insert_node(node->left, item);
  }
  return node;
}

TreeNode* delete_node(TreeNode* node, int item) {
  if(!node) return NULL;
  if(node->data>item) { // item이 node data보다 작으면 node 좌측 서브트리에 있다는 의미 + 좌측 서브트리는 빈 트리가 아님을 암시
    node=delete_node(node->left, item);
  }
  else if(node->data<item) {
    node=delete_node(node->right, item);
  }
  else {
    // 좌,우 서브트리 중 하나가 빈트리거나 둘 다 빈트리가 아님
    if(node->left==NULL) {
      TreeNode* temp=node->right;
      free(node);
      return temp;
    } else if(node->right==NULL) {
      TreeNode* temp=node->left;
      free(node);
      return temp;
    } else {
      int temp_data=min_value_search(node->right);
      node->data=temp_data;
      node=delete_node(node->right, temp_data); // 우측 서브트리에서 가져온 최소노드 제거
    }
  }
  return node;
}

// 재귀 탐색
TreeNode* search_tree(TreeNode* node, int item) {
  // int flag=0;
  // if(node==NULL) return 0;
  // if(node->data==item) return 1;
  // if(node->left!=NULL && search_tree(node->left,item)) return 1;
  // if(node->right!=NULL && search_tree(node->right,item)) return 1;
  // return 0;

  // 이진탐색트리는 좌우 자손, 루트 간 대소관계가 있고 이를 거의 항상 활용함
  if(node==NULL) return NULL;
  if(node->data==item) return node;
  if(node->data>item) return search_tree(node->left,item);
  else return search_tree(node->right,item);
  // return NULL;
}

// 반복 탐색
TreeNode* search_tree_iter(TreeNode* node, int item) {
  if(node==NULL) return NULL;
  while(node!=NULL) {
    if(node->data==item) return node;
    if(node->data>item) node=node->left;
    else node=node->right;
  }
  return NULL;
}

void inorder_traversal(TreeNode* root) {
  if(root==NULL) return;
  if(root->left!=NULL) inorder_traversal(root->left);
  printf("%d ",root->data);
  if(root->right!=NULL) inorder_traversal(root->right);
  return;
}

int main() {
  srand(time(NULL));
  TreeNode* root=NULL;
  int item;

  for(int i=0;i<10;i++) {
    item=rand()%100+1;
    root=insert_node(root,item);
  }
  inorder_traversal(root);
  return 0;
}