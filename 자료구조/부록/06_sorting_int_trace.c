#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 200
#define MAX_QUEUE_SIZE 200
#define BUCKETS 10
#define TRUE 1
#define FALSE 0
#define SWAP(a, b, t) ((t) = (a), (a) = (b), (b) = (t))

typedef struct {
    int data[MAX_QUEUE_SIZE];
    int front;
    int rear;
} QueueType;

static int sorted[MAX_SIZE];
static int trace_size;

// 오류 메시지를 출력하고 프로그램을 종료한다.
static void error(const char *message)
{
    fprintf(stderr, "%s\n", message);
    exit(1);
}

// 정수 배열의 모든 원소를 한 줄에 출력한다.
static void print_array(int list[], int n)
{
    for (int i = 0; i < n; i++) {
        printf("%d ", list[i]);
    }
    printf("\n");
}

// 원본 배열을 대상 배열로 복사한다.
static void copy_array(int dest[], int src[], int n)
{
    for (int i = 0; i < n; i++) {
        dest[i] = src[i];
    }
}

// 선택 정렬로 배열을 오름차순 정렬한다.
static void selection_sort(int list[], int n)
{
    int i;
    int j;
    int least;
    int temp;

    for (i = 0; i < n - 1; i++) {
        least = i;
        for (j = i + 1; j < n; j++) {
            if (list[j] < list[least]) {
                least = j;
            }
        }
        SWAP(list[i], list[least], temp);
    }
}

// 삽입 정렬로 배열을 오름차순 정렬한다.
static void insertion_sort(int list[], int n)
{
    int i;
    int j;
    int key;

    for (i = 1; i < n; i++) {
        key = list[i];
        for (j = i - 1; j >= 0 && list[j] > key; j--) {
            list[j + 1] = list[j];
        }
        list[j + 1] = key;
    }
}

// 버블 정렬로 배열을 오름차순 정렬한다.
static void bubble_sort(int list[], int n)
{
    int i;
    int j;
    int temp;

    for (i = n - 1; i > 0; i--) {
        for (j = 0; j < i; j++) {
            if (list[j] > list[j + 1]) {
                SWAP(list[j], list[j + 1], temp);
            }
        }
    }
}

// 지정한 gap 간격의 부분 배열을 삽입 정렬한다.
static void inc_insertion_sort(int list[], int first, int last, int gap)
{
    int i;
    int j;
    int key;

    for (i = first + gap; i <= last; i += gap) {
        key = list[i];
        for (j = i - gap; j >= first && key < list[j]; j -= gap) {
            list[j + gap] = list[j];
        }
        list[j + gap] = key;
    }
}

// 셸 정렬로 배열을 오름차순 정렬한다.
static void shell_sort(int list[], int n)
{
    int gap;

    for (gap = n / 2; gap > 0; gap /= 2) {
        if (gap % 2 == 0) {
            gap++;
        }
        for (int i = 0; i < gap; i++) {
            inc_insertion_sort(list, i, n - 1, gap);
        }
    }
}

// 병합 정렬에서 두 정렬 구간을 합친다.
static void merge(int list[], int left, int mid, int right, int trace)
{
    int i = left;
    int j = mid + 1;
    int k = left;
    int l;

    while (i <= mid && j <= right) {
        if (list[i] <= list[j]) {
            sorted[k++] = list[i++];
        } else {
            sorted[k++] = list[j++];
        }
    }

    if (i > mid) {
        for (l = j; l <= right; l++) {
            sorted[k++] = list[l];
        }
    } else {
        for (l = i; l <= mid; l++) {
            sorted[k++] = list[l];
        }
    }

    for (l = left; l <= right; l++) {
        list[l] = sorted[l];
    }

    if (trace) {
        printf("merge [%d,%d] + [%d,%d]: ", left, mid, mid + 1, right);
        print_array(list, trace_size);
    }
}

// 병합 정렬을 수행하며 필요하면 병합 과정을 출력한다.
static void merge_sort_trace(int list[], int left, int right, int trace)
{
    if (left < right) {
        int mid = (left + right) / 2;
        merge_sort_trace(list, left, mid, trace);
        merge_sort_trace(list, mid + 1, right, trace);
        merge(list, left, mid, right, trace);
    }
}

// 퀵 정렬의 분할을 수행하고 피벗 위치를 반환한다.
static int partition_trace(int list[], int left, int right, int trace)
{
    int pivot = list[left];
    int low = left;
    int high = right + 1;
    int temp;

    do {
        do {
            low++;
        } while (low <= right && list[low] < pivot);

        do {
            high--;
        } while (high >= left && list[high] > pivot);

        if (low < high) {
            SWAP(list[low], list[high], temp);
        }
    } while (low < high);

    SWAP(list[left], list[high], temp);

    if (trace) {
        printf("partition [%d,%d], pivot=%d, position=%d\n", left, right, pivot, high);
        printf("array: ");
        print_array(list, trace_size);
        printf("\n");
    }
    return high;
}

