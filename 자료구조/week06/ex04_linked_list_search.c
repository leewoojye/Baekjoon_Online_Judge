#include <stdio.h>
#include <stdlib.h>

typedef int element;

typedef struct ListNode {
    element data;
    struct ListNode *link;
} ListNode;

ListNode *insert_first(ListNode *head, element value)
{
    ListNode *p = (ListNode *)malloc(sizeof(ListNode));

    p->data = value;
    p->link = head;
    head = p;
    return head;
}

void print_list(ListNode *head)
{
    for (ListNode *p = head; p != NULL; p = p->link) {
        printf("%d->", p->data);
    }
    printf("NULL\n");
}

ListNode *search_list(ListNode *head, element x)
{
    ListNode *p = head;

    while (p != NULL) {
        if (p->data == x) {
            return p;
        }
        p = p->link;
    }
    return NULL;
}

void free_list(ListNode *head)
{
    while (head != NULL) {
        ListNode *next = head->link;

        free(head);
        head = next;
    }
}

int main(void)
{
    ListNode *head = NULL;

    head = insert_first(head, 10);
    print_list(head);
    head = insert_first(head, 20);
    print_list(head);
    head = insert_first(head, 30);
    print_list(head);

    if (search_list(head, 30) != NULL) {
        printf("Found 30 in the list.\n");
    } else {
        printf("Could not find 30 in the list.\n");
    }

    free_list(head);
    return 0;
}
