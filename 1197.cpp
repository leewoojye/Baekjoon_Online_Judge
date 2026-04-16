#include <iostream>
#include <vector>
#include <climits>
#include <utility>
using namespace std;
#define fastio ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

// 프림 최소 스패닝 트리
int main() {
  fastio;
  int V,E;
  cin >> V >> E;
  vector<vector<pair<int,int>>> adj(V+1);
  vector<bool> added(V+1, false);
  int INF=INT_MAX;
  int v1,v2,w;
  for(int i=0;i<E;++i) {
    cin >> v1 >> v2 >> w;
    adj[v1].push_back({v2, w});
    adj[v2].push_back({v1, w});
  }
  int ret=0; // 가중치 합
  vector<int> minWeight(V+1, INF); // 현재 트리에서 해당 정점까지의 최소거리
  minWeight[1]=0;
  for (int k=0;k<V;++k) {
    int u=-1;
    for(int i=1;i<=V;++i) {
      if(!added[i] && (u==-1 || minWeight[u]>minWeight[i])) u=i;
    }
    ret+=minWeight[u];
    added[u]=true;
    for(int i=0;i<adj[u].size();++i) {
      int next=adj[u][i].first; int cost=adj[u][i].second;
      if(!added[next] && minWeight[next]>cost) {
        minWeight[next]=cost;
      }
    }
  }
  cout << ret << '\n';
  return 0;
}