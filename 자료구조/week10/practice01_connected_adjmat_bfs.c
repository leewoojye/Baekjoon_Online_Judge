#include <stdio.h>

#define MAX_VERTICES 8
#define MAX_QUEUE_SIZE 20

typedef int element;

typedef struct {
    element data[MAX_QUEUE_SIZE];
    int front;
    int rear;
} QueueType;

typedef struct {
    int n;
    int adj_mat[MAX_VERTICES][MAX_VERTICES];
} GraphType;

static int visited[MAX_VERTICES];
static int order[MAX_VERTICES];
static int order_size;

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

// 인접행렬 그래프를 빈 그래프로 초기화한다.
static void graph_init(GraphType *g)
{
    g->n = 0;
    for (int i = 0; i < MAX_VERTICES; i++) {
        for (int j = 0; j < MAX_VERTICES; j++) {
            g->adj_mat[i][j] = 0;
        }
    }
}

// 그래프에 지정한 번호의 정점을 추가한다.
static void insert_vertex(GraphType *g, int v)
{
    if (v >= 0 && v < MAX_VERTICES && v >= g->n) {
        g->n = v + 1;
    }
}

// 무방향 그래프에 양방향 간선을 추가한다.
static void insert_edge(GraphType *g, int u, int v)
{
    if (u < 0 || v < 0 || u >= g->n || v >= g->n) {
        return;
    }
    g->adj_mat[u][v] = 1;
    g->adj_mat[v][u] = 1;
}

// 방문 배열과 방문 순서 배열을 초기화한다.
static void clear_visited(void)
{
    for (int i = 0; i < MAX_VERTICES; i++) {
        visited[i] = 0;
        order[i] = -1;
    }
    order_size = 0;
}

// BFS로 방문 가능한 정점을 순서 배열에 기록한다.
static void bfs(GraphType *g, int start)
{
    QueueType q;
    int v;

    queue_init(&q);
    visited[start] = 1;
    order[order_size++] = start;
    enqueue(&q, start);

    while (!is_empty(&q)) {
        v = dequeue(&q);
        for (int w = 0; w < g->n; w++) {
            if (g->adj_mat[v][w] && !visited[w]) {
                visited[w] = 1;
                order[order_size++] = w;
                enqueue(&q, w);
            }
        }
    }
}

// BFS 방문 순서를 출력한다.
static void print_visit_order(void)
{
    printf("Visit order: ");
    for (int i = 0; i < order_size; i++) {
        printf("vertex %d", order[i]);
        if (i + 1 < order_size) {
            printf(" -> ");
        }
    }
    printf(" -> end\n");
}

// 아직 방문하지 않은 정점들을 출력한다.
static void print_unvisited(GraphType *g)
{
    int found = 0;

    printf("Unvisited vertices: ");
    for (int i = 0; i < g->n; i++) {
        if (!visited[i]) {
            printf("%d ", i);
            found = 1;
        }
    }
    if (!found) {
        printf("none");
    }
    printf("\n");
}

// 특정 시작 정점에서 BFS로 그래프 연결 여부를 확인한다.
static void check_connected_from(GraphType *g, int start)
{
    clear_visited();
    bfs(g, start);

    printf("Start vertex %d\n", start);
    print_visit_order();

    if (order_size == g->n) {
        printf("Result: connected graph.\n");
    } else {
        printf("Result: disconnected graph.\n");
        print_unvisited(g);
    }
    printf("\n");
}

// 연결 그래프 예제 데이터를 만든다.
void make_connected_graph(GraphType *g)
{
    graph_init(g);

    for (int i = 0; i < 8; i++) {
        insert_vertex(g, i);
    }

    insert_edge(g, 0, 1);
    insert_edge(g, 1, 2);
    insert_edge(g, 2, 3);
    insert_edge(g, 3, 4);
    insert_edge(g, 4, 5);
    insert_edge(g, 5, 6);
    insert_edge(g, 6, 7);

    insert_edge(g, 0, 2);
    insert_edge(g, 2, 5);
    insert_edge(g, 3, 6);
}

// 비연결 그래프 예제 데이터를 만든다.
void make_disconnected_graph(GraphType *g)
{
    graph_init(g);

    for (int i = 0; i < 8; i++) {
        insert_vertex(g, i);
    }

    insert_edge(g, 0, 1);
    insert_edge(g, 1, 2);
    insert_edge(g, 2, 3);

    insert_edge(g, 4, 5);

    insert_edge(g, 6, 7);
}

// 모든 시작 정점에 대해 연결 여부를 테스트한다.
static void test_graph(const char *title, GraphType *g)
{
    printf("===== %s =====\n", title);
    for (int start = 0; start < g->n; start++) {
        check_connected_from(g, start);
    }
}

// 연결 그래프와 비연결 그래프의 BFS 연결성 검사를 실행한다.
int main(void)
{
    GraphType g;

    make_connected_graph(&g);
    test_graph("Connected Graph BFS Test", &g);

    make_disconnected_graph(&g);
    test_graph("Disconnected Graph BFS Test", &g);

    return 0;
}
