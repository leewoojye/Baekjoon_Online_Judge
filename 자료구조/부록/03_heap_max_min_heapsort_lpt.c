#include <stdio.h>
#include <stdlib.h>

#define EMPTY_MARK -999999

typedef struct {
    int key;
} MaxElement;

typedef struct {
    MaxElement *heap;
    int heap_size;
    int capacity;
} MaxHeapType;

typedef struct {
    int id;
    int avail;
} MinElement;

typedef struct {
    MinElement *heap;
    int heap_size;
    int capacity;
} MinHeapType;

static void error(const char *message)
{
    fprintf(stderr, "%s\n", message);
    exit(1);
}

static void init_max_heap(MaxHeapType *h, int capacity)
{
    if (capacity < 1) {
        capacity = 1;
    }

    h->heap = (MaxElement *)malloc(sizeof(MaxElement) * (capacity + 1));
    if (h->heap == NULL) {
        error("allocation failed");
    }

    h->heap_size = 0;
    h->capacity = capacity;
}

static void destroy_max_heap(MaxHeapType *h)
{
    free(h->heap);
    h->heap = NULL;
    h->heap_size = 0;
    h->capacity = 0;
}

static void resize_max_heap(MaxHeapType *h)
{
    int new_capacity = h->capacity * 2;
    MaxElement *new_heap = (MaxElement *)realloc(h->heap, sizeof(MaxElement) * (new_capacity + 1));

    if (new_heap == NULL) {
        error("reallocation failed");
    }

    h->heap = new_heap;
    h->capacity = new_capacity;
}

static void insert_max_heap(MaxHeapType *h, MaxElement item)
{
    int i;

    if (h->heap_size >= h->capacity) {
        resize_max_heap(h);
    }

    i = ++h->heap_size;
    while (i != 1 && item.key > h->heap[i / 2].key) {
        h->heap[i] = h->heap[i / 2];
        i /= 2;
    }
    h->heap[i] = item;
}

