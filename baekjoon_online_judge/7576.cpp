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
  queue<pair<int,int>> q1,q2;
  int days=0;
  int rotton=0, non=0;
  int N,M;
  cin >> M >> N;
  int numBox=M*N;
  vector<vector<int>> box(N,vector<int>(M,-1));
  for(int n=0;n<N;++n) {
    for(int m=0;m<M;++m) {
      cin >> box[n][m];
      if(box[n][m]==1) { rotton++; q1.push({n,m}); }
      if(box[n][m]==-1) non++;
    }
  }

  if(rotton+non==numBox) { cout << 0 << '\n'; return 0; }
  while(!q1.empty()) {
    while(!q1.empty()) {
      int nindex=q1.front().first; int mindex=q1.front().second; q1.pop();
      int nextn, nextm;
      for(int i=0;i<4;++i) {
        nextn=nindex+dx[i];
        nextm=mindex+dy[i];
        if(nextn<0 || nextm<0 || nextn>=N || nextm>=M || box[nextn][nextm]==1) continue;
        if(box[nextn][nextm]==0) { box[nextn][nextm]=1; q2.push({nextn, nextm}); rotton++; }
      }
      if(rotton+non==numBox) { cout << days+1 << '\n'; return 0; }
    }
    days++;
    if(q2.empty()) break;
    while(!q2.empty()) {
      int nindex=q2.front().first; int mindex=q2.front().second; q2.pop();
      int nextn, nextm;
      for(int i=0;i<4;++i) {
        nextn=nindex+dx[i];
        nextm=mindex+dy[i];
        if(nextn<0 || nextm<0 || nextn>=N || nextm>=M || box[nextn][nextm]==1) continue;
        if(box[nextn][nextm]==0) { box[nextn][nextm]=1; q1.push({nextn, nextm}); rotton++; }
      }
      if(rotton+non==numBox) { cout << days+1 << '\n'; return 0; }
    }
    days++;
  }
  if(rotton+non != numBox) { cout << -1 << '\n'; return 0; }
  cout << days << '\n';
  return 0;
}