#include <stdio.h>
#include <stdlib.h>

typedef int element;

typedef struct ListNode {
    element coef;
    element expon;
    struct ListNode *link;
} ListNode;

typedef struct Header {
  int size;
  ListNode *tail, *head;
} Header;

Header *insert_first(Header *header, int coef, int expon)
{
    ListNode *p = (ListNode *)malloc(sizeof(ListNode));
    if(p==NULL) return 0;
    p->coef = coef;
    p->expon = expon;
    p->link=header->head;
    header->head=p;
    return header;
}

Header *insert_last(Header *header, int coef, int expon)
{
    ListNode *p = (ListNode *)malloc(sizeof(ListNode));
    if(p==NULL) return 0;
    p->coef = coef;
    p->expon = expon;
    if(header->tail==NULL) {
      header->head=header->tail=p;
      p->link=NULL;
    } else {
      header->tail->link=p;
      header->tail=p;
      p->link=NULL;
    }
    header->size++;
    return header;
}

// ListNode *insert(ListNode *head, ListNode *pre, element value)
// {
//     ListNode *p = (ListNode *)malloc(sizeof(ListNode));

//     p->data = value;
//     p->link = pre->link;
//     pre->link = p;
//     return head;
// }

Header *delete_first(Header *header)
{
    ListNode *removed;

    if (header == NULL) {
        return NULL;
    }
    removed = header->head;
    header = removed->link;
    free(removed);
    return header;
}

// ListNode *delete_node(ListNode *head, ListNode *pre)
// {
//     ListNode *removed;

//     if (pre == NULL || pre->link == NULL) {
//         return head;
//     }
//     removed = pre->link;
//     pre->link = removed->link;
//     free(removed);
//     return head;
// }

void print_list(Header *header)
{
    for (ListNode *p = header->head; p != NULL; p = p->link) {
        if(p->link==NULL) {
          printf("%d",p->coef);
          return;
        }
        printf("%dx^%d + ", p->coef,p->expon);
    }
    printf("NULL\n");
}