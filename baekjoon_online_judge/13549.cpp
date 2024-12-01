#include <iostream>
#include <vector>
#include <queue>
#include <utility>
using namespace std;
#define fastio ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

int searchBFS(int start, int K) {
  queue<pair<int,int>> q;
  // 노드의깊이(걸린시간) - 노드의 값(수빈이의 현재위치)
  q.push({0,start});
  while(!q.empty()) {
    pair<int,int> node=q.front();
    q.pop();
    if(node.second==K) {
      return node.first;
    }
    if(node.second>0) q.push({node.first+1,node.second-1});
    q.push({node.first+1,node.second+1});
    q.push({node.first,node.second*2});
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