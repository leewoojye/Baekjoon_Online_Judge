#include <iostream>
#include <vector>
#include <queue>
#include <utility>
using namespace std;
#define fastio ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

int dx[4]={0,-1,1,0};
int dy[4]={-1,0,0,1};

int main(int argc, const char** argv) {
  fastio;
  int N,M;
  cin >> N >> M;
  vector<vector<int>> arr(N,vector<int>(M,0));
  vector<vector<bool>> visited(N,vector<bool>(M,false));
  for(int i=0;i<N;++i) {
    for(int k=0;k<M;++k) {
      cin>>arr[i][k];
    }
  }
  // BFS
  int count=1;
  queue<pair<int,int>> q;
  q.push({0,0});
  visited[0][0] = true;
  while(!q.empty()) {
    pair<int,int> front=q.front();
    int frontx=front.first; int fronty=front.second;
    visited[frontx][fronty]=true;
    if(frontx==N-1 && fronty==M-1) break;
    q.pop();
    for(int i=0;i<4;++i) {
      if(frontx+dx[i]<0 || frontx+dx[i]>=N || fronty+dy[i]<0 || fronty+dy[i]>=M || arr[frontx+dx[i]][fronty+dy[i]] == 0) continue;
      if(visited[frontx+dx[i]][fronty+dy[i]]) continue;
      q.push({frontx+dx[i],fronty+dy[i]});
      visited[frontx+dx[i]][fronty+dy[i]]=true;
      count++;
    }
  }
  cout << count;
  return 0;
}