static MaxElement delete_max_heap(MaxHeapType *h)
{
    int parent;
    int child;
    MaxElement item;
    MaxElement temp;

    if (h->heap_size == 0) {
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
    return item;
}

static void print_max_heap(MaxHeapType *h)
{
    printf("Heap   : ");
    for (int i = 1; i <= h->heap_size; i++) {
        printf("%d ", h->heap[i].key);
    }
    printf("\n");
}

static void print_sorted(int sorted[], int n)
{
    printf("Sorted : ");
    for (int i = 0; i < n; i++) {
        if (sorted[i] == EMPTY_MARK) {
            printf("_ ");
        } else {
            printf("%d ", sorted[i]);
        }
    }
    printf("\n\n");
}

static void heap_sort_trace(int input[], int n)
{
    MaxHeapType h;
    int *sorted = (int *)malloc(sizeof(int) * n);

    if (sorted == NULL) {
        error("allocation failed");
    }

    init_max_heap(&h, 1);
    for (int i = 0; i < n; i++) {
        sorted[i] = EMPTY_MARK;
    }

    printf("=== Insertion Phase ===\n");
    for (int i = 0; i < n; i++) {
        MaxElement item = { input[i] };
        insert_max_heap(&h, item);
        print_max_heap(&h);
        print_sorted(sorted, n);
    }

    printf("=== Deletion Phase ===\n");
    for (int i = n - 1; i >= 0; i--) {
        sorted[i] = delete_max_heap(&h).key;
        print_max_heap(&h);
        print_sorted(sorted, n);
    }

    free(sorted);
    destroy_max_heap(&h);
}

static void heap_sort_desc(int input[], int output[], int n)
{
    MaxHeapType h;

    init_max_heap(&h, 1);

    for (int i = 0; i < n; i++) {
        MaxElement item = { input[i] };
        insert_max_heap(&h, item);
    }
    for (int i = 0; i < n; i++) {
        output[i] = delete_max_heap(&h).key;
    }

    destroy_max_heap(&h);
}

static int less_machine(MinElement a, MinElement b)
{
    if (a.avail != b.avail) {
        return a.avail < b.avail;
    }
    return a.id < b.id;
}

static void init_min_heap(MinHeapType *h, int capacity)
{
    if (capacity < 1) {
        capacity = 1;
    }

    h->heap = (MinElement *)malloc(sizeof(MinElement) * (capacity + 1));
    if (h->heap == NULL) {
        error("allocation failed");
    }

    h->heap_size = 0;
    h->capacity = capacity;
}

static void destroy_min_heap(MinHeapType *h)
{
    free(h->heap);
    h->heap = NULL;
    h->heap_size = 0;
    h->capacity = 0;
}

static void resize_min_heap(MinHeapType *h)
{
    int new_capacity = h->capacity * 2;
    MinElement *new_heap = (MinElement *)realloc(h->heap, sizeof(MinElement) * (new_capacity + 1));

    if (new_heap == NULL) {
        error("reallocation failed");
    }

    h->heap = new_heap;
    h->capacity = new_capacity;
}

static void insert_min_heap(MinHeapType *h, MinElement item)
{
    int i;

    if (h->heap_size >= h->capacity) {
        resize_min_heap(h);
    }

    i = ++h->heap_size;
    while (i != 1 && less_machine(item, h->heap[i / 2])) {
        h->heap[i] = h->heap[i / 2];
        i /= 2;
    }
    h->heap[i] = item;
}

static MinElement delete_min_heap(MinHeapType *h)
{
    int parent;
    int child;
    MinElement item;
    MinElement temp;

    if (h->heap_size == 0) {
        error("heap is empty");
    }

    item = h->heap[1];
    temp = h->heap[h->heap_size--];
    parent = 1;
    child = 2;

    while (child <= h->heap_size) {
        if (child < h->heap_size && less_machine(h->heap[child + 1], h->heap[child])) {
            child++;
        }
        if (!less_machine(h->heap[child], temp)) {
            break;
        }
        h->heap[parent] = h->heap[child];
        parent = child;
        child *= 2;
    }
    h->heap[parent] = temp;
    return item;
}

static void schedule_lpt(int jobs[], int job_count, int machine_count)
{
    int *sorted_jobs = (int *)malloc(sizeof(int) * job_count);
    int *final_time = (int *)calloc(machine_count + 1, sizeof(int));
    MinHeapType h;
    int makespan = 0;

    if (sorted_jobs == NULL || final_time == NULL) {
        error("allocation failed");
    }

    heap_sort_desc(jobs, sorted_jobs, job_count);

    printf("Original Jobs: ");
    for (int i = 0; i < job_count; i++) {
        printf("%d ", jobs[i]);
    }
    printf("\nSorted Jobs  : ");
    for (int i = 0; i < job_count; i++) {
        printf("%d ", sorted_jobs[i]);
    }
    printf("\n\n");

    init_min_heap(&h, machine_count);
    for (int i = 0; i < machine_count; i++) {
        MinElement machine = { i + 1, 0 };
        insert_min_heap(&h, machine);
    }

    for (int i = 0; i < job_count; i++) {
        MinElement machine = delete_min_heap(&h);
        printf("job %d: time %d to %d -> machine %d\n",
               i, machine.avail, machine.avail + sorted_jobs[i] - 1, machine.id);
        machine.avail += sorted_jobs[i];
        final_time[machine.id] = machine.avail;
        insert_min_heap(&h, machine);
    }

    printf("\nFinal Machine Time\n");
    for (int i = 1; i <= machine_count; i++) {
        printf("machine %d: %d\n", i, final_time[i]);
        if (final_time[i] > makespan) {
            makespan = final_time[i];
        }
    }
    printf("makespan: %d\n", makespan);

    free(sorted_jobs);
    free(final_time);
    destroy_min_heap(&h);
}

int main(void)
{
    int input[] = { 23, 56, 11, 9, 40, 99, 27, 34 };
    int jobs[] = { 2, 14, 4, 16, 6, 5, 3 };
    int n = (int)(sizeof(input) / sizeof(input[0]));
    int job_count = (int)(sizeof(jobs) / sizeof(jobs[0]));

    heap_sort_trace(input, n);

    printf("\n================ LPT Test ================\n");
    schedule_lpt(jobs, job_count, 3);

    return 0;
}
