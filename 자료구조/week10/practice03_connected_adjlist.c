#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 50

// 무방향 그래프, 인접리스트 표현
typedef struct LinkNode {
  struct LinkNode* link;
  int data;  
} LinkNode;

// adj list ver.
typedef struct GraphType {
  int n;
  LinkNode* list[MAX_VERTICES];
} GraphType;

// 인접리스트 그래프를 빈 그래프로 초기화한다.
void graph_init(GraphType *g)
{
  g->n = 0;
}

// 새 인접리스트 노드를 생성한다.
LinkNode* make_node(int item) {
  LinkNode* node=(LinkNode*)malloc(sizeof(LinkNode));
  node->data=item;
  node->link=NULL;
  return node;
}

// 그래프에 정점 헤더 노드를 추가한다.
void insert_vertex(GraphType *g, int v) {
  LinkNode* node=make_node(v);
  g->list[g->n++]=node;
}

// 무방향 그래프의 두 정점 인접리스트에 간선을 추가한다.
void insert_edge(GraphType *g, int v1, int v2) {
  // g->list[v1]
  LinkNode *node;
  LinkNode *node1=make_node(v1);
  LinkNode *node2=make_node(v2);
  for(node=g->list[v1];node->link!=NULL;node=node->link);
  node->link=node2; // 주의
  for(node=g->list[v2];node->link!=NULL;node=node->link);
  node->link=node1;
}

int visited[MAX_VERTICES]={0};
// DFS로 시작 정점에서 방문 가능한 정점을 표시한다.
void dfs_search(GraphType *g, int v) { // 시작점 v
  LinkNode* node=g->list[v]->link;
  if(node==NULL) return;
  for(;node!=NULL;node=node->link) {
    if(visited[node->data]) continue;
    visited[node->data]=1;
    dfs_search(g, node->data);
  }
}

// DFS 방문 결과로 그래프 전체가 연결되어 있는지 확인한다.
int check_connection(GraphType *g) {
  visited[0] = 1; // 호출부에서 시작점 방문처리 및 dfs 탐색호출 잊지 말기
  dfs_search(g,0);
  for(int i=0;i<g->n;i++) {
    if(!visited[i]) return 0;
  }
  return 1;
}

// 연결 그래프 예제 데이터를 만든다.
void make_connected_graph(GraphType* g)
{
  graph_init(g);
  for (int i = 0; i < 8; i++) insert_vertex(g, i);
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

// 인접리스트 그래프의 연결 여부를 출력한다.
int main() {
  GraphType g;
  make_disconnected_graph(&g);
  // make_connected_graph(&g);
  int result=check_connection(&g);
  printf("connected? %d\n",result);
  return 0;
}
