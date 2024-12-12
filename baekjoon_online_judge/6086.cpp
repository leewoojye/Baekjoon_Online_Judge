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
  vector<vector<int>> flow(26, vector<int>(26, 0));
  flow[0][0]=0;

  char c1,c2;
  int f;
  for(int i=0;i<E;++i) {
    cin >> c1 >> c2 >> f;
    flow[c1-65][c2-65]=f;
    flow[c2-65][c1-65]=f;
  }
  int ret=0;
  while(true) {
    vector<bool> visited(26, false);
    vector<int> parent(26, -1);
    parent[0]=0;
    visited[0]=true;
    queue<int> q;
    q.push(0);
    // int amount=INT_MAX;
    // BFS
    while(!q.empty() && parent[25]==-1) {
      int front=q.front(); q.pop();
      visited[front]=true;
      int minNode=0;
      for(int i=0;i<26;++i) {
        if(!visited[i] && flow[front][i]>0) {
          // if(flow[front][i]<flow[front][minNode]) minNode=i; 
          // amount=min(amount,flow[front][i]);
          parent[i]=front;
          q.push(i);
        }
      }
    }
    if(parent[25]==-1) break;
    int amount=INT_MAX;
    for(int p=25;p!=0;p=parent[p]) {
      amount=min(amount,flow[parent[p]][p]);
    }
    for(int p=25;p!=0;p=parent[p]) {
      flow[p][parent[p]]+=amount;
      flow[parent[p]][p]-=amount;
    }
    ret+=amount;
  }
  cout << ret << '\n';
  return 0;
}