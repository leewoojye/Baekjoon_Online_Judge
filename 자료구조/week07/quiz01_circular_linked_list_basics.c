/*
Quiz
1. 다중 연결리스트에 비하여 원형 연결 리스트의 장점은
2. 위의 코드를 실행하고 결과를 확인해 보아라
3. 원형 연결 리스트에 존재하는 노드의 수를 계산하는 함수
   get_length()를 작성하여라

예시 답안
1. 마지막 노드에서 다시 첫 번째 노드로 바로 이동할 수 있으므로
   어느 노드에서 시작해도 전체 순회가 가능하다.
   또한 tail 포인터 하나만 유지해도 맨 앞/맨 뒤 삽입을 단순하게 처리할 수 있다.
2. 아래 예제는 교안의 코드 흐름대로 10->20->30->40-> 를 출력한다.
3. get_length()는 시작 노드를 기준으로 한 바퀴 순회하면서 개수를 세면 된다.
*/

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
    int count = 0;

    if (head == NULL) {
        return 0;
    }
    p = head->link;
    do {
        count++;
        p = p->link;
    } while (p != head->link);
    return count;
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

    printf("장점: tail 하나로 앞/뒤 삽입을 쉽게 처리하고, 마지막 노드에서 첫 노드로 바로 이동할 수 있습니다.\n");
    printf("리스트 출력: ");
    print_list(head);
    printf("노드 수: %d\n", get_length(head));

    free_list(head);
    return 0;
}
