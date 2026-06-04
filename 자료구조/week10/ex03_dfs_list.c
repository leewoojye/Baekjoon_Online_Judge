#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 50
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

static int visited[MAX_VERTICES];

// 인접리스트 그래프와 방문 배열을 초기화한다.
static void graph_init(GraphType *g)
{
    g->n = 0;
    for (int i = 0; i < MAX_VERTICES; i++) {
        g->adj_list[i] = NULL;
        visited[i] = FALSE;
    }
}

// 그래프에 정점을 하나 추가한다.
static void insert_vertex(GraphType *g, int v)
{
    (void)v;
    g->n++;
}

// 방향 그래프에 단방향 간선을 추가한다.
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

// 무방향 그래프에 양방향 간선을 추가한다.
static void insert_edge(GraphType *g, int start, int end)
{
    insert_directed_edge(g, start, end);
    insert_directed_edge(g, end, start);
}

// 인접리스트 그래프를 DFS로 순회하며 방문 정점을 출력한다.
static void dfs_list(GraphType *g, int v)
{
    GraphNode *w;

    visited[v] = TRUE;
    printf("vertex %d -> ", v);
    for (w = g->adj_list[v]; w != NULL; w = w->link) {
        if (!visited[w->vertex]) {
            dfs_list(g, w->vertex);
        }
    }
}

// 인접리스트 그래프의 동적 간선 노드들을 해제한다.
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

// 인접리스트 그래프를 만들고 DFS 순회를 실행한다.
int main(void)
{
    GraphType g;

    graph_init(&g);
    for (int i = 0; i < 4; i++) {
        insert_vertex(&g, i);
    }
    insert_edge(&g, 0, 1);
    insert_edge(&g, 0, 2);
    insert_edge(&g, 0, 3);
    insert_edge(&g, 1, 2);
    insert_edge(&g, 2, 3);

    printf("DFS list\n");
    dfs_list(&g, 0);
    printf("\n");

    free_graph(&g);
    return 0;
}
