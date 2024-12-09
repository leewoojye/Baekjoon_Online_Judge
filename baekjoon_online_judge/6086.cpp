#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>
using namespace std;
#define fastio ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

int main() {
  fastio;
  int E;
  cin >> E;
  // 잔여용량이랑 유량 같은 배열로 쓰기
  vector<vector<int>> flow(26, vector<int>(26, INT_MAX));
  // flow[0][0]=0;

  char c1,c2;
  int f;
  for(int i=0;i<E;++i) {
    cin >> c1 >> c2 >> f;
    flow[c1-65][c2-65]=f;
    // flow[c2-65][c1-65]=f;
  }
  int ret=0;
  while(true) {
    vector<int> parent(26, -1);
    parent[0]=0;
    queue<int> q;
    q.push(0);
    int amount=0;
    while(!q.empty()) {
      int front=q.front(); q.pop();
      int minNode=0;
      for(int i=0;i<26;++i) {
        if(flow[front][i]!=INT_MAX && flow[front][i]<flow[front][minNode]) {
          minNode=i;
          amount=flow[front][i];
        }
      }
      parent[minNode]=front;
      if(parent[25]!=-1) break;
    }
    if(parent[25]==-1) break;
    for(int p=25;parent[p]!=0;p=parent[p]) {
      // flow[p][parent[p]]-=amount;
      flow[parent[p]][p]-=amount;
    }
    ret+=amount;
  }
  cout << ret << '\n';
  return 0;
}