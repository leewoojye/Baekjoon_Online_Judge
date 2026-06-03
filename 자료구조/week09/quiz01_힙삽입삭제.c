#include <stdio.h>

#define MAX_HEAP_SIZE 32

typedef struct {
    int heap[MAX_HEAP_SIZE];
    int heap_size;
} HeapType;

static void print_heap(const char *label, const HeapType *h)
{
    printf("%s", label);
    for (int i = 1; i <= h->heap_size; i++) {
        printf("%d ", h->heap[i]);
    }
    printf("\n");
}

static void insert_max_heap_trace(HeapType *h, int item)
{
    int i = ++h->heap_size;

    printf("insert %d at index %d\n", item, i);
    while (i != 1 && item > h->heap[i / 2]) {
        printf("  move parent %d from index %d to index %d\n", h->heap[i / 2], i / 2, i);
        h->heap[i] = h->heap[i / 2];
        i /= 2;
    }
    h->heap[i] = item;
    print_heap("after insert: ", h);
}

static int delete_max_heap_trace(HeapType *h)
{
    int parent = 1;
    int child = 2;
    int item = h->heap[1];
    int temp = h->heap[h->heap_size--];

    printf("delete root %d, move last item %d down\n", item, temp);
    while (child <= h->heap_size) {
        if (child < h->heap_size && h->heap[child] < h->heap[child + 1]) {
            child++;
        }
        if (temp >= h->heap[child]) {
            break;
        }
        printf("  move child %d from index %d to index %d\n", h->heap[child], child, parent);
        h->heap[parent] = h->heap[child];
        parent = child;
        child *= 2;
    }
    h->heap[parent] = temp;
    print_heap("after delete: ", h);
    return item;
}

int main(void)
{
    HeapType original = {
        { 0, 12, 10, 8, 4, 6, 2, 5, 3 },
        8
    };
    HeapType inserted = original;
    HeapType deleted = original;

    print_heap("original    : ", &original);

    printf("\nquiz 1 answer\n");
    insert_max_heap_trace(&inserted, 11);

    printf("\nquiz 2 answer\n");
    (void)delete_max_heap_trace(&deleted);
    return 0;
}
