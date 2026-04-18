#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char element[100];

typedef struct ListNode {
    element data;
    struct ListNode *link;
} ListNode;

ListNode *insert_first(ListNode *head, const char *data)
{
    ListNode *node = (ListNode *)malloc(sizeof(ListNode));

    if (node == NULL) {
        fprintf(stderr, "Memory allocation error\n");
        exit(1);
    }
    strcpy(node->data, data);
    if (head == NULL) {
        head = node;
        node->link = head;
    } else {
        node->link = head->link;
        head->link = node;
    }
    return head;
}

void free_list(ListNode *head)
{
    ListNode *first;
    ListNode *p;

    if (head == NULL) {
        return;
    }
    first = head->link;
    p = first;
    do {
        ListNode *next = p->link;

        free(p);
        p = next;
    } while (p != first);
}

int main(void)
{
    ListNode *head = NULL;
    ListNode *p;

    head = insert_first(head, "KIM");
    head = insert_first(head, "PARK");
    head = insert_first(head, "CHOI");

    p = head;
    for (int i = 0; i < 10; i++) {
        printf("현재 차례=%s\n", p->data);
        p = p->link;
    }

    free_list(head);
    return 0;
}
