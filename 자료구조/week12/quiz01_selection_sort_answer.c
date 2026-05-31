#include <stdio.h>

#define SWAP(x, y, t) ((t) = (x), (x) = (y), (y) = (t))

typedef struct {
    int key;
    char tag;
} Record;

static void print_array(const int list[], int n)
{
    for (int i = 0; i < n; i++) {
        printf("%d ", list[i]);
    }
    printf("\n");
}

static void selection_sort_trace(int list[], int n)
{
    int temp;

    printf("start : ");
    print_array(list, n);
    for (int i = 0; i < n - 1; i++) {
        int least = i;
        for (int j = i + 1; j < n; j++) {
            if (list[j] < list[least]) {
                least = j;
            }
        }
        SWAP(list[i], list[least], temp);
        printf("pass %d: ", i + 1);
        print_array(list, n);
    }
}

static void unstable_example(void)
{
    Record a[3] = { { 2, 'A' }, { 2, 'B' }, { 1, 'C' } };
    Record temp;
    int least = 0;

    for (int j = 1; j < 3; j++) {
        if (a[j].key < a[least].key) {
            least = j;
        }
    }
    temp = a[0];
    a[0] = a[least];
    a[least] = temp;

    printf("unstable example after first pass: ");
    for (int i = 0; i < 3; i++) {
        printf("%d%c ", a[i].key, a[i].tag);
    }
    printf("\n");
}

int main(void)
{
    int list[] = { 1, 3, 4, 9, 7, 6 };
    int n = (int)(sizeof(list) / sizeof(list[0]));

    selection_sort_trace(list, n);
    unstable_example();
    printf("already sorted input still performs n(n-1)/2 comparisons in basic selection sort.\n");
    printf("one improvement is to skip the swap when least == i; comparisons still remain.\n");
    return 0;
}
