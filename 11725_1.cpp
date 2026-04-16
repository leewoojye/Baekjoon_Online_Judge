#include <iostream>
#include <vector>
#include <queue>
using namespace std;
#define fastio ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

// 함수전달인자 대신 전역 변수를 이용하면 메모리 오버헤드를 줄일 수 있다.
// 오버헤드는 데이터 이외에 추가로 필요한 메모리로, 벡터로 말하면 리스트의 크기 등 내부상태를 뜻한다.
// 지역 변수는 함수호출시 약간의 스택 메모리를 사용할 수 있다.
vector<int> parents;
vector<bool> visited;

// 데이터복사가 아닌 참조를 사용(메모리차지비중을 낮추기위함)
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