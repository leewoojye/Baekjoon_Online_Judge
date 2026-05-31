#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 50
#define MAX_QUEUE_SIZE 50
#define TRUE 1
#define FALSE 0

typedef struct GraphNode {
    int vertex;
    struct GraphNode *link;
} GraphNode;

typedef struct GraphType {
    int n;
    GraphNode *adj_list[MAX_VERTICES];
} GraphType;

typedef struct {
    int data[MAX_QUEUE_SIZE];
    int front;
    int rear;
} QueueType;

static int visited[MAX_VERTICES];

static void queue_init(QueueType *q)
{
    q->front = 0;
    q->rear = 0;
}

static int is_empty(QueueType *q)
{
    return q->front == q->rear;
}

static void enqueue(QueueType *q, int item)
{
    q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
    q->data[q->rear] = item;
}

static int dequeue(QueueType *q)
{
    q->front = (q->front + 1) % MAX_QUEUE_SIZE;
    return q->data[q->front];
}

static void graph_init(GraphType *g)
{
    g->n = 0;
    for (int i = 0; i < MAX_VERTICES; i++) {
        g->adj_list[i] = NULL;
        visited[i] = FALSE;
    }
}

static void insert_vertex(GraphType *g, int v)
{
    (void)v;
    g->n++;
}

static void insert_directed_edge(GraphType *g, int start, int end)
{
    GraphNode *node = (GraphNode *)malloc(sizeof(GraphNode));
    if (node == NULL) {
        fprintf(stderr, "allocation failed\n");
        exit(1);
    }
    node->vertex = end;
    node->link = g->adj_list[start];
    g->adj_list[start] = node;
}

static void insert_edge(GraphType *g, int start, int end)
{
    insert_directed_edge(g, start, end);
    insert_directed_edge(g, end, start);
}

static void bfs_list(GraphType *g, int v)
{
    GraphNode *w;
    QueueType q;

    queue_init(&q);
    visited[v] = TRUE;
    printf("%d visit -> ", v);
    enqueue(&q, v);

    while (!is_empty(&q)) {
        v = dequeue(&q);
        for (w = g->adj_list[v]; w != NULL; w = w->link) {
            if (!visited[w->vertex]) {
                visited[w->vertex] = TRUE;
                printf("%d visit -> ", w->vertex);
                enqueue(&q, w->vertex);
            }
        }
    }
}

static void free_graph(GraphType *g)
{
    for (int i = 0; i < g->n; i++) {
        GraphNode *node = g->adj_list[i];
        while (node != NULL) {
            GraphNode *next = node->link;
            free(node);
            node = next;
        }
    }
}

int main(void)
{
    GraphType g;

    graph_init(&g);
    for (int i = 0; i < 6; i++) {
        insert_vertex(&g, i);
    }
    insert_edge(&g, 0, 2);
    insert_edge(&g, 2, 1);
    insert_edge(&g, 2, 3);
    insert_edge(&g, 0, 4);
    insert_edge(&g, 4, 5);
    insert_edge(&g, 1, 5);

    printf("BFS list\n");
    bfs_list(&g, 0);
    printf("\n");

    free_graph(&g);
    return 0;
}
