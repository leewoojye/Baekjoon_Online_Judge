#include <iostream>
#include <vector>
#include <queue>
#include <utility>
using namespace std;
#define fastio ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

vector<int> parents;
vector<bool> visited;

void insertBFS(int N, vector<vector<int>>& matrix) {
  visited.assign(N+1, false);
  parents.assign(N+1, 0);
  queue<int> q;
  q.push(1);
  while(!q.empty()) {
    int front=q.front();
    for(int i=0;i<matrix[front].size();++i) {
      if(!visited[matrix[front][i]]) {
        q.push(matrix[front][i]);
        parents[matrix[front][i]]=front;
      }
    }
    visited[front]=true;
    q.pop();
  }
  return;
}

int main() {
  fastio;
  int N;
  int node1, node2;
  cin >> N;
  vector<vector<int>> matrix(N+1);
  for(int i=1;i<=N-1;++i) {
    cin >> node1 >> node2;
    matrix[node1].push_back(node2);
    matrix[node2].push_back(node1);
  }
  insertBFS(N, matrix);
  for(int i=2;i<=N;++i) {
    cout << parents[i] << '\n';
  }
  return 0;
}