#include <stdio.h>

#define MAX 8

typedef struct {
    int n;
    int adj_mat[MAX][MAX];
} GraphType;

static int visited[MAX];

// 인접행렬 그래프를 빈 다중 그래프로 초기화한다.
static void graph_init(GraphType *g)
{
    g->n = 0;
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            g->adj_mat[i][j] = 0;
        }
    }
}

// 그래프에 지정한 번호의 정점을 추가한다.
static void insert_vertex(GraphType *g, int v)
{
    if (v >= 0 && v < MAX && v >= g->n) {
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
    for (int i = 0; i < MAX; i++) {
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

// 연결 조건을 확인한다.
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

// 오일러 회로가 존재하는지 확인한다.
static int has_euler_circuit(GraphType *g)
{
    if (!is_connected_for_euler(g)) {
        return 0;
    }
    return count_odd_degree_vertices(g) == 0;
}

void print_edges(int edges[][2], int len) {
  for(int i=0;i<len;i++) {
    printf("(%d, %d) ",edges[i][0],edges[i][1]);
  }
  printf("\n");
}

int main(void)
{
    GraphType g1,g2,g3;
    graph_init(&g1);
    graph_init(&g2);
    graph_init(&g3);

    int edges1[][2] = {{0, 1}, {1, 2}, {2, 3}, {3, 4}, {4, 5}, {5, 0}};
    int edges2[][2] = {{0, 1}, {1, 2}, {2, 3}, {3, 4}, {4, 5}};
    int edges3[][2] = {{0, 1}, {1, 2}, {2, 0}, {3, 4}, {4, 5}, {5, 3}};

    for(int i=0;i<6;i++) {
      insert_vertex(&g1,i);
    }
    for(int i=0;i<6;i++) {
      insert_edge(&g1,edges1[i][0],edges1[i][1]);
    }
    printf("그래프 1 간선 ");
    print_edges(edges1,6);
    int result1=has_euler_circuit(&g1);
    if(result1) {
      printf("오일러 회로가 존재함.");
    }
    else {
      printf("오일러 회로가 존재하지 않음.");
    } 
    printf("\n");

    for(int i=0;i<6;i++) {
      insert_vertex(&g2,i);
    }
    for(int i=0;i<5;i++) {
      insert_edge(&g2,edges2[i][0],edges2[i][1]);
    }
    printf("그래프 2 간선 ");
    print_edges(edges2,5);
    int result2=has_euler_circuit(&g2);
    if(result2) {
      printf("오일러 회로가 존재함.");
    }
    else {
      printf("오일러 회로가 존재하지 않음.");
    }  
    printf("\n");

    for(int i=0;i<6;i++) {
      insert_vertex(&g3,i);
    }
    for(int i=0;i<6;i++) {
      insert_edge(&g3,edges3[i][0],edges3[i][1]);
    }
    printf("그래프 3 간선 ");
    print_edges(edges1,6);
    int result3=has_euler_circuit(&g3);
    if(result3) {
      printf("오일러 회로가 존재함.");
    }
    else {
      printf("오일러 회로가 존재하지 않음.");
    }  
    printf("\n");
    return 0;
}
