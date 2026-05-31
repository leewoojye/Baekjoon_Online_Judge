#include <stdio.h>

static void print_array(const int list[], int n)
{
    for (int i = 0; i < n; i++) {
        printf("%d ", list[i]);
    }
    printf("\n");
}

static void insertion_sort_trace(int list[], int n)
{
    printf("start : ");
    print_array(list, n);

    for (int i = 1; i < n; i++) {
        int key = list[i];
        int j;

        for (j = i - 1; j >= 0 && list[j] > key; j--) {
            list[j + 1] = list[j];
        }
        list[j + 1] = key;

        printf("pass %d: ", i);
        print_array(list, n);
    }
}

int main(void)
{
    int list[] = { 3, 7, 9, 4, 1, 6 };
    int n = (int)(sizeof(list) / sizeof(list[0]));

    insertion_sort_trace(list, n);
    printf("insertion sort is stable because equal keys are not shifted when the condition is list[j] > key.\n");
    return 0;
}
