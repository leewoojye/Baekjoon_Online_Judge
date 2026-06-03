#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *link;
} Node;

static void error(const char *message)
{
    fprintf(stderr, "%s\n", message);
    exit(1);
}

static Node *make_node(int data)
{
    Node *node = (Node *)malloc(sizeof(Node));

    if (node == NULL) {
        error("allocation failed");
    }
    node->data = data;
    node->link = NULL;
    return node;
}

static void insert_last(Node **head, int data)
{
    Node *node = make_node(data);

    if (*head == NULL) {
        *head = node;
    } else {
        Node *p = *head;

        while (p->link != NULL) {
            p = p->link;
        }
        p->link = node;
    }
}

static Node *set_union(Node *a, Node *b)
{
    Node *result = NULL;

    while (a != NULL && b != NULL) {
        if (a->data < b->data) {
            insert_last(&result, a->data);
            a = a->link;
        } else if (a->data > b->data) {
            insert_last(&result, b->data);
            b = b->link;
        } else {
            insert_last(&result, a->data);
            a = a->link;
            b = b->link;
        }
    }

    while (a != NULL) {
        insert_last(&result, a->data);
        a = a->link;
    }

    while (b != NULL) {
        insert_last(&result, b->data);
        b = b->link;
    }

    return result;
}

static Node *set_difference(Node *a, Node *b)
{
    Node *result = NULL;

    while (a != NULL && b != NULL) {
        if (a->data < b->data) {
            insert_last(&result, a->data);
            a = a->link;
        } else if (a->data > b->data) {
            b = b->link;
        } else {
            a = a->link;
            b = b->link;
        }
    }

    while (a != NULL) {
        insert_last(&result, a->data);
        a = a->link;
    }

    return result;
}

static void print_list(const char *name, Node *head)
{
    Node *p = head;

    printf("%s: ", name);
    while (p != NULL) {
        printf("%d", p->data);
        if (p->link != NULL) {
            printf(" -> ");
        }
        p = p->link;
    }
    printf("\n");
}

static void free_list(Node *head)
{
    while (head != NULL) {
        Node *removed = head;

        head = head->link;
        free(removed);
    }
}

int main(void)
{
    int arrA[] = { 1, 3, 5, 7, 9 };
    int arrB[] = { 3, 4, 7, 10 };
    int sizeA = (int)(sizeof(arrA) / sizeof(arrA[0]));
    int sizeB = (int)(sizeof(arrB) / sizeof(arrB[0]));
    Node *A = NULL;
    Node *B = NULL;
    Node *C;
    Node *D;

    for (int i = 0; i < sizeA; i++) {
        insert_last(&A, arrA[i]);
    }
    for (int i = 0; i < sizeB; i++) {
        insert_last(&B, arrB[i]);
    }

    C = set_union(A, B);
    D = set_difference(A, B);

    print_list("A", A);
    print_list("B", B);
    print_list("C", C);
    print_list("D", D);

    free_list(A);
    free_list(B);
    free_list(C);
    free_list(D);
    return 0;
}
