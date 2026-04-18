#include <stdio.h>
#include <stdlib.h>

typedef int element;

typedef struct ListNode {
    element data;
    struct ListNode *link;
} ListNode;

ListNode *insert_first(ListNode *head, element data)
{
    ListNode *node = (ListNode *)malloc(sizeof(ListNode));

    if (node == NULL) {
        fprintf(stderr, "Memory allocation error\n");
        exit(1);
    }
    node->data = data;
    if (head == NULL) {
        head = node;
        node->link = head;
    } else {
        node->link = head->link;
        head->link = node;
    }
    return head;
}

ListNode *insert_last(ListNode *head, element data)
{
    ListNode *node = (ListNode *)malloc(sizeof(ListNode));

    if (node == NULL) {
        fprintf(stderr, "Memory allocation error\n");
        exit(1);
    }
    node->data = data;
    if (head == NULL) {
        head = node;
        node->link = head;
    } else {
        node->link = head->link;
        head->link = node;
        head = node;
    }
    return head;
}

int get_length(ListNode *head)
{
    ListNode *p;
    int length = 0;

    if (head == NULL) {
        return 0;
    }
    p = head->link;
    do {
        length++;
        p = p->link;
    } while (p != head->link);
    return length;
}

void print_list(ListNode *head)
{
    ListNode *p;

    if (head == NULL) {
        printf("EMPTY\n");
        return;
    }
    p = head->link;
    do {
        printf("%d->", p->data);
        p = p->link;
    } while (p != head->link);
    printf("\n");
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

    head = insert_last(head, 20);
    head = insert_last(head, 30);
    head = insert_last(head, 40);
    head = insert_first(head, 10);

    print_list(head);
    printf("length = %d\n", get_length(head));

    free_list(head);
    return 0;
}
