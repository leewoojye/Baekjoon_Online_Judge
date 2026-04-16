/*
Quiz
- 단순 연결 리스트에서 첫번째 노드를 가리키고 있는 포인터를 __ 라고 한다.
- 노드는 데이터 필드와 __ 필드로 이루어져 있다.
- 배열에 비하여 연결 리스트는 어떤 장점을 가지는가?
- 단순 연결리스트에서 하나의 노드를 삭제하려면 어떤 노드를 가리키는 포인터 변수가 필요한가?
- 단순 연결 리스트에 존재하는 노드의 수를 계산하는 함수 get_length()를 작성하여라.

예시 답안
- 첫 번째 노드를 가리키는 포인터: head pointer
- 노드의 두 필드: data field, link field
- 장점: 크기를 동적으로 변경하기 쉽고, 중간 삽입/삭제 시 원소 이동이 필요 없다.
- 삭제에 필요한 포인터: 삭제할 노드의 이전 노드를 가리키는 포인터
- 아래 코드는 get_length() 구현 예시이다.
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct ListNode {
    int data;
    struct ListNode *link;
} ListNode;

ListNode *insert_first(ListNode *head, int value)
{
    ListNode *node = (ListNode *)malloc(sizeof(ListNode));

    node->data = value;
    node->link = head;
    return node;
}

int get_length(ListNode *head)
{
    int count = 0;

    for (ListNode *p = head; p != NULL; p = p->link) {
        count++;
    }
    return count;
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
    head = insert_first(head, 20);
    head = insert_first(head, 30);

    printf("length = %d\n", get_length(head));
    free_list(head);
    return 0;
}
