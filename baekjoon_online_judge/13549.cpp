#include <iostream>
#include <vector>
#include <queue>
#include <utility>
using namespace std;
#define fastio ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

int searchBFS(int start, int K) {
  priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;
  vector<bool> visited(100001, false);  // 0 ~ 100000까지 방문 여부 체크
  q.push({0, start});
  visited[start] = true;
  while (!q.empty()) {
    pair<int, int> node = q.top();
    q.pop();
    if (node.second == K) {
      return node.first;
    }
    // 세 가지 경우를 큐에 넣을 때, 방문하지 않았으면 큐에 넣음
    // N=1 K=2 케이스에 유의할 것
    // 걷는 것보다 순간이동 조건문을 먼저 통과시키는데 1 2 케이스에서 걷는 경우가 먼저 탐색될 경우 순간이동 선택지는 visited에 막혀 탐색되지 않기 때문이다.
    if (node.second*2 <= 100000 && node.second < K && !visited[node.second * 2]) {  // K 보다 작은 위치에서만 곱하기
      visited[node.second * 2] = true;
      q.push({node.first, node.second * 2});
    }
    if (node.second > 0 && !visited[node.second - 1]) {
      visited[node.second - 1] = true;
      q.push({node.first + 1, node.second - 1});
    }
    if (node.second < 100000 && !visited[node.second + 1]) {
      visited[node.second + 1] = true;
      q.push({node.first + 1, node.second + 1});
    }
  }
  return 0;
}

int main() {
  fastio;
  int N,K;
  cin >> N >> K;
  cout << searchBFS(N,K);
  return 0;
}