#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 50
#define TRUE 1
#define FALSE 0

typedef struct GraphType {
    int n;
    int adj_mat[MAX_VERTICES][MAX_VERTICES];
} GraphType;

static int visited[MAX_VERTICES];

// 인접행렬 그래프와 방문 배열을 초기화한다.
static void init(GraphType *g)
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

// 인접행렬 그래프를 DFS로 순회하며 방문 정점을 출력한다.
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

// 인접행렬 그래프를 만들고 DFS 순회를 실행한다.
int main(void)
{
    GraphType *g = (GraphType *)malloc(sizeof(GraphType));

    if (g == NULL) {
        fprintf(stderr, "allocation failed\n");
        return 1;
    }
    init(g);

    for (int i = 0; i < 4; i++) {
        insert_vertex(g, i);
    }
    insert_edge(g, 0, 1);
    insert_edge(g, 0, 2);
    insert_edge(g, 0, 3);
    insert_edge(g, 1, 2);
    insert_edge(g, 2, 3);

    printf("DFS\n");
    dfs_mat(g, 0);
    printf("\n");

    free(g);
    return 0;
}
