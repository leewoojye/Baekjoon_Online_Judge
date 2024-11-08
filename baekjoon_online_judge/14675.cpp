#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <string>
using namespace std;
#define fastio ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

vector<int> discovered;
vector<bool> isCutVertex;
vector<vector<int>> list;
int counter=0;

int findCutVertex(int here, bool isRoot) {
  // 전위/후위 증감연산자는 변수값 자체도 변경시킴 counter+1을 쓰면 안됨.
  discovered[here]=counter++;
  int ret=discovered[here]+1;
  int children=0;
  for(int i=0;i<list[here].size();++i) {
    int there=list[here][i];
    if(discovered[there]==-1) {
      // 서브트리가 방문할수있는 최소방문정점을 반환
      ++children;
      int subTree=findCutVertex(there, false);  
      if(!isRoot && subTree>discovered[here]) {
        isCutVertex[here]=true;
      }
      ret=min(subTree, ret);
    }
  }
  //시작점이 루트인지는 어떻게 아나?
  // 시작점에선 처음부터 모든 자식을 탐색하므로 모든 시작점은 곧 루트라고 볼 수 있다.
  if(isRoot) isCutVertex[here] = (children>=2);
  return ret;
}

vector<bool> isCutBridge;
int counter1=0;
int findCutBridge(int here, bool isRoot) {

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
  isCutBridge.resize(N);
  for(int i=0;i<N-1;++i) {
    cin >> e1 >> e2;
    list[e1].push_back(e2);
    list[e2].push_back(e1);
  }

  // 한 번의 dfs로 모든 정점의 단절점 여부를 조사
  int n=findCutVertex(1, true);
  
  cin >> q;
  for(int i=0;i<q;++i) {
    int option, data;
    string s;
    cin >> option >> data;
    switch (option)
    {
    case 1:
    s=isCutVertex[data] ? "yes" : "no";
     cout << s << '\n';
     break;
     default:
     break;
    }
  }
  return 0;
}