// 퀵 정렬을 수행하며 필요하면 분할 과정을 출력한다.
static void quick_sort_trace(int list[], int left, int right, int trace)
{
    if (left < right) {
        int pivot = partition_trace(list, left, right, trace);
        quick_sort_trace(list, left, pivot - 1, trace);
        quick_sort_trace(list, pivot + 1, right, trace);
    }
}

// 기수 정렬 버킷에 사용할 원형 큐를 초기화한다.
static void init_queue(QueueType *q)
{
    q->front = 0;
    q->rear = 0;
}

// 원형 큐가 비어 있는지 확인한다.
static int is_empty(QueueType *q)
{
    return q->front == q->rear;
}

// 원형 큐가 가득 찼는지 확인한다.
static int is_full(QueueType *q)
{
    return (q->rear + 1) % MAX_QUEUE_SIZE == q->front;
}

// 원형 큐에 정수를 삽입한다.
static void enqueue(QueueType *q, int item)
{
    if (is_full(q)) {
        error("queue is full");
    }
    q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
    q->data[q->rear] = item;
}

// 원형 큐에서 정수를 삭제해 반환한다.
static int dequeue(QueueType *q)
{
    if (is_empty(q)) {
        error("queue is empty");
    }
    q->front = (q->front + 1) % MAX_QUEUE_SIZE;
    return q->data[q->front];
}

// 원형 큐에 들어 있는 값을 순서대로 출력한다.
static void print_queue(QueueType *q)
{
    int i = (q->front + 1) % MAX_QUEUE_SIZE;

    while (i != (q->rear + 1) % MAX_QUEUE_SIZE) {
        printf("%d ", q->data[i]);
        i = (i + 1) % MAX_QUEUE_SIZE;
    }
}

// 비어 있지 않은 기수 정렬 버킷들을 출력한다.
static void print_buckets(QueueType buckets[])
{
    for (int i = 0; i < BUCKETS; i++) {
        if (!is_empty(&buckets[i])) {
            printf("bucket %d: ", i);
            print_queue(&buckets[i]);
            printf("\n");
        }
    }
}

// 기수 정렬을 수행하며 자리수별 버킷 상태를 출력한다.
static void radix_sort_trace(int list[], int n, int digits, int trace)
{
    QueueType buckets[BUCKETS];
    int factor = 1;

    for (int i = 0; i < BUCKETS; i++) {
        init_queue(&buckets[i]);
    }

    for (int d = 0; d < digits; d++) {
        for (int i = 0; i < n; i++) {
            int bucket = (list[i] / factor) % 10;
            enqueue(&buckets[bucket], list[i]);
        }

        if (trace) {
            printf("[%d digit]\n", factor);
            print_buckets(buckets);
        }

        int idx = 0;
        for (int i = 0; i < BUCKETS; i++) {
            while (!is_empty(&buckets[i])) {
                list[idx++] = dequeue(&buckets[i]);
            }
        }

        if (trace) {
            printf("after pass: ");
            print_array(list, n);
            printf("\n");
        }
        factor *= 10;
    }
}

// 단순 정렬 알고리즘들의 결과를 차례로 출력한다.
static void run_simple_sort_examples(int original[], int n)
{
    int list[MAX_SIZE];

    printf("=== Selection Sort ===\n");
    copy_array(list, original, n);
    selection_sort(list, n);
    print_array(list, n);

    printf("\n=== Insertion Sort ===\n");
    copy_array(list, original, n);
    insertion_sort(list, n);
    print_array(list, n);

    printf("\n=== Bubble Sort ===\n");
    copy_array(list, original, n);
    bubble_sort(list, n);
    print_array(list, n);

    printf("\n=== Shell Sort ===\n");
    copy_array(list, original, n);
    shell_sort(list, n);
    print_array(list, n);
}

// 여러 정렬 알고리즘과 추적 출력을 한 번에 시연한다.
int main(void)
{
    int original[] = { 4, 7, 1, 8, 6, 2, 5, 3 };
    int n = (int)(sizeof(original) / sizeof(original[0]));
    int list[MAX_SIZE];

    run_simple_sort_examples(original, n);

    printf("\n=== Quick Sort Trace ===\n");
    trace_size = n;
    copy_array(list, original, n);
    printf("initial: ");
    print_array(list, n);
    quick_sort_trace(list, 0, n - 1, TRUE);
    printf("sorted : ");
    print_array(list, n);

    printf("\n=== Merge Sort Trace ===\n");
    int merge_input[] = { 8, 2, 5, 7, 6, 4, 1, 3 };
    n = (int)(sizeof(merge_input) / sizeof(merge_input[0]));
    trace_size = n;
    copy_array(list, merge_input, n);
    printf("initial: ");
    print_array(list, n);
    merge_sort_trace(list, 0, n - 1, TRUE);
    printf("sorted : ");
    print_array(list, n);

    printf("\n=== Radix Sort Trace ===\n");
    int radix_input[] = { 329, 457, 657, 839, 436, 720, 355 };
    n = (int)(sizeof(radix_input) / sizeof(radix_input[0]));
    copy_array(list, radix_input, n);
    printf("initial: ");
    print_array(list, n);
    radix_sort_trace(list, n, 3, TRUE);
    printf("sorted : ");
    print_array(list, n);

    return 0;
}
