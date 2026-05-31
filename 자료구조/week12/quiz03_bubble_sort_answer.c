#include <stdio.h>

#define SWAP(x, y, t) ((t) = (x), (x) = (y), (y) = (t))

static void print_array(const int list[], int n)
{
    for (int i = 0; i < n; i++) {
        printf("%d ", list[i]);
    }
    printf("\n");
}

static void bubble_sort_trace(int list[], int n)
{
    int temp;

    printf("start : ");
    print_array(list, n);

    for (int i = n - 1; i > 0; i--) {
        for (int j = 0; j < i; j++) {
            if (list[j] > list[j + 1]) {
                SWAP(list[j], list[j + 1], temp);
            }
        }
        printf("pass %d: ", n - i);
        print_array(list, n);
    }
}

int main(void)
{
    int list[] = { 3, 7, 4, 1, 6, 9 };
    int n = (int)(sizeof(list) / sizeof(list[0]));

    bubble_sort_trace(list, n);
    printf("bubble sort moves records often because every inversion is fixed by adjacent swaps.\n");
    printf("selection sort usually swaps only once per outer pass.\n");
    return 0;
}
