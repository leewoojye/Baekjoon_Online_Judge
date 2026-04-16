#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <algorithm>
#include <string>
using namespace std;
#define fastio ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

vector<vector<int>> maze;
// vector<bool> visited;
// priority_queue<pair<int,pair<int,int>>> pq;
int N,M;
int best=987654321;
int dx[4]={1,0,-1,0};
int dy[4]={0,1,0,-1};

// maze속 정점방문여부 vi, 지금까지 부순 벽수 broken, 현재좌표 x,y
void searchMaze(__int128 vi, int broken, int x, int y) {
  if(x==N && y==M) { best=min(best,broken); return; }
  // if(best<broken+N+M-x-y+1) return; // pruning
  if(best<broken) return;
  int nextx;
  int nexty;
  for(int i=0;i<4;++i) {
    nextx=x+dx[i];
    nexty=y+dy[i];
    if(nextx<1 || nextx>N || nexty<1 || nexty>M) continue;
    if(vi & 1<<(nexty*N+nextx)) continue;
    if(maze[nextx][nexty]==1) {
      searchMaze(vi | 1<<(nexty*N+nextx), broken+1, nextx, nexty);
    } else {
      searchMaze(vi | 1<<(nexty*N+nextx), broken, nextx, nexty);
    }
  }
  return;
}

int main() {
  fastio;
  cin >> N >> M;
  maze.resize(N+1,vector<int>(M+1));
  // visited.resize(N*M,false);
  string s;
  for(int m=1;m<=M;++m) {
    cin >> s;
    for(int n=1;n<=N;++n) {
      s[n-1]=='0' ? maze[n][m]=0 : maze[n][m]=1;
    }
  }
  __int128 vi=0;
  searchMaze(vi,0,1,1);
  cout << best;
  return 0;
}