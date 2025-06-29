#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <string>
using namespace std;
#define fastio ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

int dx[4]={0,-1,1,0};
int dy[4]={-1,0,0,1};

int main(int argc, const char** argv) {
  fastio;
  int N,M;
  cin >> N >> M;
  vector<vector<int>> maze(N,vector<int>(M,0)); // 입력 미로 매트릭스
  vector<vector<bool>> visited(N,vector<bool>(M,false)); // 미로상 각 좌표 방문 여부
  vector<vector<int>> shortest(N,vector<int>(M,987654321)); // 미로상 각 좌표 방문 여부
  for(int i=0;i<N;++i) {
    string line;
    cin >> line;
    for(int k=0;k<M;++k) {
      maze[i][k]=line[k]-'0';
    }
  }
  // BFS
  int count=1;
  bool flag=false;
  queue<pair<int,int>> q;
  q.push({0,0});
  visited[0][0] = true;
  shortest[0][0]=1;
  while(!q.empty()) {
    pair<int,int> front=q.front(); q.pop();
    int frontx=front.first; int fronty=front.second;
    if(frontx==N-1 && fronty==M-1) break;
    int nextx,nexty;
    for(int i=0;i<4;++i) {
      nextx=frontx+dx[i];
      nexty=fronty+dy[i];
      if(nextx<0 || nextx>=N || nexty<0 || nexty>=M || maze[nextx][nexty] == 0) continue;
      if(visited[nextx][nexty]) continue;
      shortest[nextx][nexty]=shortest[frontx][fronty]+1;
      q.push({nextx,nexty});
      visited[nextx][nexty]=true;
    }
  }
  cout << shortest[N-1][M-1] << '\n';
  return 0;
}