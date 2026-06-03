#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 50
#define MAX_QUEUE_SIZE 200

typedef struct GraphType {
    int n;
    int adj_mat[MAX_VERTICES][MAX_VERTICES];
} GraphType;

typedef struct {
    int data[MAX_QUEUE_SIZE];
    int front;
    int rear;
} QueueType;

static int visited[MAX_VERTICES];

static void error(const char *message)
{
    fprintf(stderr, "%s\n", message);
    exit(1);
}

static void graph_init(GraphType *g)
{
    g->n = 0;
    for (int i = 0; i < MAX_VERTICES; i++) {
        for (int j = 0; j < MAX_VERTICES; j++) {
            g->adj_mat[i][j] = 0;
        }
    }
}

static void insert_vertex(GraphType *g, int v)
{
    if (g->n >= MAX_VERTICES) {
        error("too many vertices");
    }
    (void)v;
    g->n++;
}

static void check_vertex(GraphType *g, int start, int end)
{
    if (start < 0 || end < 0 || start >= g->n || end >= g->n) {
        error("vertex number error");
    }
}

static void insert_edge(GraphType *g, int start, int end)
{
    check_vertex(g, start, end);
    g->adj_mat[start][end] = 1;
    g->adj_mat[end][start] = 1;
}

static void insert_directed_edge(GraphType *g, int start, int end)
{
    check_vertex(g, start, end);
    g->adj_mat[start][end] = 1;
}

static void reset_visited(GraphType *g)
{
    for (int i = 0; i < g->n; i++) {
        visited[i] = FALSE;
    }
}

static int get_degree(GraphType *g, int v)
{
    int count = 0;

    for (int i = 0; i < g->n; i++) {
        if (g->adj_mat[v][i]) {
            count++;
        }
    }
    return count;
}

static int get_outdegree(GraphType *g, int v)
{
    int count = 0;

    for (int i = 0; i < g->n; i++) {
        if (g->adj_mat[v][i]) {
            count++;
        }
    }
    return count;
}

static int get_indegree(GraphType *g, int v)
{
    int count = 0;

    for (int i = 0; i < g->n; i++) {
        if (g->adj_mat[i][v]) {
            count++;
        }
    }
    return count;
}

static void print_adj_mat(GraphType *g)
{
    printf("adjacency matrix\n");
    for (int i = 0; i < g->n; i++) {
        for (int j = 0; j < g->n; j++) {
            printf("%d ", g->adj_mat[i][j]);
        }
        printf("\n");
    }
}

static void dfs_mat(GraphType *g, int v)
{
    visited[v] = TRUE;
    printf("vertex %d -> ", v);

    for (int w = 0; w < g->n; w++) {
        if (g->adj_mat[v][w] && !visited[w]) {
            dfs_mat(g, w);
        }
    }
}

static void dfs_component(GraphType *g, int v)
{
    visited[v] = TRUE;
    printf("%d ", v);

    for (int w = 0; w < g->n; w++) {
        if (g->adj_mat[v][w] && !visited[w]) {
            dfs_component(g, w);
        }
    }
}

static int all_visited(GraphType *g)
{
    for (int i = 0; i < g->n; i++) {
        if (!visited[i]) {
            return FALSE;
        }
    }
    return TRUE;
}

static void print_unvisited(GraphType *g)
{
    int found = FALSE;

    printf("unvisited vertices: ");
    for (int i = 0; i < g->n; i++) {
        if (!visited[i]) {
            printf("%d ", i);
            found = TRUE;
        }
    }
    if (!found) {
        printf("none");
    }
    printf("\n");
}

static void test_connected_from_each_start(GraphType *g)
{
    for (int start = 0; start < g->n; start++) {
        reset_visited(g);
        printf("\nstart vertex %d\n", start);
        printf("visit order: ");
        dfs_mat(g, start);
        printf("end\n");

        if (all_visited(g)) {
            printf("result: connected graph.\n");
        } else {
            printf("result: disconnected graph.\n");
            print_unvisited(g);
        }
    }
}

static int count_and_print_components(GraphType *g)
{
    int count = 0;

    reset_visited(g);
    printf("\nDFS components\n");

    for (int i = 0; i < g->n; i++) {
        if (!visited[i]) {
            count++;
            printf("component %d: ", count);
            dfs_component(g, i);
            printf("\n");
        }
    }

    printf("component count: %d\n", count);
    return count;
}

static void init_queue(QueueType *q)
{
    q->front = 0;
    q->rear = 0;
}

static int is_empty(QueueType *q)
{
    return q->front == q->rear;
}

static int is_full(QueueType *q)
{
    return (q->rear + 1) % MAX_QUEUE_SIZE == q->front;
}

