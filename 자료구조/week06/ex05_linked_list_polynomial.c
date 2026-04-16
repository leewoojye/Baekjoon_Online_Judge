#include <stdio.h>
#include <stdlib.h>

typedef struct ListNode {
    int coef;
    int expon;
    struct ListNode *link;
} ListNode;

typedef struct ListType {
    int size;
    ListNode *head;
    ListNode *tail;
} ListType;

void error(char *message)
{
    fprintf(stderr, "%s\n", message);
    exit(1);
}

ListType *create(void)
{
    ListType *plist = (ListType *)malloc(sizeof(ListType));

    if (plist == NULL) {
        error("Memory allocation error");
    }
    plist->size = 0;
    plist->head = plist->tail = NULL;
    return plist;
}

void insert_last(ListType *plist, int coef, int expon)
{
    ListNode *temp = (ListNode *)malloc(sizeof(ListNode));

    if (temp == NULL) {
        error("Memory allocation error");
    }
    temp->coef = coef;
    temp->expon = expon;
    temp->link = NULL;

    if (plist->tail == NULL) {
        plist->head = plist->tail = temp;
    } else {
        plist->tail->link = temp;
        plist->tail = temp;
    }
    plist->size++;
}

void poly_add(ListType *plist1, ListType *plist2, ListType *plist3)
{
    ListNode *a = plist1->head;
    ListNode *b = plist2->head;
    int sum;

    while (a && b) {
        /* Same exponent: merge the two terms. */
        if (a->expon == b->expon) {
            sum = a->coef + b->coef;
            if (sum != 0) {
                insert_last(plist3, sum, a->expon);
            }
            a = a->link;
            b = b->link;
        /* a has the larger exponent, so copy a's term first. */
        } else if (a->expon > b->expon) {
            insert_last(plist3, a->coef, a->expon);
            a = a->link;
        /* b has the larger exponent, so copy b's term first. */
        } else {
            insert_last(plist3, b->coef, b->expon);
            b = b->link;
        }
    }

    for (; a != NULL; a = a->link) {
        insert_last(plist3, a->coef, a->expon);
    }
    for (; b != NULL; b = b->link) {
        insert_last(plist3, b->coef, b->expon);
    }
}

void poly_print(ListType *plist)
{
    ListNode *p = plist->head;

    printf("polynomial = ");
    for (; p != NULL; p = p->link) {
        printf("%dx^%d", p->coef, p->expon);
        if (p->link != NULL) {
            printf(" + ");
        }
    }
    printf("\n");
}

void destroy(ListType *plist)
{
    ListNode *p = plist->head;

    while (p != NULL) {
        ListNode *next = p->link;

        free(p);
        p = next;
    }
    free(plist);
}

int main(void)
{
    ListType *list1;
    ListType *list2;
    ListType *list3;

    list1 = create();
    list2 = create();
    list3 = create();

    insert_last(list1, 3, 12);
    insert_last(list1, 2, 8);
    insert_last(list1, 1, 0);

    insert_last(list2, 8, 12);
    insert_last(list2, -3, 10);
    insert_last(list2, 10, 6);

    poly_print(list1);
    poly_print(list2);

    poly_add(list1, list2, list3);
    poly_print(list3);

    destroy(list1);
    destroy(list2);
    destroy(list3);
    return 0;
}
