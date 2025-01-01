#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
using namespace std;
#define fastio ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

vector<vector<int>> matrix;
int start;
int N;
short fullvisited;
// visited 목록의 도시를 거쳐 here까지 왔을 때 시작점부터 here를 포함한 경로의 최소비용을 반환
int searchTSP(short visited, int here) {
  // here 방문처리
  visited |= (1 << here);
  if((visited==fullvisited) && (here==start)) {
    return 0;
  }
  if(visited==fullvisited) {
    return 987654321;
  }
  int ret=987654321;
  for(int i=0;i<N;++i) {
    int cost=matrix[here][i];
    // cost가 0이면 연결되지 않은 것이므로 순회 패스
    if(cost==0) continue;
    // 아직 방문하지 않은 도시면 방문
    if((!(visited & (1 << i)) || (i==start))) {
      ret=min(ret,searchTSP(visited,i)+cost);
    }
    // if((!(visited & (1 << i)) || (i==start)) && (here!=i)) {
    //   ret=min(ret,searchTSP(visited,i)+cost);
    // }
  }
  return ret;
}

int main() {
  fastio;
  cin >> N;
  matrix.resize(N);
  fullvisited = (1 << N) - 1;
  int w;
  for(int i=0;i<N;++i) {
    for(int j=0;j<N;++j) {
      cin >> w;
      matrix[i].push_back(w);
    }
  }
  int result=987654321;
  for(int i=0;i<N;++i) {
    start=i;
    result=min(result,searchTSP(0,i));
  }
  cout << result;
  return 0;
}