static void enqueue(QueueType *q, int item)
{
    if (is_full(q)) {
        error("queue is full");
    }
    q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
    q->data[q->rear] = item;
}

static int dequeue(QueueType *q)
{
    if (is_empty(q)) {
        error("queue is empty");
    }
    q->front = (q->front + 1) % MAX_QUEUE_SIZE;
    return q->data[q->front];
}

static void bfs_distance(GraphType *g, int start, int dist[])
{
    QueueType q;

    init_queue(&q);

    for (int i = 0; i < g->n; i++) {
        dist[i] = -1;
    }

    dist[start] = 0;
    enqueue(&q, start);

    printf("BFS from %d: ", start);
    while (!is_empty(&q)) {
        int v = dequeue(&q);
        printf("%d ", v);

        for (int w = 0; w < g->n; w++) {
            if (g->adj_mat[v][w] && dist[w] == -1) {
                dist[w] = dist[v] + 1;
                enqueue(&q, w);
            }
        }
    }
    printf("\n");
}

static int path_exists_dfs(GraphType *g, int v, int target)
{
    if (v == target) {
        return TRUE;
    }

    visited[v] = TRUE;

    for (int w = 0; w < g->n; w++) {
        if (g->adj_mat[v][w] && !visited[w]) {
            if (path_exists_dfs(g, w, target)) {
                return TRUE;
            }
        }
    }
    return FALSE;
}

static int path_exists(GraphType *g, int start, int target)
{
    reset_visited(g);
    return path_exists_dfs(g, start, target);
}

static void make_undirected_graph_from_edges(GraphType *g, int n, int edges[][2], int edge_count)
{
    graph_init(g);
    for (int i = 0; i < n; i++) {
        insert_vertex(g, i);
    }
    for (int i = 0; i < edge_count; i++) {
        insert_edge(g, edges[i][0], edges[i][1]);
    }
}

static void make_directed_graph_from_edges(GraphType *g, int n, int edges[][2], int edge_count)
{
    graph_init(g);
    for (int i = 0; i < n; i++) {
        insert_vertex(g, i);
    }
    for (int i = 0; i < edge_count; i++) {
        insert_directed_edge(g, edges[i][0], edges[i][1]);
    }
}

int main(void)
{
    GraphType g;
    int edges[][2] = {
        { 0, 1 }, { 0, 2 },
        { 1, 3 },
        { 2, 3 }, { 2, 4 },
        { 4, 5 },
        { 5, 6 }
    };
    int edge_count = (int)(sizeof(edges) / sizeof(edges[0]));
    int dist[MAX_VERTICES];

    make_undirected_graph_from_edges(&g, 8, edges, edge_count);

    print_adj_mat(&g);

    printf("\ndegree\n");
    for (int i = 0; i < g.n; i++) {
        printf("%d: %d\n", i, get_degree(&g, i));
    }

    test_connected_from_each_start(&g);
    count_and_print_components(&g);

    bfs_distance(&g, 0, dist);
    printf("distance from 0\n");
    for (int i = 0; i < g.n; i++) {
        printf("%d: %d\n", i, dist[i]);
    }

    printf("\n================ Directed Graph Test ================\n");

    GraphType dg;
    int directed_edges[][2] = {
        { 0, 1 }, { 0, 2 },
        { 1, 3 },
        { 2, 3 },
        { 3, 4 },
        { 4, 1 }, { 4, 5 }
    };
    int directed_edge_count = (int)(sizeof(directed_edges) / sizeof(directed_edges[0]));
    int queries[][2] = { { 0, 5 }, { 5, 0 }, { 2, 1 } };
    int query_count = (int)(sizeof(queries) / sizeof(queries[0]));

    make_directed_graph_from_edges(&dg, 6, directed_edges, directed_edge_count);

    printf("vertex  indegree  outdegree\n");
    for (int i = 0; i < dg.n; i++) {
        printf("%d       %d         %d\n", i, get_indegree(&dg, i), get_outdegree(&dg, i));
    }

    reset_visited(&dg);
    printf("DFS from 0: ");
    dfs_mat(&dg, 0);
    printf("end\n");

    printf("\npath query\n");
    for (int i = 0; i < query_count; i++) {
        int start = queries[i][0];
        int target = queries[i][1];
        printf("%d to %d: %s\n", start, target, path_exists(&dg, start, target) ? "YES" : "NO");
    }

    bfs_distance(&dg, 0, dist);
    printf("BFS distance from 0\n");
    for (int i = 0; i < dg.n; i++) {
        printf("%d: %d\n", i, dist[i]);
    }

    return 0;
}
