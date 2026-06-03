#include <stdio.h>
#include <stdlib.h>

#define INITIAL_CAPACITY 4

typedef struct {
    int key;
} element;

typedef struct {
    element *heap;
    int heap_size;
    int capacity;
    int min_capacity;
} HeapType;

static void error(const char *message)
{
    fprintf(stderr, "%s\n", message);
    exit(1);
}

static void init_heap(HeapType *h, int capacity)
{
    if (capacity < 1) {
        capacity = INITIAL_CAPACITY;
    }

    h->heap = (element *)malloc(sizeof(element) * (capacity + 1));
    if (h->heap == NULL) {
        error("allocation failed");
    }

    h->heap_size = 0;
    h->capacity = capacity;
    h->min_capacity = capacity;
}

static void destroy_heap(HeapType *h)
{
    free(h->heap);
    h->heap = NULL;
    h->heap_size = 0;
    h->capacity = 0;
    h->min_capacity = 0;
}

static void resize_heap(HeapType *h, int new_capacity)
{
    element *new_heap;

    if (new_capacity < h->min_capacity) {
        new_capacity = h->min_capacity;
    }
    if (new_capacity < h->heap_size) {
        new_capacity = h->heap_size;
    }

    new_heap = (element *)realloc(h->heap, sizeof(element) * (new_capacity + 1));
    if (new_heap == NULL) {
        error("reallocation failed");
    }

    h->heap = new_heap;
    h->capacity = new_capacity;
}

static void ensure_insert_capacity(HeapType *h)
{
    if (h->heap_size >= h->capacity) {
        resize_heap(h, h->capacity * 2);
    }
}

static void shrink_if_needed(HeapType *h)
{
    if (h->capacity > h->min_capacity && h->heap_size <= h->capacity / 4) {
        resize_heap(h, h->capacity / 2);
    }
}

static int is_empty(const HeapType *h)
{
    return h->heap_size == 0;
}

static void insert_max_heap(HeapType *h, element item)
{
    int i;

    ensure_insert_capacity(h);
    i = ++h->heap_size;

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

    if (is_empty(h)) {
        error("heap is empty");
    }

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

    shrink_if_needed(h);
    return item;
}

static void print_heap(const HeapType *h)
{
    printf("size=%d capacity=%d heap=", h->heap_size, h->capacity);
    for (int i = 1; i <= h->heap_size; i++) {
        printf("%d ", h->heap[i].key);
    }
    printf("\n");
}

int main(void)
{
    int values[] = { 23, 56, 11, 9, 40, 99, 27, 34, 72, 18 };
    int count = sizeof(values) / sizeof(values[0]);
    HeapType heap;

    init_heap(&heap, INITIAL_CAPACITY);

    printf("insert phase\n");
    for (int i = 0; i < count; i++) {
        element item = { values[i] };
        insert_max_heap(&heap, item);
        print_heap(&heap);
    }

    printf("\ndelete phase\n");
    while (!is_empty(&heap)) {
        element item = delete_max_heap(&heap);
        printf("delete %d -> ", item.key);
        print_heap(&heap);
    }

    destroy_heap(&heap);
    return 0;
}
