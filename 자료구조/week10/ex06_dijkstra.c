#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 50
#define INF 1000000
#define TRUE 1
#define FALSE 0

typedef struct GraphType {
    int n;
    int weight[MAX_VERTICES][MAX_VERTICES];
} GraphType;

static int distance[MAX_VERTICES];
static int selected[MAX_VERTICES];
static int previous[MAX_VERTICES];

static void graph_init(GraphType *g)
{
    g->n = 0;
    for (int i = 0; i < MAX_VERTICES; i++) {
        for (int j = 0; j < MAX_VERTICES; j++) {
            if (i == j) {
                g->weight[i][j] = 0;
            } else {
                g->weight[i][j] = INF;
            }
        }
    }
}

static void insert_vertex(GraphType *g, int v)
{
    (void)v;
    if (g->n + 1 > MAX_VERTICES) {
        fprintf(stderr, "too many vertices\n");
        return;
    }
    g->n++;
}

static void insert_edge(GraphType *g, int start, int end, int weight)
{
    if (start >= g->n || end >= g->n || start < 0 || end < 0) {
        fprintf(stderr, "invalid vertex number\n");
        return;
    }
    if (weight < 0) {
        fprintf(stderr, "dijkstra cannot use negative weight\n");
        return;
    }
    g->weight[start][end] = weight;
    g->weight[end][start] = weight;
}

static int choose(GraphType *g)
{
    int min = INF;
    int minpos = -1;

    for (int i = 0; i < g->n; i++) {
        if (!selected[i] && distance[i] < min) {
            min = distance[i];
            minpos = i;
        }
    }
    return minpos;
}

static void print_status(GraphType *g)
{
    printf("distance: ");
    for (int i = 0; i < g->n; i++) {
        if (distance[i] == INF) {
            printf("%4s", "*");
        } else {
            printf("%4d", distance[i]);
        }
    }
    printf("\n");
}

static void dijkstra(GraphType *g, int start)
{
    int u;

    for (int i = 0; i < g->n; i++) {
        distance[i] = g->weight[start][i];
        selected[i] = FALSE;
        if (g->weight[start][i] != INF && i != start) {
            previous[i] = start;
        } else {
            previous[i] = -1;
        }
    }
    distance[start] = 0;
    previous[start] = -1;
    selected[start] = TRUE;

    printf("start vertex: %d\n", start);
    print_status(g);

    for (int i = 0; i < g->n - 1; i++) {
        u = choose(g);
        if (u == -1) {
            break;
        }
        selected[u] = TRUE;

        for (int w = 0; w < g->n; w++) {
            if (!selected[w] && g->weight[u][w] != INF &&
                distance[u] + g->weight[u][w] < distance[w]) {
                distance[w] = distance[u] + g->weight[u][w];
                previous[w] = u;
            }
        }
        print_status(g);
    }
}

static void print_path(int start, int end)
{
    if (end == start) {
        printf("%d", start);
        return;
    }
    if (previous[end] == -1) {
        printf("no path");
        return;
    }
    print_path(start, previous[end]);
    printf(" -> %d", end);
}

static void print_shortest_paths(GraphType *g, int start)
{
    for (int i = 0; i < g->n; i++) {
        printf("%d to %d: ", start, i);
        if (distance[i] == INF) {
            printf("no path\n");
        } else {
            printf("distance=%d, path=", distance[i]);
            print_path(start, i);
            printf("\n");
        }
    }
}

int main(void)
{
    GraphType *g = (GraphType *)malloc(sizeof(GraphType));

    if (g == NULL) {
        fprintf(stderr, "allocation failed\n");
        return 1;
    }

    graph_init(g);
    for (int i = 0; i < 7; i++) {
        insert_vertex(g, i);
    }

    insert_edge(g, 0, 1, 7);
    insert_edge(g, 0, 4, 3);
    insert_edge(g, 0, 5, 10);
    insert_edge(g, 1, 2, 4);
    insert_edge(g, 1, 3, 10);
    insert_edge(g, 1, 4, 2);
    insert_edge(g, 2, 3, 2);
    insert_edge(g, 3, 4, 11);
    insert_edge(g, 3, 6, 4);
    insert_edge(g, 4, 5, 13);
    insert_edge(g, 4, 6, 5);
    insert_edge(g, 5, 6, 6);

    dijkstra(g, 0);
    printf("\n");
    print_shortest_paths(g, 0);

    free(g);
    return 0;
}
