#include <stdio.h>

#define MAX_SIZE 32

static int sorted[MAX_SIZE];

static void merge(int list[], int left, int mid, int right)
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
}

static void merge_sort(int list[], int left, int right)
{
    if (left < right) {
        int mid = (left + right) / 2;
        merge_sort(list, left, mid);
        merge_sort(list, mid + 1, right);
        merge(list, left, mid, right);
    }
}

int main(void)
{
    int list[] = { 27, 10, 12, 20, 25, 13, 15, 22 };
    int n = (int)(sizeof(list) / sizeof(list[0]));

    merge_sort(list, 0, n - 1);
    for (int i = 0; i < n; i++) {
        printf("%d ", list[i]);
    }
    printf("\n");
    return 0;
}
