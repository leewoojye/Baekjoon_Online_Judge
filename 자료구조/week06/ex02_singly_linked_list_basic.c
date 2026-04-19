#include <stdio.h>
#include <stdlib.h>

typedef int element;

typedef struct ListNode {
    element data;
    struct ListNode *link;
} ListNode;

ListNode *insert_first(ListNode *head, int value)
{
    ListNode *p = (ListNode *)malloc(sizeof(ListNode));

    p->data = value;
    p->link = head;
    head = p;
    return head;
}

ListNode *insert(ListNode *head, ListNode *pre, element value)
{
    ListNode *p = (ListNode *)malloc(sizeof(ListNode));

    p->data = value;
    p->link = pre->link;
    pre->link = p;
    return head;
}

ListNode *delete_first(ListNode *head)
{
    ListNode *removed;

    if (head == NULL) {
        return NULL;
    }
    removed = head;
    head = removed->link;
    free(removed);
    return head;
}

ListNode *delete_node(ListNode *head, ListNode *pre)
{
    ListNode *removed;

    if (pre == NULL || pre->link == NULL) {
        return head;
    }
    removed = pre->link;
    pre->link = removed->link;
    free(removed);
    return head;
}

void print_list(ListNode *head)
{
    for (ListNode *p = head; p != NULL; p = p->link) {
        printf("%d->", p->data);
    }
    printf("NULL\n");
}

void free_list(ListNode *head)
{
    while (head != NULL) {
        ListNode *next = head->link;

        free(head);
        head = next;
    }
}

ListNode* reverse_list(ListNode *head) {
    ListNode *pos=head; // 다음 단계에 역순으로 만들 노드
    ListNode *reversing=head; // 현재 역순으로 만들 노드 = link를 반대편으로 바꿀 노드
    ListNode *reversed=NULL; // 현재까지 역순리스트의 head
    // for(;reversing!=NULL;) {
    //     reversing->link=reversed;
    //     reversed=reversing;
    //     reversing=pos;
    //     pos=pos->link;
    // }
    for(;pos!=NULL;) {
        
    }
    return reversed;
}

ListNode* reverse(ListNode *head) {
    ListNode *p,*q,*r;
    p=head; // 역순으로 만들 리스트
    q=NULL; // 역순으로 만들 노드
    while(p!=NULL) {
        r=q; // 역순으로 된 리스트
        q=p;
        p=p->link;
        q->link=r;
    }
    return q;
}

int main(void)
{
    // ListNode *manual_head = NULL;
    // ListNode *p;
    ListNode *head = NULL;

    // manual_head = (ListNode *)malloc(sizeof(ListNode));
    // manual_head->data = 10;
    // manual_head->link = NULL;

    // p = (ListNode *)malloc(sizeof(ListNode));
    // p->data = 20;
    // p->link = NULL;
    // manual_head->link = p;
    // print_list(manual_head);
    // free_list(manual_head);

    for (int i = 0; i < 5; i++) {
        head = insert_first(head, i);
        print_list(head);
    }

    head = reverse(head);
    print_list(head);

    // if (head != NULL && head->link != NULL) {
    //     head = insert(head, head, 99);
    //     print_list(head);
    //     head = delete_node(head, head);
    //     print_list(head);
    // }

    // for (int i = 0; i < 5 && head != NULL; i++) {
    //     head = delete_first(head);
    //     print_list(head);
    // }

    free_list(head);
    return 0;
}
