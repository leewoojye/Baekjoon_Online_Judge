#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct ListNode
{
  element data;
  struct ListNode* link;
} ListNode;

int is_empty(ListNode *head) {
  return head==NULL;
}

ListNode* insert_first(ListNode *head, element data) {
  ListNode *node=(ListNode*)malloc(sizeof(ListNode));
  node->data=data;
  node->link=head;
  head=node;
  return head;
}

element delete_next(ListNode *prev) { // prev 다음 노드를 제거
  if(prev->link==NULL) return 1;
  ListNode *removed=prev->link;
  element data=removed->data;
  prev->link=removed->link;
  free(removed);
  return data;
}

void print_list(ListNode *head) {
  ListNode *p=head;
  for(;p!=NULL;p=p->link) {
    printf("%d->",p->data);
  }
  printf("NULL\n");
  return;
}

int main() {
  ListNode *head=NULL;
  head=insert_first(head,10);
  head=insert_first(head,20);
  head=insert_first(head,30);
  head=insert_first(head,20);
  head=insert_first(head,40);
  head=insert_first(head,10);
  print_list(head);

  ListNode *p1=head;
  ListNode *p2;
  for(;p1->link!=NULL;p1=p1->link) {
    p2=p1;
    for(;p2->link!=NULL;) {
      if(p1->data==p2->link->data) {
        element e = delete_next(p2);
      } else {
        p2=p2->link; // 중복이 아닐때만 p2 포인터 이동
      }
    }
  }
  print_list(head);
  free(head);
  return 0;
}