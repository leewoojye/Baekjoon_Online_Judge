#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <queue>
using namespace std;
#define fastio ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

int dx[4]={1,0,-1,0};
int dy[4]={0,-1,0,1};

int main() {
  fastio;
  queue<pair<int,int>> q;
  int rotton=0, non=0;
  int N,M;
  cin >> M >> N;
  vector<vector<int>> box(N,vector<int>(M,-1));
  for(int n=0;n<N;++n) {
    for(int m=0;m<M;++m) {
      cin >> box[n][m];
      if(box[n][m]==1) { rotton++; q.push({n,m}); }
      if(box[n][m]==-1) non++;
    }
  }
  // 
  while(!q.empty()) {
    int nindex=q.front().first; int mindex=q.front().second;
    int nextn, nextm;
    for(int i=0;i<4;++i) {
      nextn=nindex+dx[i];
      nextm=mindex+dy[i];
      if(nextn<0 || nextm<0 || nextn>=N || nextm>=M || box[nextn][nextm]==1) continue;
      if(box[nextn][nextm]==0) { box[nextn][nextm]=1; rotton++; }
    }
    if(rotton+non==M*N) break;
  }
  if(rotton+non != M*N) { cout << -1 << '\n'; return 0; }
  return 0;
}