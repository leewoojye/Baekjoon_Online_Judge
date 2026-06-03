#include <stdio.h>

#define MAX_ELEMENT 200
#define JOBS 7
#define MACHINES 3

typedef struct {
    int id;
    int avail;
} Machine;

typedef struct {
    int heap[MAX_ELEMENT];
    int heap_size;
} JobHeap;

typedef struct {
    Machine heap[MAX_ELEMENT];
    int heap_size;
} MachineHeap;

static void init_job_heap(JobHeap *h)
{
    h->heap_size = 0;
}

static void init_machine_heap(MachineHeap *h)
{
    h->heap_size = 0;
}

static void insert_max_heap(JobHeap *h, int item)
{
    int i = ++h->heap_size;

    while (i != 1 && item > h->heap[i / 2]) {
        h->heap[i] = h->heap[i / 2];
        i /= 2;
    }
    h->heap[i] = item;
}

static int delete_max_heap(JobHeap *h)
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

static int less_machine(Machine a, Machine b)
{
    if (a.avail != b.avail) {
        return a.avail < b.avail;
    }
    return a.id < b.id;
}

static void insert_min_heap(MachineHeap *h, Machine item)
{
    int i = ++h->heap_size;

    while (i != 1 && less_machine(item, h->heap[i / 2])) {
        h->heap[i] = h->heap[i / 2];
        i /= 2;
    }
    h->heap[i] = item;
}

static Machine delete_min_heap(MachineHeap *h)
{
    int parent = 1;
    int child = 2;
    Machine item = h->heap[1];
    Machine temp = h->heap[h->heap_size--];

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

static void heap_sort_jobs_desc(const int jobs[], int sorted[], int n)
{
    JobHeap h;

    init_job_heap(&h);

    for (int i = 0; i < n; i++) {
        insert_max_heap(&h, jobs[i]);
    }
    for (int i = 0; i < n; i++) {
        sorted[i] = delete_max_heap(&h);
    }
}

static void print_array(const char *name, const int list[], int n)
{
    printf("%s: ", name);
    for (int i = 0; i < n; i++) {
        printf("%d ", list[i]);
    }
    printf("\n");
}

static void lpt_schedule(const int jobs[], int n)
{
    MachineHeap h;
    Machine m;

    init_machine_heap(&h);

    for (int i = 0; i < MACHINES; i++) {
        m.id = i + 1;
        m.avail = 0;
        insert_min_heap(&h, m);
    }

    for (int i = 0; i < n; i++) {
        m = delete_min_heap(&h);
        printf("JOB %d: time %d to %d on machine %d\n", i, m.avail, m.avail + jobs[i] - 1, m.id);
        m.avail += jobs[i];
        insert_min_heap(&h, m);
    }
}

int main(void)
{
    int jobs[JOBS] = { 2, 8, 1, 6, 5, 3, 7 };
    int sorted[JOBS];

    heap_sort_jobs_desc(jobs, sorted, JOBS);

    print_array("Unsorted jobs", jobs, JOBS);
    print_array("Sorted jobs", sorted, JOBS);
    lpt_schedule(sorted, JOBS);
    return 0;
}
