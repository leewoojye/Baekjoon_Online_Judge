#include <iostream>
#include <vector>
#include <queue>
using namespace std;
#define fastio ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

vector<int> parents;
vector<bool> visited;

void insertBFS(int N, vector<vector<bool>>& matrix) {
  // vector 크기와 초기값을 동시에 재설정 : assign()
  visited.assign(N+1, false);
  parents.assign(N+1, 0);
  queue<int> q;
  q.push(1);
  while(!q.empty()) {
    int front=q.front();
    for(int i=1;i<=N;++i) {
      if(matrix[front][i] && !visited[i]) {
        q.push(i);
        parents[i]=front;
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
  vector<vector<bool>> matrix(N+1, vector<bool>(N+1, false));
  for(int i=0;i<N-1;++i) {
    cin >> node1 >> node2;
    matrix[node1][node2]=true;
    matrix[node2][node1]=true;
  }
  insertBFS(N, matrix);
  for(int i=2;i<=N;++i) {
    cout << parents[i] << '\n';
  }
  return 0;
}