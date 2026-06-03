#include <stdio.h>
#include <stdlib.h>

typedef int element;

typedef struct {
    element *data;
    int capacity;
    int front, rear;
} QueueType;

void init_queue(QueueType *s)
{
    s->front = s->rear = 0;
    s->capacity = 1;
    s->data = (element *)malloc(s->capacity * sizeof(element));
    if (s->data == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
}

int is_empty(QueueType *s)
{
    return s->front == s->rear;
}

int is_full(QueueType *s)
{
    return (s->rear + 1) % (s->capacity) == s->front;
}

void push(QueueType *s, element item)
{
    if (is_full(s)) {
        s->capacity *= 2;
        s->data = (element *)realloc(s->data, s->capacity * sizeof(element));
        if (s->data == NULL) {
            fprintf(stderr, "Memory reallocation failed\n");
            exit(1);
        }
    }
    s->data[++(s->rear)] = item;
}

element pop(QueueType *s)
{
    if (is_empty(s)) {
        fprintf(stderr, "Stack underflow\n");
        exit(1);
    }
    s->front = (s->front + 1) % (s->capacity);
    return s->data[s->front];
}

void queue_print(QueueType *q)
{
    printf("queue = ");
    if (!is_empty(q)) {
        int i = q->front;
        do {
            i = (i + 1) % (q->capacity);
            printf("%d ", q->data[i]);
            if (i == q->rear) {
                break;
            }
        } while (i != q->front);
    }
}

int main(void)
{
    int operations[] = {1, 2, 3, -1, 4, 5, 6, 7, 8, -1};
    QueueType s;
    init_queue(&s);
    for(int i=0;i<10;++i) {
      if(operations[i]>0) {
        push(&s,operations[i]);
        printf("enqueue = %d ",operations[i]);
        queue_print(&s);
        printf("capacity = %d\n",s.capacity);
        continue;
      }
      element pop_e = pop(&s);
      printf("dequeue -> %d ",pop_e);
      queue_print(&s);
      printf("capacity = %d\n",s.capacity);
    }
    free(s.data);
    return 0;
}
