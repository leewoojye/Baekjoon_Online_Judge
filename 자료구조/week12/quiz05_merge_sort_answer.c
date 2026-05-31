#include <stdio.h>

#define MAX_SIZE 32

static int sorted[MAX_SIZE];

static void print_array(const int list[], int n)
{
    for (int i = 0; i < n; i++) {
        printf("%d ", list[i]);
    }
    printf("\n");
}

static void merge(int list[], int left, int mid, int right, int n)
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

    printf("merge %d..%d: ", left, right);
    print_array(list, n);
}

static void merge_sort_trace(int list[], int left, int right, int n)
{
    if (left < right) {
        int mid = (left + right) / 2;
        merge_sort_trace(list, left, mid, n);
        merge_sort_trace(list, mid + 1, right, n);
        merge(list, left, mid, right, n);
    }
}

int main(void)
{
    int list[] = { 8, 2, 5, 7, 6, 4, 1, 3 };
    int n = (int)(sizeof(list) / sizeof(list[0]));

    printf("start      : ");
    print_array(list, n);
    merge_sort_trace(list, 0, n - 1, n);
    printf("merge sort divides and merges the same-sized subproblems regardless of initial order.\n");
    printf("Therefore best, average, and worst cases are all O(n log n).\n");
    return 0;
}
