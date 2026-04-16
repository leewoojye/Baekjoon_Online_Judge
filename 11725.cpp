#include <iostream>
#include <utility>
#include <vector>
using namespace std;
#define fastio ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

int main() {
  fastio;
  int N;
  cin >> N;
  vector<pair<int, int>> list(N-1);
  vector<bool> visited(N+1, false);
  vector<int> parent(N+1, 1);
  visited[1]=true;

  for(int i=0;i<N-1;++i) {
    cin >> list[i].first >> list[i].second;
  }
  for(auto& e : list) {
    if(visited[e.first] && !visited[e.second]) {
      parent[e.second]=e.first;
      visited[e.second]=true;
    } else {
      parent[e.first]=e.second;
      visited[e.first]=true;
    }
  }
  for(int i=2;i<=N;++i) {
    cout << parent[i] << '\n';
  }
  return 0;
}