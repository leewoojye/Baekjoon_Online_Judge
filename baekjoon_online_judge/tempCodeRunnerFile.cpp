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
    if (node.second > 0 && !visited[node.second - 1]) {
      visited[node.second - 1] = true;
      q.push({node.first + 1, node.second - 1});
    }
    if (node.second < 100000 && !visited[node.second + 1]) {
      visited[node.second + 1] = true;
      q.push({node.first + 1, node.second + 1});
    }
    if (node.second*2 <= 100000 && node.second < K && !visited[node.second * 2]) {  // K 보다 작은 위치에서만 곱하기
      visited[node.second * 2] = true;
      q.push({node.first, node.second * 2});
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