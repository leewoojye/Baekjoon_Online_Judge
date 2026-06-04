#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VERTEX 10

typedef struct GraphType {
  int adj_matrix[MAX_VERTEX][MAX_VERTEX]; // 인접 행렬
  int size;
} GraphType;

// 인접행렬 그래프를 빈 그래프로 초기화한다.
void graph_init(GraphType* g) {
  g->size = 0;
  memset(g->adj_matrix, 0, sizeof(g->adj_matrix));
}

// 그래프에 정점을 하나 추가한다.
void insert_vertex(GraphType* g, int v1) {
  g->size++;
}

// 무방향 그래프에 양방향 간선을 추가한다.
void insert_edge(GraphType* g, int e1, int e2) {
  g->adj_matrix[e1][e2]=1;
  g->adj_matrix[e2][e1]=1;
}

// 연결 그래프 예제 데이터를 만든다.
void make_connected_graph(GraphType* g)
{
graph_init(g);
for (int i = 0; i < 8; i++) insert_vertex(g, i); // 정점 8개

insert_edge(g, 0, 1);
insert_edge(g, 1, 2);
insert_edge(g, 2, 3);
insert_edge(g, 3, 4);
insert_edge(g, 4, 5);
insert_edge(g, 5, 6);
insert_edge(g, 6, 7);

// 추가 간선
insert_edge(g, 0, 2);
insert_edge(g, 2, 5);
insert_edge(g, 3, 6);
}

// 비연결 그래프 예제 데이터를 만든다.
void make_disconnected_graph(GraphType* g)
{
graph_init(g);
for (int i = 0; i < 8; i++) insert_vertex(g, i);

// 컴포넌트 1: 0-1-2-3
insert_edge(g, 0, 1);
insert_edge(g, 1, 2);
insert_edge(g, 2, 3);

// 컴포넌트 2: 4-5
insert_edge(g, 4, 5);

// 컴포넌트 3: 6-7
insert_edge(g, 6, 7);
}

int visited[MAX_VERTEX]={0}; // 정점의 방문 여부를 나타내는 배열, 0:방문되지 않음, 1:방문됨
int visit_sequence[MAX_VERTEX]={-1}; // 방문 순서 기록
int visit_idx=0;

// DFS로 방문 가능한 정점을 방문 순서 배열에 기록한다.
void DFS_search(GraphType *g, int node) {
  visited[node] = 1;
  visit_sequence[visit_idx++] = node;

  for(int next=0;next<g->size;next++) {
    // 정점가 이미 방문되었거나 연결되지 않은 노드라면 skip
    if(visited[next]==1 || g->adj_matrix[node][next]==0) { continue; }
    DFS_search(g, next);
  }
}

// 연결 그래프 예제를 각 시작 정점에서 테스트한다.
void test_connected(GraphType *g) {
  printf("==== 연결 그래프 테스트 ====\n\n");
  for (int i = 0; i < g->size; i++) {
    memset(visited, 0, sizeof(visited));
    memset(visit_sequence, -1, sizeof(visit_sequence));
    visit_idx = 0;

    printf("시작 정점 %d\n", i);
    printf("방문 순서: ");
    DFS_search(g, i);

    for (int j = 0; j < visit_idx; j++) {
      printf("정점 %d -> ", visit_sequence[j]);
    }
    printf("끝\n");
    
    // 각 시작점마다 연결성 판별
    if (visit_idx == g->size) {
      printf("결과: 연결그래프입니다.\n\n");
    } else {
      printf("결과: 비연결그래프입니다.\n\n");
    }
  }
  printf("\n\n");
}

// 비연결 그래프 예제를 각 시작 정점에서 테스트한다.
void test_disconnected(GraphType *g) {
  printf("==== 비연결 그래프 테스트 ====\n\n");
  for (int i = 0; i < g->size; i++) {
    memset(visited, 0, sizeof(visited));
    memset(visit_sequence, -1, sizeof(visit_sequence));
    visit_idx = 0;

    printf("시작 정점 %d\n", i);
    printf("방문 순서: ");
    DFS_search(g, i);

    for (int j = 0; j < visit_idx; j++) {
      printf("정점 %d -> ", visit_sequence[j]);
    }
    printf("끝\n");
    printf("결과: 비연결 그래프입니다.\n");
    printf("방문하지 않은 정점: ");
    for(int j=0; j<g->size; j++) {
      if(visited[j] == 0) {
        printf("%d ", j);
      }
    }
    printf("\n\n");
  }
  printf("\n\n");
}

// 연결 그래프와 비연결 그래프의 DFS 연결성 검사를 실행한다.
int main() {
  GraphType g_connected;
  GraphType g_disconnected;
  make_connected_graph(&g_connected);
  make_disconnected_graph(&g_disconnected);
  test_connected(&g_connected);
  test_disconnected(&g_disconnected);
  return 0;
}
