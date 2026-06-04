#include <stdio.h>

#define MAX_ELEMENT 200
#define JOBS 7
#define MACHINES 3

typedef struct {
    int id;
    int time;
} Job;

typedef struct {
    Job heap[MAX_ELEMENT];
    int heap_size;
} JobHeap;

typedef struct {
    int id;
    int current_job;
    int job_time;
    int remaining_time;
    int total_work;
} Machine;

static void init_job_heap(JobHeap *h)
{
    h->heap_size = 0;
}

static int greater_job(Job a, Job b)
{
    if (a.time != b.time) {
        return a.time > b.time;
    }
    return a.id < b.id;
}

static void insert_max_heap(JobHeap *h, Job item)
{
    int i = ++h->heap_size;

    while (i != 1 && greater_job(item, h->heap[i / 2])) {
        h->heap[i] = h->heap[i / 2];
        i /= 2;
    }
    h->heap[i] = item;
}

static Job delete_max_heap(JobHeap *h)
{
    int parent = 1;
    int child = 2;
    Job item = h->heap[1];
    Job temp = h->heap[h->heap_size--];

    while (child <= h->heap_size) {
        if (child < h->heap_size && greater_job(h->heap[child + 1], h->heap[child])) {
            child++;
        }
        if (!greater_job(h->heap[child], temp)) {
            break;
        }
        h->heap[parent] = h->heap[child];
        parent = child;
        child *= 2;
    }
    h->heap[parent] = temp;
    return item;
}

static void init_machines(Machine machines[])
{
    for (int i = 0; i < MACHINES; i++) {
        machines[i].id = i + 1;
        machines[i].current_job = -1;
        machines[i].job_time = 0;
        machines[i].remaining_time = 0;
        machines[i].total_work = 0;
    }
}

static int is_machine_busy(Machine *m)
{
    return m->remaining_time > 0;
}

static int has_busy_machine(Machine machines[])
{
    for (int i = 0; i < MACHINES; i++) {
        if (is_machine_busy(&machines[i])) {
            return 1;
        }
    }
    return 0;
}

static void assign_jobs(JobHeap *h, Machine machines[], int clock)
{
    Job job;

    for (int i = 0; i < MACHINES; i++) {
        if (!is_machine_busy(&machines[i]) && h->heap_size > 0) {
            job = delete_max_heap(h);
            machines[i].current_job = job.id;
            machines[i].job_time = job.time;
            machines[i].remaining_time = job.time;
            machines[i].total_work += job.time;
            printf(
                "JOB %d starts at time %d on machine %d. Processing time = %d\n",
                job.id,
                clock,
                machines[i].id,
                job.time
            );
        }
    }
}

static void work_one_minute(Machine machines[], int clock)
{
    for (int i = 0; i < MACHINES; i++) {
        if (is_machine_busy(&machines[i])) {
            printf(
                "Machine %d works on JOB %d. Remaining time = %d\n",
                machines[i].id,
                machines[i].current_job,
                machines[i].remaining_time
            );
            machines[i].remaining_time--;

            if (machines[i].remaining_time == 0) {
                printf(
                    "JOB %d finishes at time %d on machine %d.\n",
                    machines[i].current_job,
                    clock + 1,
                    machines[i].id
                );
                machines[i].current_job = -1;
                machines[i].job_time = 0;
            }
        } else {
            printf("Machine %d is idle.\n", machines[i].id);
        }
    }
}

static void print_summary(Machine machines[], int finish_time)
{
    printf("\nFinish time = %d\n", finish_time);
    for (int i = 0; i < MACHINES; i++) {
        printf("Machine %d total work = %d\n", machines[i].id, machines[i].total_work);
    }
}

static void lpt_time_simulation(const int jobs[], int n)
{
    JobHeap h;
    Machine machines[MACHINES];
    int clock = 0;

    init_job_heap(&h);
    init_machines(machines);

    for (int i = 0; i < n; i++) {
        Job job;

        job.id = i;
        job.time = jobs[i];
        insert_max_heap(&h, job);
    }

    while (h.heap_size > 0 || has_busy_machine(machines)) {
        printf("Current time = %d\n", clock);
        assign_jobs(&h, machines, clock);
        work_one_minute(machines, clock);
        printf("\n");
        clock++;
    }

    print_summary(machines, clock);
}

int main(void)
{
    int jobs[JOBS] = { 2, 8, 1, 6, 5, 3, 7 };

    lpt_time_simulation(jobs, JOBS);
    return 0;
}
