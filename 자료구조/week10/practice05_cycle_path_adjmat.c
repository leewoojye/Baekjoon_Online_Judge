#include <stdio.h>

#define MAX_VERTICES 8

typedef struct {
    int n;
    int adj_mat[MAX_VERTICES][MAX_VERTICES];
} GraphType;

static int visited[MAX_VERTICES];

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
    if (v >= 0 && v < MAX_VERTICES && v >= g->n) {
        g->n = v + 1;
    }
}

static void insert_edge(GraphType *g, int u, int v)
{
    if (u < 0 || v < 0 || u >= g->n || v >= g->n) {
        return;
    }
    g->adj_mat[u][v] = 1;
    g->adj_mat[v][u] = 1;
}

static void clear_visited(void)
{
    for (int i = 0; i < MAX_VERTICES; i++) {
        visited[i] = 0;
    }
}

static int dfs_cycle(GraphType *g, int v, int parent)
{
    visited[v] = 1;

    for (int w = 0; w < g->n; w++) {
        if (!g->adj_mat[v][w]) {
            continue;
        }
        if (!visited[w]) {
            if (dfs_cycle(g, w, v)) {
                return 1;
            }
        } else if (w != parent) {
            return 1;
        }
    }
    return 0;
}

static int has_cycle(GraphType *g)
{
    clear_visited();
    for (int i = 0; i < g->n; i++) {
        if (!visited[i] && dfs_cycle(g, i, -1)) {
            return 1;
        }
    }
    return 0;
}

static int dfs_same_start_end_cycle(GraphType *g, int start, int v, int depth)
{
    visited[v] = 1;

    for (int w = 0; w < g->n; w++) {
        if (!g->adj_mat[v][w]) {
            continue;
        }
        if (w == start && depth >= 2) {
            return 1;
        }
        if (!visited[w]) {
            if (dfs_same_start_end_cycle(g, start, w, depth + 1)) {
                return 1;
            }
        }
    }
    return 0;
}

static int has_same_start_end_cycle(GraphType *g, int start)
{
    if (start < 0 || start >= g->n) {
        return 0;
    }
    clear_visited();
    return dfs_same_start_end_cycle(g, start, start, 0);
}

static void print_adj_mat(GraphType *g)
{
    for (int i = 0; i < g->n; i++) {
        for (int j = 0; j < g->n; j++) {
            printf("%2d", g->adj_mat[i][j]);
        }
        printf("\n");
    }
}

static void print_same_start_end_cycles(GraphType *g)
{
    printf("Same start/end cycle: ");
    for (int i = 0; i < g->n; i++) {
        printf("%d=%s", i, has_same_start_end_cycle(g, i) ? "yes" : "no");
        if (i + 1 < g->n) {
            printf(", ");
        }
    }
    printf("\n");
}

static void print_result(const char *title, GraphType *g)
{
    printf("===== %s =====\n", title);
    print_adj_mat(g);
    printf("Cycle path exists: %s\n", has_cycle(g) ? "yes" : "no");
    print_same_start_end_cycles(g);
    printf("\n");
}

static void make_cycle_graph(GraphType *g)
{
    graph_init(g);

    for (int i = 0; i < 6; i++) {
        insert_vertex(g, i);
    }

    insert_edge(g, 0, 1);
    insert_edge(g, 1, 2);
    insert_edge(g, 2, 0);
    insert_edge(g, 2, 3);
    insert_edge(g, 3, 4);
    insert_edge(g, 4, 5);
}

static void make_acyclic_graph(GraphType *g)
{
    graph_init(g);

    for (int i = 0; i < 6; i++) {
        insert_vertex(g, i);
    }

    insert_edge(g, 0, 1);
    insert_edge(g, 0, 2);
    insert_edge(g, 1, 3);
    insert_edge(g, 1, 4);
    insert_edge(g, 2, 5);
}

static void make_disconnected_cycle_graph(GraphType *g)
{
    graph_init(g);

    for (int i = 0; i < 6; i++) {
        insert_vertex(g, i);
    }

    insert_edge(g, 0, 1);
    insert_edge(g, 1, 2);

    insert_edge(g, 3, 4);
    insert_edge(g, 4, 5);
    insert_edge(g, 5, 3);
}

int main(void)
{
    GraphType g;

    make_cycle_graph(&g);
    print_result("Cycle Graph", &g);

    make_acyclic_graph(&g);
    print_result("Acyclic Graph", &g);

    make_disconnected_cycle_graph(&g);
    print_result("Disconnected Cycle Graph", &g);

    return 0;
}
