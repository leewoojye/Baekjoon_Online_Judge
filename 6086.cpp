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
  vector<vector<int>> flow(52, vector<int>(52, 0));
  flow[0][0]=0;
  char c1,c2;
  int i1,i2;
  int f;
  for(int i=0;i<E;++i) {
    cin >> c1 >> c2 >> f;
    if(c1 >= 'a' && c1 <= 'z') i1=c1-'a'+26;
    if(c2 >= 'a' && c2 <= 'z') i2=c2-'a'+26;
    if(c1 >= 'A' && c1 <= 'Z') i1=c1-'A';
    if(c2 >= 'A' && c2 <= 'Z') i2=c2-'A';
    flow[i1][i2] += f;
    flow[i2][i1] += f;
  }
  int ret=0;
  while(true) {
    vector<bool> visited(52, false);
    vector<int> parent(52, -1);
    parent[0]=0;
    visited[0]=true;
    queue<int> q;
    q.push(0);
    // BFS, 아무탐색으로 찾은 경로도 증가경로가 되는이유는?
    while(!q.empty() && parent[25]==-1) {
      int front=q.front(); q.pop();
      visited[front]=true;
      for(int i=0;i<52;++i) {
        if(!visited[i] && flow[front][i]>0) {
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