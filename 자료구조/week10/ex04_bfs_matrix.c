#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 50
#define MAX_QUEUE_SIZE 50
#define TRUE 1
#define FALSE 0

typedef int element;

typedef struct {
    element data[MAX_QUEUE_SIZE];
    int front;
    int rear;
} QueueType;

typedef struct GraphType {
    int n;
    int adj_mat[MAX_VERTICES][MAX_VERTICES];
} GraphType;

static int visited[MAX_VERTICES];

// BFS에 사용할 원형 큐를 초기화한다.
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
static void enqueue(QueueType *q, element item)
{
    q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
    q->data[q->rear] = item;
}

// 원형 큐에서 정점 번호를 삭제해 반환한다.
static element dequeue(QueueType *q)
{
    q->front = (q->front + 1) % MAX_QUEUE_SIZE;
    return q->data[q->front];
}

// 인접행렬 그래프와 방문 배열을 초기화한다.
static void graph_init(GraphType *g)
{
    g->n = 0;
    for (int i = 0; i < MAX_VERTICES; i++) {
        visited[i] = FALSE;
        for (int j = 0; j < MAX_VERTICES; j++) {
            g->adj_mat[i][j] = 0;
        }
    }
}

// 그래프에 정점을 하나 추가한다.
static void insert_vertex(GraphType *g, int v)
{
    (void)v;
    g->n++;
}

// 무방향 그래프에 양방향 간선을 추가한다.
static void insert_edge(GraphType *g, int start, int end)
{
    g->adj_mat[start][end] = 1;
    g->adj_mat[end][start] = 1;
}

// 인접행렬 그래프를 BFS로 순회하며 방문 정점을 출력한다.
static void bfs_mat(GraphType *g, int v)
{
    QueueType q;

    queue_init(&q);
    visited[v] = TRUE;
    printf("%d visit -> ", v);
    enqueue(&q, v);

    while (!is_empty(&q)) {
        v = dequeue(&q);
        for (int w = 0; w < g->n; w++) {
            if (g->adj_mat[v][w] && !visited[w]) {
                visited[w] = TRUE;
                printf("%d visit -> ", w);
                enqueue(&q, w);
            }
        }
    }
}

// 인접행렬 그래프를 만들고 BFS 순회를 실행한다.
int main(void)
{
    GraphType *g = (GraphType *)malloc(sizeof(GraphType));

    if (g == NULL) {
        fprintf(stderr, "allocation failed\n");
        return 1;
    }
    graph_init(g);
    for (int i = 0; i < 6; i++) {
        insert_vertex(g, i);
    }
    insert_edge(g, 0, 2);
    insert_edge(g, 2, 1);
    insert_edge(g, 2, 3);
    insert_edge(g, 0, 4);
    insert_edge(g, 4, 5);
    insert_edge(g, 1, 5);

    printf("BFS\n");
    bfs_mat(g, 0);
    printf("\n");

    free(g);
    return 0;
}
