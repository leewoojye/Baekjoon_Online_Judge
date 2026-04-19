#include <stdio.h>
#include <stdlib.h>
// #define MAX_SIZE 100;

typedef int element;

typedef struct ListNode {
    element data;
    struct ListNode *link;
} ListNode;

typedef struct ListType // meta type 불필요
{
  ListNode *head;
} ListType;

void init_list(ListType *plist) {
  plist->head=NULL;
}

int is_empty(ListType *plist) {
  return plist->head==NULL;
}

ListNode* insert_first(ListType *plist, int e) {
  ListNode *p=(ListNode*)malloc(sizeof(ListNode));
  p->data=e;
  if(plist->head==NULL) {
    plist->head=p->link=p;
  }
  else {
    p->link=plist->head->link;
    plist->head->link=p;
  }
  return plist->head;
}

ListNode* insert_last(ListType *plist, int e) {
  ListNode *p=(ListNode*)malloc(sizeof(ListNode));
  p->data=e;
  if(plist->head==NULL) {
    plist->head=p->link=p;
  }
  else {
    p->link=plist->head->link;
    plist->head->link=p;
    plist->head=p;
  }
  return plist->head;
}

void print_list(ListNode *head) {
  if(head==NULL) return;
  ListNode *p=head;
  p=p->link;
  int count=0; // 노드 개수
  do {
    count++;
    printf("%d->",p->data);
    p=p->link;
  } while(p!=head->link);
  printf("\n");
  return;
}

int main() {
  return 0;
}
