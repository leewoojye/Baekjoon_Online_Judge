#include <iostream>
#include <vector>
#include <algorithm>
#define fastio ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

vector<vector<int>> matrix;
vector<bool> visited;
vector<int> result;

void DAGSearch(int here) {
  for(int i=0;i<matrix[here].size();++i) {
    int there=matrix[here][i];
    if(!visited[there]) {
      visited[there]=true;
      DAGSearch(there);
    }
  }
  result.push_back(here);
  return;
}

int main() {
  fastio;
  int N,M;
  cin >> N >> M;
  matrix.resize(N+1);
  visited.resize(N+1, false);
  int e1,e2;
  for(int i=0;i<M;++i) {
    cin >> e1 >> e2;
    matrix[e1].push_back(e2);
  }
  for(int i=1;i<=N;++i) {
    if(!visited[i]) DAGSearch(i);
  }
  reverse(result.begin(), result.end());
  for(int i=0;i<N;++i) {
    if(i==N-1) cout << result[i];
    cout << result[i] << " ";
  }
  return 0;
}