#include <stdio.h>
#include <stdlib.h>

typedef int element;

typedef struct DListNode {
    element data;
    struct DListNode *llink;
    struct DListNode *rlink;
} DListNode;

void init(DListNode *phead)
{
    phead->llink = phead;
    phead->rlink = phead;
}

void print_dlist(DListNode *phead)
{
    DListNode *p;

    for (p = phead->rlink; p != phead; p = p->rlink) {
        printf("<-| |%d| |-> ", p->data);
    }
    printf("\n");
}

void dinsert(DListNode *before, element data)
{
    DListNode *newnode = (DListNode *)malloc(sizeof(DListNode));

    if (newnode == NULL) {
        fprintf(stderr, "Memory allocation error\n");
        exit(1);
    }
    newnode->data = data;
    newnode->llink = before;
    newnode->rlink = before->rlink;
    before->rlink->llink = newnode;
    before->rlink = newnode;
}

void ddelete(DListNode *head, DListNode *removed)
{
    if (removed == head) {
        return;
    }
    removed->llink->rlink = removed->rlink;
    removed->rlink->llink = removed->llink;
    free(removed);
}

void destroy(DListNode *head)
{
    while (head->rlink != head) {
        ddelete(head, head->rlink);
    }
    free(head);
}

int main(void)
{
    DListNode *head = (DListNode *)malloc(sizeof(DListNode));

    if (head == NULL) {
        fprintf(stderr, "Memory allocation error\n");
        return 1;
    }
    init(head);

    printf("추가 단계\n");
    for (int i = 0; i < 5; i++) {
        dinsert(head, i);
        print_dlist(head);
    }

    printf("\n삭제 단계\n");
    for (int i = 0; i < 5; i++) {
        print_dlist(head);
        ddelete(head, head->rlink);
    }

    destroy(head);
    return 0;
}
