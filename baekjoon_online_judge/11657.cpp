#include <iostream>
#include <vector>
#include <utility>
#include <climits>
using namespace std;
#define fastio ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

vector<vector<pair<int,int>>> list;
vector<int> upper;
int N,M;

int belmanford(int start) {
  bool updated;
  upper[start]=0;
  for(int i=0;i<N;++i) {
    updated=false;
    for(int j=1;j<=N;++j) {
      for(int k=0;k<list[j].size();++k) {
        int adj=list[j][k].first;
        int cost=list[j][k].second;
        if(upper[j] != INT_MAX && upper[j]+cost<upper[adj]) {
          upper[adj]=upper[j]+cost;
          updated=true;
        }
      }
    }
  }
  if(updated) return -1;
  return 0;
}

int main() {
  fastio;
  int v1,v2,w;
  cin >> N >> M;
  list.resize(N+1);
  upper.resize(N+1, INT_MAX);
  for(int i=0;i<M;++i) {
    cin >> v1 >> v2 >> w;
    list[v1].push_back({v2,w});
  }
  int result=belmanford(1);
  if(result==-1) {
    cout << -1;
    return 0;
  }
  for(int i=2;i<=N;++i) {
    if(upper[i]==INT_MAX) {
      cout << -1 << '\n';
      continue;
    }
    cout << upper[i] << '\n';
  }
  return 0;
}