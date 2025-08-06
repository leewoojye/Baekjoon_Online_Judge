#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
using namespace std;
#define fastio ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

// vector<vector<pair<int,int>>> adjList;
vector<Node> nodeList;
struct Node
{
  vector<pair<int,int>> children; // 자손번호,가중치 쌍
};

int main() {
  fastio;
  int N;
  cin >> N;
  nodeList.resize(N+1);
  int parent, child, weight;
  // 트리 생성
  for(int i=0;i<N-1;++i) {
    cin >> parent >> child >> weight;
    // 구조체 동적, 정적 할당 방식
    Node n;
    n.children.push_back({child,weight});
    nodeList[parent]=n; // 벡터에 구조체 복사본 저장, 원본은 반복턴 바뀔때 소멸
  }

  return 0;
}

/*
1. 루트노드에서 양자손 각각 깊이우선탐색 -> 제일 긴 경로값 두개 추출
2-1. 두 경로가 한 자식에 몰림 -> 해당 자식을 입력으로 해 재귀호출
2-2. 두 경로가 분산 -> 두 경로를 더한 게 결과

1. 각 노드에 대해 연결된 이웃노드를 깊이우선탐색 -> 제일 긴 두 경로 이은 값으로 지름 갱신
*/