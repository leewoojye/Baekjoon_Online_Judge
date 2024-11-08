#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;
#define fastio ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

vector<int> discovered;
vector<bool> isCutVertex;
vector<vector<int>> list;
int counter=0;

int findCutVertex(int here, bool isRoot) {
  discovered[here]=counter+1;
  int ret=INT_MAX;
  for(int there=0;there<list[here][there];++there) {
    if(discovered[there]==-1) {
      // 서브트리가 방문할수있는 최소방문정점을 반환
      int subTree=findCutVertex(there, false);
      ret=min(subTree, ret);
    }
  }
  if(!isRoot && ret<=discovered[here]) {
    isCutVertex[here]=true;
  }
}

int main() {
  fastio;
  int N;
  int e1,e2;
  int q;
  cin >> N;
  list.resize(N+1);
  discovered.resize(N+1, -1);
  isCutVertex.resize(N+1, false);
  for(int i=0;i<N-1;++i) {
    cin >> e1 >> e2;
    list[e1].push_back(e2);
    list[e2].push_back(e1);
  }
  cin >> q;
  for(int i=0;i<q;++i) {
    int option, data;
    cin >> option >> data;
    switch (option)
    {
    case 1:
     cout << isCutVertex[data] << '\n'
     default;
    }
  }
  return 0;
}