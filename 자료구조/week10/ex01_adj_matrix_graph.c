#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 50

typedef struct GraphType {
    int n;
    int adj_mat[MAX_VERTICES][MAX_VERTICES];
} GraphType;

// 인접행렬 그래프를 빈 그래프로 초기화한다.
static void init(GraphType *g)
{
    g->n = 0;
    for (int r = 0; r < MAX_VERTICES; r++) {
        for (int c = 0; c < MAX_VERTICES; c++) {
            g->adj_mat[r][c] = 0;
        }
    }
}

// 그래프에 정점을 하나 추가한다.
static void insert_vertex(GraphType *g, int v)
{
    (void)v;
    if (g->n + 1 > MAX_VERTICES) {
        fprintf(stderr, "too many vertices\n");
        return;
    }
    g->n++;
}

// 무방향 그래프에 양방향 간선을 추가한다.
static void insert_edge(GraphType *g, int start, int end)
{
    if (start >= g->n || end >= g->n) {
        fprintf(stderr, "invalid vertex number\n");
        return;
    }
    g->adj_mat[start][end] = 1;
    g->adj_mat[end][start] = 1;
}

// 그래프의 인접행렬을 출력한다.
static void print_adj_mat(GraphType *g)
{
    for (int i = 0; i < g->n; i++) {
        for (int j = 0; j < g->n; j++) {
            printf("%2d", g->adj_mat[i][j]);
        }
        printf("\n");
    }
}

// 인접행렬 그래프를 생성하고 출력한다.
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

    print_adj_mat(g);
    free(g);
    return 0;
}
