#include <stdio.h>

#define STACK_SIZE 100

typedef struct TreeNode {
    int data;
    struct TreeNode* left, * right; 
} TreeNode;

static int top = -1;
static TreeNode *stack[STACK_SIZE];

static void push(TreeNode *p)
{
    if (top < STACK_SIZE - 1) {
        stack[++top] = p;
    }
}

static TreeNode *pop(void)
{
    if (top >= 0) {
        return stack[top--];
    }
    return NULL;
}

int peek(TreeNode* stack[]) {
  return stack[top]->data;
}

void print_stack(TreeNode* stack[], int top) {
  printf("Stack: [");
  for(int i=0;i<top;i++) {
    printf("%d, ",stack[i]->data);
  }
  if(top==-1) {
    printf("]\n");
    return;
  }
  printf("%d]\n",stack[top]->data);
  return;
}

static void postorder_iter(TreeNode *root)
{
    // out_stack은 root -> right -> left 순서를 뒤집어 출력하기 위한 보조 스택이다.
    TreeNode *out_stack[STACK_SIZE];
    int out_top = -1;

    // 첫 번째 스택은 아직 방문할 노드를 저장한다.
    top = -1;
    if (root != NULL) {
        push(root);
    }

    while (top >= 0) {
        // 먼저 root -> right -> left 순서로 노드를 꺼내 out_stack에 저장한다.
        // if(top>=0) print_stack(stack,top);
        root = pop();
        if (out_top < STACK_SIZE - 1) {
            out_stack[++out_top] = root;
        }

        // left를 먼저 넣고 right를 나중에 넣으면 pop할 때 right가 먼저 나온다.
        if (root->left != NULL) {
            push(root->left);
        }
        if (root->right != NULL) {
            push(root->right);
        }
        // while (out_top >= 0) {
        //     root = out_stack[out_top--];
        //     printf("Visited: %d, ", root->data);
        //     print_stack(stack,top);
        // }
        if(root->left==NULL && root->right==NULL && top>=0) {
          while (out_top >= 0) {
              root = out_stack[out_top--];
              printf("Visited: %d, ", root->data);
              print_stack(stack,top);
          }
        }
        // while (out_top >= 0) {
        //     root = out_stack[out_top--];
        //     printf("Visited: %d, ", root->data);
        //     print_stack(stack,top);
        // }
    }

    // out_stack에서 거꾸로 꺼내면 left -> right -> root, 즉 후위 순회가 된다.
    // while (out_top >= 0) {
    //     root = out_stack[out_top--];
    //     printf("Visited: %d, ", root->data);
    //     print_stack(stack,top);
    // }
}

int main(void)
{
    TreeNode n1 = { 1, NULL, NULL }; 
    TreeNode n2 = { 3, &n1, NULL }; 
    TreeNode n3 = { 8, NULL, NULL }; 
    TreeNode n4 = { 7, NULL, &n3 }; 
    TreeNode n5 = { 5, &n2, &n4 }; 
    TreeNode n6 = { 12, NULL, NULL }; 
    TreeNode n7 = { 25, NULL, NULL }; 
    TreeNode n8 = { 20, NULL, &n7 }; 
    TreeNode n9 = { 15, &n6, &n8 }; 
    TreeNode n10 = { 10, &n5, &n9 };

    printf("후위순회과정\n");
    // printf("후위순회결과 = ");
    postorder_iter(&n10);
    printf("\n");
    return 0;
}
