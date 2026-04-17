#include <stdio.h>
#include <stdlib.h>

typedef int element;

typedef struct Node {
    element data;
    struct Node *link;
} Node;

Node *insert_first(Node *head, int value)
{
    Node *p = (Node *)malloc(sizeof(Node));

    p->data = value;
    p->link = head;
    head = p;
    return head;
}

Node *insert(Node *head, Node *pre, element value)
{
    Node *p = (Node *)malloc(sizeof(Node));

    p->data = value;
    p->link = pre->link;
    pre->link = p;
    return head;
}

Node *delete_first(Node *head)
{
    Node *removed;

    if (head == NULL) {
        return NULL;
    }
    removed = head;
    head = removed->link;
    free(removed);
    return head;
}

Node *delete_node(Node *head, Node *pre)
{
    Node *removed;

    if (pre == NULL || pre->link == NULL) {
        return head;
    }
    removed = pre->link;
    pre->link = removed->link;
    free(removed);
    return head;
}

void print_list(Node *head)
{
    for (Node *p = head; p != NULL; p = p->link) {
        printf("%d->", p->data);
    }
    printf("NULL\n");
}

void free_list(Node *head)
{
    while (head != NULL) {
        Node *next = head->link;

        free(head);
        head = next;
    }
}

Node* set_union(Node* A, Node* B) {
  Node* pos_A = A;
  Node* pos_B = B;
  while(pos_A->link != NULL) {
    if(pos_A->data == pos_B->data) {
      pos_A = pos_A->link;
      pos_B = pos_B->link;
      continue;
    }
    if(pos_A->data < pos_B->data) {
      insert(A, pos_A, pos_B->data);
      continue;
    }
  }
  while(pos_B != NULL) { // 남은 B 요소 삽입
    insert(A, pos_A, pos_B->data);
    pos_A = pos_A->link;
    pos_B = pos_B->link;
  }
  return A;
}

Node* set_difference(Node* A, Node* B) {
  Node* pos_A = A;
  Node* pos_B = B;
  while(pos_A->link != NULL) {
    if(pos_A->data == pos_B->data) {
      pos_A = pos_A->link;
      pos_B = pos_B->link;
      continue;
    }
    if(pos_A->data < pos_B->data) {
      insert(A, pos_A, pos_B->data);
      continue;
    }
  }
  return A;
}

int main(void)
{
    // Node *A = NULL;
    // Node *p;
    // Node *head = NULL;
    // Node *head_A = NULL;
    // Node *head_B = NULL;

    // A = (ListNode *)malloc(sizeof(ListNode));
    // A->data = 10;
    // A->link = NULL;

    // p = (ListNode *)malloc(sizeof(ListNode));
    // p->data = 20;
    // p->link = NULL;
    // A->link = p;
    // print_list(A);
    // free_list(A);

    // head = insert_first(head, i);
    // print_list(head);

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
    // free_list(head);

    int arrA[] = { 1, 3, 5, 7, 9 };
    int arrB[] = { 3, 4, 7, 10 };
    int sizeA = 5;
    int sizeB = 4;
    Node* A = NULL; // A의 head 포인터
    Node* B = NULL;
    for (int i = 0; i < sizeA; i++) insert_last(&A, arrA[i]);
    for (int i = 0; i < sizeB; i++) insert_last(&B, arrB[i]);
    Node* C = set_union(A, B);
    // Node* D = set_difference(A, B);
    // print_list("A", A); 
    // free_list(A);
    // print_list("B", B); 
    // free_list(B);
    print_list(C); 
    free_list(C);
    // print_list("D", D); 
    // free_list(D);

    return 0;
}
