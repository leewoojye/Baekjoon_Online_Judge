#include <stdio.h>

#define MAX_HEAP_SIZE 100
#define SIZE 8

typedef struct {
    int heap[MAX_HEAP_SIZE];
    int heap_size;
} HeapType;

static void init_heap(HeapType *h)
{
    h->heap_size = 0;
}

static void print_state(const HeapType *h, const int sorted[], int n)
{
    printf("Heap   : ");
    for (int i = 1; i <= h->heap_size; i++) {
        printf("%d ", h->heap[i]);
    }
    printf("\n");

    printf("Sorted : ");
    for (int i = 0; i < n; i++) {
        if (sorted[i] == -1) {
            printf("_ ");
        } else {
            printf("%d ", sorted[i]);
        }
    }
    printf("\n\n");
}

static void insert_max_heap(HeapType *h, int item)
{
    int i = ++h->heap_size;

    while (i != 1 && item > h->heap[i / 2]) {
        h->heap[i] = h->heap[i / 2];
        i /= 2;
    }
    h->heap[i] = item;
}

static int delete_max_heap(HeapType *h)
{
    int parent = 1;
    int child = 2;
    int item = h->heap[1];
    int temp = h->heap[h->heap_size--];

    while (child <= h->heap_size) {
        if (child < h->heap_size && h->heap[child] < h->heap[child + 1]) {
            child++;
        }
        if (temp >= h->heap[child]) {
            break;
        }
        h->heap[parent] = h->heap[child];
        parent = child;
        child *= 2;
    }
    h->heap[parent] = temp;
    return item;
}

static void heap_sort_trace(const int input[], int sorted[], int n)
{
    HeapType h;

    init_heap(&h);
    for (int i = 0; i < n; i++) {
        sorted[i] = -1;
    }

    printf("=== Insertion Phase ===\n");
    for (int i = 0; i < n; i++) {
        insert_max_heap(&h, input[i]);
        print_state(&h, sorted, n);
    }

    printf("=== Deletion (Sorting) Phase ===\n");
    for (int i = n - 1; i >= 0; i--) {
        sorted[i] = delete_max_heap(&h);
        print_state(&h, sorted, n);
    }
}

int main(void)
{
    int input[SIZE] = { 23, 56, 11, 9, 40, 99, 27, 34 };
    int sorted[SIZE];

    heap_sort_trace(input, sorted, SIZE);

    printf("Result: ");
    for (int i = 0; i < SIZE; i++) {
        printf("%d ", sorted[i]);
    }
    printf("\n");
    return 0;
}
