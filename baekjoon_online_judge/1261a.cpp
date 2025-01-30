#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <algorithm>
#include <string>
using namespace std;
#define fastio ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

vector<vector<int>> maze;
int N,M;
int best=987654321;
int dx[4]={1,0,-1,0};
int dy[4]={0,1,0,-1};

struct state {
  __int128 vi;
  int x,y;
  int broken;
  state(__int128 vP, int xP, int yP, int bP) : vi(vP),x(xP),y(yP),broken(bP) {}
  bool operator<(const state& other) const {
    if(broken==other.broken) return (x+y) < (other.x+other.y);
    return broken > other.broken; 
  }
  bool operator==(const state& other) const {
    return x == other.x && y == other.y;
  }
};

// void removeDuplicates(priority_queue<state>& pq) {
//     vector<state> temp;  // 큐의 원소들을 임시로 저장할 벡터
//     while (!pq.empty()) {
//         state current = pq.top();
//         pq.pop();
//         bool duplicateFound = false;
//         // 벡터에서 이미 존재하는 원소와 비교
//         for (const state& task : temp) {
//             if (task == current) {
//                 duplicateFound = true;
//                 if(task.broken<current.broken) {
//                   temp.push_back(task);
//                 } else {
//                   temp.push_back(current);
//                 }
//                 break;
//             }
//         }
//         if (!duplicateFound) {
//             temp.push_back(current);  // 중복이 아니면 임시 벡터에 추가
//             continue;
//         }
//     }
//     for (const state& task : temp) {
//         pq.push(task);
//     }
// }

int main() {
  fastio;
  cin >> N >> M;

  vector<vector<state>> stateMap;
  state zeroState(0,0,0,987654321);
  stateMap.resize(N+1,vector<state>(M+1, zeroState));

  maze.resize(N+1,vector<int>(M+1));
  string s;
  for(int m=1;m<=M;++m) {
    cin >> s;
    for(int n=1;n<=N;++n) {
      s[n-1]=='0' ? maze[n][m]=0 : maze[n][m]=1;
    }
  }
  priority_queue<state> pq;
  state start(0,1,1,0);
  pq.push(start);
  int nextx;
  int nexty;
  while(!pq.empty()) {
    state front=pq.top(); pq.pop();
    if(front.x==N && front.y==M) { 
      if(front.broken==0) break;
      best=min(best,front.broken); continue; 
    }
    if(front.broken>best) continue; // pruning
    for(int i=0;i<4;++i) {
      nextx=front.x+dx[i];
      nexty=front.y+dy[i];
      if(nextx<1 || nextx>N || nexty<1 || nexty>M) continue;
      if(front.vi & 1<<(nexty*N+nextx)) continue;
      if(maze[nextx][nexty]==1) {
        state newState(front.vi | 1<<(nexty*N+nextx),nextx,nexty,front.broken+1);
        if(newState.broken<=stateMap[nextx][nexty].broken) { 
          if(newState.broken<stateMap[nextx][nexty].broken) stateMap[nextx][nexty]=newState;
          pq.push(newState);
        };
      } else {
        state newState(front.vi | 1<<(nexty*N+nextx),nextx,nexty,front.broken);
        if(newState.broken<=stateMap[nextx][nexty].broken) { 
          if(newState.broken<stateMap[nextx][nexty].broken) stateMap[nextx][nexty]=newState;
          pq.push(newState);
        };
      }
      // 새 상태를 나타내는 구조체를 추가할때, 해당 구조체의 좌표와 동일한 구조체가 있으면 broken 변수로 비교 및 삭제 최적화가 필요함.
      // removeDuplicates(pq);
    }
  }
  cout << best;
  return 0;
}