#include <stdio.h>
#include <stdlib.h>

#define MAX_ELEMENT 200

typedef struct {
    int key;
} element;

typedef struct {
    element heap[MAX_ELEMENT];
    int heap_size;
} HeapType;

static HeapType *create(void)
{
    return (HeapType *)malloc(sizeof(HeapType));
}

static void init(HeapType *h)
{
    h->heap_size = 0;
}

static void insert_max_heap(HeapType *h, element item)
{
    int i = ++h->heap_size;

    while (i != 1 && item.key > h->heap[i / 2].key) {
        h->heap[i] = h->heap[i / 2];
        i /= 2;
    }
    h->heap[i] = item;
}

static element delete_max_heap(HeapType *h)
{
    int parent;
    int child;
    element item;
    element temp;

    item = h->heap[1];
    temp = h->heap[h->heap_size--];
    parent = 1;
    child = 2;

    while (child <= h->heap_size) {
        if (child < h->heap_size && h->heap[child].key < h->heap[child + 1].key) {
            child++;
        }
        if (temp.key >= h->heap[child].key) {
            break;
        }
        h->heap[parent] = h->heap[child];
        parent = child;
        child *= 2;
    }
    h->heap[parent] = temp;
    return item;
}

int main(void)
{
    element e1 = { 10 };
    element e2 = { 5 };
    element e3 = { 30 };
    element e4;
    element e5;
    element e6;
    HeapType *heap = create();

    if (heap == NULL) {
        fprintf(stderr, "allocation failed\n");
        return 1;
    }
    init(heap);

    insert_max_heap(heap, e1);
    insert_max_heap(heap, e2);
    insert_max_heap(heap, e3);

    e4 = delete_max_heap(heap);
    printf("< %d > ", e4.key);
    e5 = delete_max_heap(heap);
    printf("< %d > ", e5.key);
    e6 = delete_max_heap(heap);
    printf("< %d >\n", e6.key);

    free(heap);
    return 0;
}
