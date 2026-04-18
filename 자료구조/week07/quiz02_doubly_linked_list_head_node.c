/*
Quiz
1. 이중 연결 리스트에서 헤드 노드를 사용하는 이유는 무엇인가
2. 헤드 노드만 있는 이중 연결 리스트에 노드를 삽입하기 위하여
   dinsert()를 호출하였다면 포인터들은 어떻게 변경되는가? 그림으로
   그려서 설명하여라

예시 답안
1. 헤드 노드를 두면 빈 리스트와 일반 노드 처리를 같은 방식으로 할 수 있어
   삽입/삭제 코드가 단순해진다.
2. head만 있는 상태에서 dinsert(head, x)를 호출하면
   newnode->llink = head
   newnode->rlink = head
   head->llink = newnode
   head->rlink = newnode
   가 되어 head <-> newnode <-> head 구조가 된다.
*/

#include <stdio.h>
#include <stdlib.h>

typedef int element;

typedef struct DListNode {
    element data;
    struct DListNode *llink;
    struct DListNode *rlink;
} DListNode;

void init(DListNode *head)
{
    head->llink = head;
    head->rlink = head;
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

void print_links(DListNode *head)
{
    printf("head      : self=%p llink=%p rlink=%p\n",
           (void *)head, (void *)head->llink, (void *)head->rlink);
    if (head->rlink != head) {
        DListNode *node = head->rlink;

        printf("new node   : self=%p data=%d llink=%p rlink=%p\n",
               (void *)node, node->data, (void *)node->llink, (void *)node->rlink);
    }
}

int main(void)
{
    DListNode *head = (DListNode *)malloc(sizeof(DListNode));

    if (head == NULL) {
        fprintf(stderr, "Memory allocation error\n");
        return 1;
    }
    init(head);

    printf("헤드 노드 사용 이유: 빈 리스트와 일반 리스트를 같은 규칙으로 다뤄서 경계 조건을 줄일 수 있습니다.\n");
    printf("\n삽입 전\n");
    print_links(head);

    dinsert(head, 100);

    printf("\n삽입 후\n");
    print_links(head);
    printf("\n구조: head <-> %d <-> head\n", head->rlink->data);

    free(head->rlink);
    free(head);
    return 0;
}
