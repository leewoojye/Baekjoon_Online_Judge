#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <string>
#include <map>
using namespace std;
#define fastio ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

vector<int> discovered;
vector<bool> isCutVertex;
vector<vector<int>> list;
map<pair<int,int>, int> edgeList;
int counter=0;

int findCutVertex(int here, bool isRoot) {
  // 전위/후위 증감연산자는 변수값 자체도 변경시킴 counter+1을 쓰면 안됨.
  discovered[here]=counter++;
  int ret=discovered[here];
  int children=0;
  int uniqueChild; // here가 루트이며 자손이 1개일 경우 단절선정보를 구하기 위한 변수
  for(int i=0;i<list[here].size();++i) {
    int there=list[here][i];
    if(discovered[there]==-1) { // discovered 비교 조건문만으로 부모는 이미 방문된 상태로 걸러지므로 parent 변수를 따로 설정할 필요가 없음
      // 서브트리가 방문할수있는 최소방문정점을 반환
      ++children;
      int subTree=findCutVertex(there, false);  
      // 서브트리 중 하나라도 역방향간선이 없으면 절단점이 되므로 모든 서브트리에 대해 최소발견간선을 조사해야함.
      if(!isRoot && subTree>=discovered[here]) {
        isCutVertex[here]=true;
        if(subTree!=discovered[here]) {
          edgeList.erase({here,i});
          edgeList.erase({i,here});
        }
        // edgeList.erase({here,i});
        // edgeList.erase({i,here});
        ret=min(subTree, ret);
      }
      if(isRoot) uniqueChild=i;
    }
  //시작점이 루트인지는 어떻게 아나?
  // 시작점에선 처음부터 모든 자식을 탐색하므로 모든 시작점은 곧 루트라고 볼 수 있다.
  }
  if(isRoot) isCutVertex[here] = (children>=2);
  if(isRoot&&children==1) {
    edgeList.erase({here,uniqueChild});
    edgeList.erase({uniqueChild,here});
  }
  return ret;
}

int main() {
  fastio;
  int N;
  int e1,e2;
  cin >> N;
  list.resize(N+1);
  discovered.resize(N+1, -1);
  isCutVertex.resize(N+1, false);
  
  for(int i=0;i<N-1;++i) {
    cin >> e1 >> e2;
    list[e1].push_back(e2);
    list[e2].push_back(e1);
    edgeList.insert({{e1, e2}, i+1});
    edgeList.insert({{e2, e1}, i+1});
  }

  // 한 번의 dfs로 모든 정점의 단절점 여부를 조사
  int n=findCutVertex(1, true);
  
  int q;
  cin >> q;
  for(int i=0;i<q;++i) {
    int option, data;
    string s;
    cin >> option >> data;
    switch (option) {
    case 1:
        // 'isCutVertex[data]' 값을 기반으로 "yes" 또는 "no" 출력
        cout << (isCutVertex[data] ? "yes" : "no") << '\n';
        break;
    case 2: {
        // edgeList에서 data와 일치하는 간선이 있다는 건 단절선이 아니라는 뜻
        bool found = false;
        for (const auto& pair : edgeList) {
            if (pair.second == data) {
                cout << "no\n";
                found = true;
                break; 
            }
        }
        if (!found) { // switch-case문의 break는 case만 벗어날 뿐이므로 분기 처리를 추가로 해줌
            cout << "yes\n";
        }
        break;
    }
    default:
        break;  // option이 1이나 2가 아닌 경우 처리 안 함
    }
  }
  return 0;
}