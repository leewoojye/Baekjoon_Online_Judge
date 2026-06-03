#include <stdio.h>

#define VERTICES 5

typedef struct GraphType {
    int n;
    int adj_mat[VERTICES][VERTICES];
} GraphType;

static void insert_edge(GraphType *g, int a, int b)
{
    g->adj_mat[a][b] = 1;
    g->adj_mat[b][a] = 1;
}

static int get_degree(GraphType *g, int v)
{
    int degree = 0;

    for (int i = 0; i < g->n; i++) {
        degree += g->adj_mat[v][i];
    }
    return degree;
}

static void print_matrix(GraphType *g)
{
    printf("adjacency matrix:\n");
    for (int i = 0; i < g->n; i++) {
        for (int j = 0; j < g->n; j++) {
            printf("%d ", g->adj_mat[i][j]);
        }
        printf("\n");
    }
}

static void print_list(GraphType *g)
{
    printf("\nadjacency list:\n");
    for (int i = 0; i < g->n; i++) {
        printf("%d:", i);
        for (int j = 0; j < g->n; j++) {
            if (g->adj_mat[i][j]) {
                printf(" %d", j);
            }
        }
        printf("\n");
    }
}

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

    print_matrix(&g);
    print_list(&g);
    printf("\ndegree(2)=%d\n", get_degree(&g, 2));
    return 0;
}
