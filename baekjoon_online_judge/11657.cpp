#include <iostream>
#include <vector>
#include <utility>
#include <climits>
using namespace std;
#define fastio ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

vector<vector<pair<int,int>>> list;
vector<int> upper;
int N,M;

void belmanford(int start) {
  bool updated;
  for(int i=0;i<N;++i) {
    updated=false;
    for(int j=1;j<=N;++j) {
      int here=
      for(int k=0;k<list[j].size();++k) {
        int adj=list[j][k].first;
        int cost=list[j][k].second;
        if(upper[<upper[adj])
      }
    }
  }
  return;
}

int main() {
  fastio;
  int v1,v2,w;
  cin >> N >> M;
  list.resize(N+1);
  upper.resize(N+1);
  for(int i=0;i<M;++i) {
    cin >> v1 >> v2 >> w;
    list[v1].push_back({v2,w});
  }
  return 0;
}