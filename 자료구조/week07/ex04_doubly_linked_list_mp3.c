#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char element[100];

typedef struct DListNode {
    element data;
    struct DListNode *llink;
    struct DListNode *rlink;
} DListNode;

DListNode *current = NULL;

void init(DListNode *phead)
{
    phead->llink = phead;
    phead->rlink = phead;
}

void dinsert(DListNode *before, const char *data)
{
    DListNode *newnode = (DListNode *)malloc(sizeof(DListNode));

    if (newnode == NULL) {
        fprintf(stderr, "Memory allocation error\n");
        exit(1);
    }
    strcpy(newnode->data, data);
    newnode->llink = before;
    newnode->rlink = before->rlink;
    before->rlink->llink = newnode;
    before->rlink = newnode;
}

void print_dlist(DListNode *phead)
{
    DListNode *p;

    for (p = phead->rlink; p != phead; p = p->rlink) {
        if (p == current) {
            printf("<-| #%s# |-> ", p->data);
        } else {
            printf("<-| %s |-> ", p->data);
        }
    }
    printf("\n");
}

void destroy(DListNode *head)
{
    DListNode *p = head->rlink;

    while (p != head) {
        DListNode *next = p->rlink;

        free(p);
        p = next;
    }
    free(head);
}

void consume_line(void)
{
    int ch;

    while ((ch = getchar()) != '\n' && ch != EOF) {
    }
}

int main(void)
{
    char ch;
    DListNode *head = (DListNode *)malloc(sizeof(DListNode));

    if (head == NULL) {
        fprintf(stderr, "Memory allocation error\n");
        return 1;
    }
    init(head);
    dinsert(head, "Mamamia");
    dinsert(head, "Dancing Queen");
    dinsert(head, "Fernando");

    current = head->rlink;
    print_dlist(head);

    do {
        printf("\n명령어를 입력하시오(<, >, q): ");
        ch = getchar();

        if (ch == '<') {
            current = current->llink;
            if (current == head) {
                current = current->llink;
            }
        } else if (ch == '>') {
            current = current->rlink;
            if (current == head) {
                current = current->rlink;
            }
        }

        if (ch == '<' || ch == '>' || ch == 'q') {
            print_dlist(head);
        } else if (ch != '\n' && ch != EOF) {
            printf("지원하지 않는 명령입니다.\n");
            print_dlist(head);
        }

        if (ch != EOF) {
            consume_line();
        }
    } while (ch != 'q' && ch != EOF);

    destroy(head);
    return 0;
}
