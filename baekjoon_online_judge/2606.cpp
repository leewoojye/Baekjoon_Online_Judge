#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
#define fastio ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

vector<int> parent(101,0);
int numVertex[101]; // 한 그룹에 속한 정점의 수
  // for(int i = 0; i < 101; ++i) {
  //   numVertex[i] = 1;
  // } // 메인함수 밖에선 선언만 가능

int find(int u) {
  if(parent[u]==u) return u;
  return find(parent[u]);
}

void merge(int u, int v) {
  int uparent=find(u);
  int vparent=find(v);
  if(uparent!=vparent) {
    parent[uparent]=parent[vparent];
    numVertex[vparent]+=numVertex[uparent];
  }
  return;
}

// 상호배타집합
int main() {
  fastio;
  int numComputer;
  int pairs;
  cin >> numComputer;
  for(int i=1;i<101;++i) {
    parent[i]=i;
  }
  for(int i = 0; i < 101; ++i) {
    numVertex[i] = 1;
  } // 메인함수 밖에선 선언만 가능
  // 인접리스트 표현
  vector<vector<int>> adj(101);
  cin >> pairs;
  int v1,v2;
  for(int p=0;p<pairs;++p) {
    cin >> v1 >> v2;
    adj[v1].push_back(v2);
    adj[v2].push_back(v1);
    merge(v1,v2);
  }
  int result=numVertex[find(1)];
  cout << result-1 << '\n';
  return 0;
}