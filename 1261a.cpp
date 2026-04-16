#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <string>
using namespace std;
// #define fastio ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

vector<vector<int>> maze;
int N,M;
int best=987654321;
int dx[4]={1,0,-1,0};
int dy[4]={0,1,0,-1};

struct state {
  __int128 vi=0; // gcc 컴파일러 내장 프로퍼티
  int x,y;
  int broken=0;
  state(__int128 vP, int xP, int yP, int bP) : vi(vP),x(xP),y(yP),broken(bP) {}
  bool operator<(const state& other) const {
    // 최적화 : broken이 같을 경우 (N,M)에 더 가까운 좌표를 갖는 상태에 우선순위를 부여함. 종착지와 가까울수록 정답에 가까울 것이라는 건 직관적으로 알 수 있으니까 (휴리스틱)
    if(broken==other.broken) return (x+y) < (other.x+other.y);
    return broken < other.broken; 
  }
  bool operator==(const state& other) const {
    return x == other.x && y == other.y;
  }
};

int main() {
  // fastio;
  cin >> N >> M;

  // 각 좌표에 도달하는데 부숴야할 벽의 수를 갱신하기 위한 2차원 배열
  vector<vector<int>> stateMap;
  stateMap.resize(N+1,vector<int>(M+1, 987654321));

  maze.resize(N+1,vector<int>(M+1,0));
  string s;
  // a[b][c]에서 b는 행, c는 열을 의미 하지만 여기서  모든 x,y 좌표는 대칭된채 계산되므로 결과에 영향은 없음
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
      if(front.broken==0) { best=0; break; }
      best=min(best,front.broken);
      continue;
    }
    if(front.broken>best) continue; // pruning
    for(int i=0;i<4;++i) {
      nextx=front.x+dx[i];
      nexty=front.y+dy[i];
      if(nextx<1 || nextx>N || nexty<1 || nexty>M) continue;
      if(front.vi & 1<<(nexty*N+nextx)) continue;
      if(maze[nextx][nexty]==1) {
        state newState(front.vi | 1<<(nexty*N+nextx),nextx,nexty,front.broken+1);
        if(newState.broken<=stateMap[nextx][nexty]) { 
          stateMap[nextx][nexty]=min(stateMap[nextx][nexty],newState.broken);
          pq.push(newState);
        }
      } else {
        state newState(front.vi | 1<<(nexty*N+nextx),nextx,nexty,front.broken);
        if(newState.broken<=stateMap[nextx][nexty]) { 
          stateMap[nextx][nexty]=min(stateMap[nextx][nexty],newState.broken);
          pq.push(newState);
        }
      }
      // 새 상태를 나타내는 구조체를 추가할때, 해당 구조체의 좌표와 동일한 구조체가 있으면 broken 변수로 비교 및 삭제 최적화가 필요함.
    }
  }
  cout << best;
  return 0;
}