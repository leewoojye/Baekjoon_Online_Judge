#include <stdio.h>
#include <stdlib.h>

#define MAX_ELEMENTS 100

typedef struct {
    int heap[MAX_ELEMENTS];
    int heap_size;
} HeapType;

void print_array(const char* label, int arr[], int n) {
    printf("%-8s: ", label);
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void print_step(const char* phase, HeapType* h, int sorted_arr[], int sorted_size, int total_size) {
    printf("=== %s ===\n", phase);
    printf("Heap    : ");
    for (int i = 1; i <= h->heap_size; i++) {
        printf("%d ", h->heap[i]);
    }
    printf("\n");

    printf("Sorted  : ");
    if (sorted_size > 0) {
        for (int i = 0; i < total_size - sorted_size; i++) {
            printf("   "); 
        }
        for (int i = 0; i < sorted_size; i++) {
            printf("%d ", sorted_arr[i]);
        }
    }
    printf("\n\n");
}

void insert_max_heap(HeapType* h, int item, int sorted_arr[], int sorted_size, int total_size) {
    int i;
    h->heap_size++;
    i = h->heap_size;
    while ((i != 1) && (item > h->heap[i / 2])) {
        h->heap[i] = h->heap[i / 2];
        i /= 2;
    }
    h->heap[i] = item;
    print_step("Insertion Phase", h, sorted_arr, sorted_size, total_size);
}

int delete_max_heap(HeapType* h) {
    int parent, child;
    int item, temp;

    if (h->heap_size == 0) {
        fprintf(stderr, "Heap is empty\n");
        exit(1);
    }

    item = h->heap[1];
    temp = h->heap[h->heap_size--];
    parent = 1;
    child = 2;

    while (child <= h->heap_size) {
        if ((child < h->heap_size) && (h->heap[child] < h->heap[child + 1])) {
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

void heap_sort(int arr[], int n) {
    HeapType h;
    h.heap_size = 0;
    
    int* sorted_arr = (int*)malloc(sizeof(int) * n);
    int sorted_size = 0;

    for (int i = 0; i < n; i++) {
        insert_max_heap(&h, arr[i], sorted_arr, sorted_size, n);
    }

    for (int i = n - 1; i >= 0; i--) {
        int max_val = delete_max_heap(&h);
        sorted_arr[i] = max_val;
        sorted_size++;
        
        int temp_sorted[MAX_ELEMENTS];
        int k = 0;
        for(int j = i; j < n; j++){
            temp_sorted[k++] = sorted_arr[j];
        }

        printf("=== Deletion (Sorting) Phase ===\n");
        printf("Heap    : ");
        for (int j = 1; j <= h.heap_size; j++) {
            printf("%d ", h.heap[j]);
        }
        printf("\n");

        printf("Sorted  : ");
        for (int j = 0; j < i; j++) {
             printf("   ");
        }
        for (int j = 0; j < k; j++) {
            printf("%d ", temp_sorted[j]);
        }
        printf("\n\n");
    }
    
    free(sorted_arr);
}

int main() {
    int arr[] = { 23, 56, 11, 9, 40, 99, 27, 34 };
    int n = sizeof(arr) / sizeof(arr[0]);

    heap_sort(arr, n);

    return 0;
}
