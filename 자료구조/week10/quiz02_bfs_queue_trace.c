#include <stdio.h>

#define VERTICES 5
#define MAX_QUEUE_SIZE 20

// 원형큐 bfs 넓이우선탐색
typedef struct {
    int data[MAX_QUEUE_SIZE];
    int front;
    int rear;
} QueueType;

typedef struct {
    int n;
    int adj_mat[VERTICES][VERTICES];
} GraphType;

static int visited[VERTICES];

// 무방향 그래프에 양방향 간선을 추가한다.
static void insert_edge(GraphType *g, int a, int b)
{
    g->adj_mat[a][b] = 1;
    g->adj_mat[b][a] = 1;
}

// BFS 추적에 사용할 원형 큐를 초기화한다.
static void queue_init(QueueType *q)
{
    q->front = 0;
    q->rear = 0;
}

// 원형 큐가 비어 있는지 확인한다.
static int is_empty(QueueType *q)
{
    return q->front == q->rear;
}

// 원형 큐에 정점 번호를 삽입한다.
static void enqueue(QueueType *q, int item)
{
    q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
    q->data[q->rear] = item;
}

// 원형 큐에서 정점 번호를 삭제해 반환한다.
static int dequeue(QueueType *q)
{
    q->front = (q->front + 1) % MAX_QUEUE_SIZE;
    return q->data[q->front];
}

// 현재 큐에 들어 있는 정점 번호들을 출력한다.
static void print_queue(QueueType *q)
{
    printf("[");
    for (int i = (q->front + 1) % MAX_QUEUE_SIZE; i != (q->rear + 1) % MAX_QUEUE_SIZE; i = (i + 1) % MAX_QUEUE_SIZE) {
        printf("%d", q->data[i]);
        if ((i + 1) % MAX_QUEUE_SIZE != (q->rear + 1) % MAX_QUEUE_SIZE) {
            printf(" ");
        }
    }
    printf("]");
}

// BFS를 수행하며 방문과 큐 상태 변화를 출력한다.
static void bfs_trace(GraphType *g, int start)
{
    QueueType q;

    queue_init(&q);
    visited[start] = 1;
    enqueue(&q, start);
    printf("visit %d, queue=", start);
    print_queue(&q);
    printf("\n");

    while (!is_empty(&q)) {
        int v = dequeue(&q);
        printf("dequeue %d, queue=", v);
        print_queue(&q);
        printf("\n");

        for (int w = 0; w < g->n; w++) {
            if (g->adj_mat[v][w] && !visited[w]) {
                visited[w] = 1;
                enqueue(&q, w);
                printf("  visit %d, queue=", w);
                print_queue(&q);
                printf("\n");
            }
        }
    }
}

// 그래프를 만들고 특정 시작 정점의 BFS 큐 변화를 출력한다.
int main(void)
{
    GraphType g = { 0 };

    g.n = VERTICES;
    insert_edge(&g, 0, 1);
    insert_edge(&g, 0, 2);
    insert_edge(&g, 0, 3);
    insert_edge(&g, 1, 2);
    insert_edge(&g, 1, 4);
    insert_edge(&g, 2, 3);
    insert_edge(&g, 3, 4);

    bfs_trace(&g, 2);
    printf("visit order: 2 0 1 3 4\n");
    return 0;
}
