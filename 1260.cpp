#include <iostream>
#include <vector>
#include <queue>
using namespace std;
queue<int> q;

void DFS(int here, vector<bool>& visited, vector<vector<int>>& matrix) {
    cout << here << ' ';
    visited[here]=true;
    for(int j=1;j<=visited.size();++j) {
      if(matrix[here][j]!=0 && !visited[j]){
        int there=j;
        matrix[here][j]--;
        matrix[j][here]--;
        visited[j]=true;
        DFS(j, visited, matrix);
      }
    }
}

void BFS(int here, vector<bool>& visited, vector<vector<int>>& matrix) {
    visited[here]=true;
    q.push(here);
    while(!q.empty()) {
        int front=q.front();
        for(int i=1;i<=visited.size();++i) {
            if(matrix[front][i]!=0 && !visited[i]) {
                q.push(i);
                matrix[front][i]--;
                matrix[i][front]--;
                visited[i]=true;
            }
        }
        cout << q.front() << ' ';
        q.pop();
    }
}

int main() {
  int N,M,V;
  cin >> N >> M >> V;
  vector<bool> visited(N, false);
  // vector 크기를 N으로 설정해도, index는 0~N-1이다.
  // 즉 정점 개수 N에 대해 matrix[정점번호]로 표현하려면 N+1 X N+1 행렬이 필요하다.
  vector<vector<int>> matrix(N+1, vector<int>(N+1, 0));
  int n1, n2;
  for(int i=0;i<M;++i) {
    cin >> n1 >> n2;
    matrix[n1][n2]++;
    matrix[n2][n1]++;
  }
  vector<bool> visitedcopy=visited;
  vector<vector<int>> matrixcopy=matrix;
  DFS(V,visited, matrix);
  cout << endl;
  BFS(V,visitedcopy,matrixcopy);
  
  return 0;
}