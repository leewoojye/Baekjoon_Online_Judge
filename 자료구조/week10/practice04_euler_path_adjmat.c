#include <stdio.h>

#define MAX_VERTICES 8

typedef struct {
    int n;
    int adj_mat[MAX_VERTICES][MAX_VERTICES];
} GraphType;

static int visited[MAX_VERTICES];

// 인접행렬 그래프를 빈 다중 그래프로 초기화한다.
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

// 무방향 다중 그래프에 간선을 하나 추가한다.
static void insert_edge(GraphType *g, int u, int v)
{
    if (u < 0 || v < 0 || u >= g->n || v >= g->n) {
        return;
    }
    g->adj_mat[u][v]++;
    g->adj_mat[v][u]++;
}

// 방문 배열을 모두 미방문 상태로 초기화한다.
static void clear_visited(void)
{
    for (int i = 0; i < MAX_VERTICES; i++) {
        visited[i] = 0;
    }
}

// 정점의 차수를 계산한다.
static int degree(GraphType *g, int v)
{
    int count = 0;

    for (int i = 0; i < g->n; i++) {
        if (i == v) {
            count += g->adj_mat[v][i] * 2;
        } else {
            count += g->adj_mat[v][i];
        }
    }
    return count;
}

// 간선을 가진 첫 번째 정점을 찾는다.
static int first_vertex_with_edge(GraphType *g)
{
    for (int i = 0; i < g->n; i++) {
        if (degree(g, i) > 0) {
            return i;
        }
    }
    return -1;
}

// DFS로 간선이 있는 연결 요소를 방문한다.
static void dfs(GraphType *g, int v)
{
    visited[v] = 1;

    for (int w = 0; w < g->n; w++) {
        if (g->adj_mat[v][w] > 0 && !visited[w]) {
            dfs(g, w);
        }
    }
}

// 오일러 판별에 필요한 연결 조건을 확인한다.
static int is_connected_for_euler(GraphType *g)
{
    int start = first_vertex_with_edge(g);

    if (start == -1) {
        return 1;
    }

    clear_visited();
    dfs(g, start);

    for (int i = 0; i < g->n; i++) {
        if (degree(g, i) > 0 && !visited[i]) {
            return 0;
        }
    }
    return 1;
}

// 홀수 차수 정점의 개수를 센다.
static int count_odd_degree_vertices(GraphType *g)
{
    int odd_count = 0;

    for (int i = 0; i < g->n; i++) {
        if (degree(g, i) % 2 != 0) {
            odd_count++;
        }
    }
    return odd_count;
}

// 오일러 경로가 존재하는지 확인한다.
static int has_euler_path(GraphType *g)
{
    int odd_count;

    if (!is_connected_for_euler(g)) {
        return 0;
    }

    odd_count = count_odd_degree_vertices(g);
    return odd_count == 0 || odd_count == 2;
}

// 오일러 회로가 존재하는지 확인한다.
static int has_euler_circuit(GraphType *g)
{
    if (!is_connected_for_euler(g)) {
        return 0;
    }
    return count_odd_degree_vertices(g) == 0;
}

// 각 정점의 차수를 출력한다.
static void print_degrees(GraphType *g)
{
    printf("Degree: ");
    for (int i = 0; i < g->n; i++) {
        printf("%c=%d", 'A' + i, degree(g, i));
        if (i + 1 < g->n) {
            printf(", ");
        }
    }
    printf("\n");
}

// 홀수 차수 정점들을 출력한다.
static void print_odd_vertices(GraphType *g)
{
    int found = 0;

    printf("Odd degree vertices: ");
    for (int i = 0; i < g->n; i++) {
        if (degree(g, i) % 2 != 0) {
            printf("%c ", 'A' + i);
            found = 1;
        }
    }
    if (!found) {
        printf("none");
    }
    printf("\n");
}

// 그래프의 오일러 경로와 회로 판별 결과를 출력한다.
static void print_result(const char *title, GraphType *g)
{
    printf("===== %s =====\n", title);
    print_degrees(g);
    print_odd_vertices(g);
    printf("Connected for Euler check: %s\n",
           is_connected_for_euler(g) ? "yes" : "no");
    printf("Euler path exists: %s\n",
           has_euler_path(g) ? "yes" : "no");
    printf("Euler circuit exists: %s\n",
           has_euler_circuit(g) ? "yes" : "no");
    printf("\n");
}

// 쾨니히스베르크 다리 그래프 예제를 만든다.
static void make_konigsberg_graph(GraphType *g)
{
    graph_init(g);

    for (int i = 0; i < 4; i++) {
        insert_vertex(g, i);
    }

    insert_edge(g, 0, 1);
    insert_edge(g, 0, 1);
    insert_edge(g, 0, 2);
    insert_edge(g, 0, 2);
    insert_edge(g, 0, 3);
    insert_edge(g, 1, 3);
    insert_edge(g, 2, 3);
}

// 오일러 경로만 존재하는 예제 그래프를 만든다.
static void make_euler_path_graph(GraphType *g)
{
    graph_init(g);

    for (int i = 0; i < 4; i++) {
        insert_vertex(g, i);
    }

    insert_edge(g, 0, 1);
    insert_edge(g, 1, 2);
    insert_edge(g, 2, 0);
    insert_edge(g, 2, 3);
}

// 오일러 회로가 존재하는 예제 그래프를 만든다.
static void make_euler_circuit_graph(GraphType *g)
{
    graph_init(g);

    for (int i = 0; i < 4; i++) {
        insert_vertex(g, i);
    }

    insert_edge(g, 0, 1);
    insert_edge(g, 1, 2);
    insert_edge(g, 2, 3);
    insert_edge(g, 3, 0);
}

// 세 가지 그래프의 오일러 경로 존재 여부를 테스트한다.
int main(void)
{
    GraphType g;

    make_konigsberg_graph(&g);
    print_result("Konigsberg Bridge Graph", &g);

    make_euler_path_graph(&g);
    print_result("Euler Path Graph", &g);

    make_euler_circuit_graph(&g);
    print_result("Euler Circuit Graph", &g);

    return 0;
}
