#include <stdio.h>
#define MAX_TREE_NODE 101

int calculate_height(int tree[], int node, int height) {
  if (node >= MAX_TREE_NODE || tree[node] == 0) return height - 1;
  int left_child=node*2;
  int right_child=node*2+1;
  int height_left=calculate_height(tree,left_child,height+1);
  int height_right=calculate_height(tree,right_child,height+1);
  int height_result=(height_left>height_right) ? height_left : height_right;
  return height_result;
}

// 균형트리 판별 함수
int is_balanced(int tree[]) {
  int height_leftsub=calculate_height(tree,2,0);
  int height_rightsub=calculate_height(tree,3,0);
  if((height_leftsub-height_rightsub)>1 || (height_leftsub-height_rightsub)<1) {
    return 0;
  }
  return 1;
}

// 중위 순회
void traverse_infix(int tree[], int node) {
  if (node >= MAX_TREE_NODE || tree[node] == 0) return;
  int left_child=node*2;
  int right_child=node*2+1;
  if(left_child!=0) traverse_infix(tree,left_child);
  printf("%d ",tree[node]);
  if(right_child!=0) traverse_infix(tree,right_child);
  return;
}

int search_last_node(int tree[], int index, int root) {
  int left_child=index*2;
  int right_child=index*2+1;
  if(index >= MAX_TREE_NODE || tree[index]==0) return 0;
  int right=search_last_node(tree, right_child, root);
  if(right) return right;
  int left=search_last_node(tree, left_child, root); return left ? left : index;
}

int search_node(int tree[], int index, int node, int root) {
  if(tree[index]==node) return index;
  int left_child=index*2;
  int right_child=index*2+1;
  int found=0; if(tree[left_child]!=0 && (found=search_node(tree, left_child, node, root))) return found; if(tree[right_child]!=0 && (found=search_node(tree, right_child, node, root))) return found;
  if(tree[right_child]!=0) search_node(tree, right_child, node, root);
  return 0;
}

int* delete_node(int tree[], int node) {
  int index_removed=search_node(tree,1,node,1);
  int last_node=search_last_node(tree,1,1);
  tree[index_removed]=tree[last_node];
  tree[last_node]=0;
  return tree;
}

int main() {
  // 0은 빈노드를 나타냄
  int tree[MAX_TREE_NODE]={0,35,18,68,7,26,0,99,3,12,22,30};
  int root=1;
  printf("이진 탐색 트리 중위 순회 결과:\n");
  traverse_infix(tree, 1);
  printf("\n");
  int flag_balanced=is_balanced(tree);
  if(flag_balanced) {
    printf("[균형 검사] 트리는 균형 잡혀 있습니다.");
  } else {
    printf("[균형 검사] 트리는 불균형입니다.");
  }

  printf("\n");
  printf("\n");

  printf("노드 99 삭제 후 중위 순회 결과:\n");
  int* tree_deleted=delete_node(tree,99);
  traverse_infix(tree_deleted, 1);
  printf("\n");
  flag_balanced=is_balanced(tree_deleted);
  if(flag_balanced) {
    printf("[균형 검사] 트리는 균형 잡혀 있습니다.");
  } else {
    printf("[균형 검사] 트리는 불균형입니다.");
  }
  return 0;
}
