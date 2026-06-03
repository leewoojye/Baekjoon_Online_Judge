#include <stdio.h>
#include <stdlib.h>

#define MAX_ELEMENT 200
#define JOBS 7
#define MACHINES 3

typedef struct {
    int id;
    int avail;
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

static int less_machine(element a, element b)
{
    if (a.avail != b.avail) {
        return a.avail < b.avail;
    }
    return a.id < b.id;
}

static void insert_min_heap(HeapType *h, element item)
{
    int i = ++h->heap_size;

    while (i != 1 && less_machine(item, h->heap[i / 2])) {
        h->heap[i] = h->heap[i / 2];
        i /= 2;
    }
    h->heap[i] = item;
}

static element delete_min_heap(HeapType *h)
{
    int parent = 1;
    int child = 2;
    element item = h->heap[1];
    element temp = h->heap[h->heap_size--];

    while (child <= h->heap_size) {
        if (child < h->heap_size && less_machine(h->heap[child + 1], h->heap[child])) {
            child++;
        }
        if (less_machine(temp, h->heap[child]) || (temp.avail == h->heap[child].avail && temp.id == h->heap[child].id)) {
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
    int jobs[JOBS] = { 8, 7, 6, 5, 3, 2, 1 };
    element m = { 0, 0 };
    HeapType *h = create();

    if (h == NULL) {
        fprintf(stderr, "allocation failed\n");
        return 1;
    }
    init(h);

    for (int i = 0; i < MACHINES; i++) {
        m.id = i + 1;
        m.avail = 0;
        insert_min_heap(h, m);
    }

    for (int i = 0; i < JOBS; i++) {
        m = delete_min_heap(h);
        printf("JOB %d: time %d to %d on machine %d\n", i, m.avail, m.avail + jobs[i] - 1, m.id);
        m.avail += jobs[i];
        insert_min_heap(h, m);
    }

    free(h);
    return 0;
}
