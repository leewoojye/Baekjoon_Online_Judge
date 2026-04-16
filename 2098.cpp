#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
using namespace std;
#define fastio ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

vector<vector<int>> matrix;
int start;
int startCount=0;
int N;
short fullvisited=0;
int result=987654321;
// visited 목록의 도시를 거쳐 here까지 왔을 때 시작점부터 here를 포함한 경로의 최소비용을 반환
int searchTSP(short visited, int here) {
  // here 방문처리
  visited |= (1 << here);
  if(here==start) startCount++;
  if((visited==fullvisited)) {
    if(here==start) return 0;
    if(startCount>2) return 987654321;
  }
  int ret=987654321;
  for(int i=0;i<N;++i) {
    int cost=matrix[here][i];
    // cost가 0이면 연결되지 않은 것이므로 순회 패스
    if(cost==0) continue;
    // 아직 방문하지 않은 도시면 방문
    if((!(visited & (1 << i)) || ((i==start) && (visited==fullvisited)))) {
      ret=min(ret,searchTSP(visited,i)+cost);
    }
  }
  if(ret>=result) return 987654321;
  return ret;
}

int main() {
  fastio;
  cin >> N;
  matrix.resize(N);
  for(int i=0;i<N;++i) {
    fullvisited |= (1 << i);
  }
  int w;
  for(int i=0;i<N;++i) {
    for(int j=0;j<N;++j) {
      cin >> w;
      matrix[i].push_back(w);
    }
  }
  for(int i=0;i<N;++i) {
    start=i;
    result=min(result,searchTSP(0,i));
  }
  cout << result;
  return 0;
}

/*
두 번째 알고리즘 :
s지점에서 출발해 다시 s지점으로 돌아오므로 s-t, t-s 거리 합 중 최소가 되는 비용을 구함
*/