#include <stdio.h>
#include <stdlib.h>

#define MAX_ELEMENT 200
#define JOBS 7
#define MACHINES 3

typedef struct {
    int id;
    int key; // avail: 기계가 사용가능하게 되는 시간
} element;

typedef struct {
    element heap[MAX_ELEMENT];
    int heap_size;
} HeapType;

static HeapType *create(void)
{
    return (HeapType *)malloc(sizeof(HeapType));
}

static void init(HeapType *h)
{
    h->heap_size = 0;
}

static void insert_min_heap(HeapType *h, element item)
{
    int i = ++h->heap_size;

    while (i != 1 && item.key < h->heap[i / 2].key) {
        h->heap[i] = h->heap[i / 2];
        i /= 2;
    }
    h->heap[i] = item;
}

static element delete_min_heap(HeapType *h)
{
    int parent;
    int child;
    element item;
    element temp;

    item = h->heap[1];
    temp = h->heap[h->heap_size--];
    parent = 1;
    child = 2;

    while (child <= h->heap_size) {
        if (child < h->heap_size && h->heap[child].key > h->heap[child + 1].key) {
            child++;
        }
        if (temp.key <= h->heap[child].key) {
            break;
        }
        h->heap[parent] = h->heap[child];
        parent = child;
        child *= 2;
    }
    h->heap[parent] = temp;
    return item;
}

int main() {
  int jobs[JOBS]={8,7,6,5,3,2,1};
  element m={0,0};
  element machine;
  HeapType *h;
  h=create();
  init(h);
  for(int i=0;i<MACHINES;i++) {
    m.id=i+1;
    m.key=0;
    insert_min_heap(h, m);
  }
  for(int i=0;i<JOBS;i++) {
    m=delete_min_heap(h);
    // m.key + jobs[i] - 1: 시간 10부터 시간 10까지 할당(가능한 시간 avail에서 시작해 한 칸 동안 작업)
    printf("JOB %d을 시간=%d부터 시간=%d까지 기계 %d번에 할당한다. \n", i, m.key, m.key + jobs[i] - 1, m.id);
    m.key+=jobs[i];
    insert_min_heap(h,m);
  }

  return 0;
}