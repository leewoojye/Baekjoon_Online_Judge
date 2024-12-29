#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
using namespace std;
#define fastio ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

vector<vector<int>> matrix;
int start;
int N;
// visited 목록의 도시를 거쳐 here까지 왔을 때 시작점부터 here를 포함한 경로의 최소비용을 반환
int searchTSP(short visited, int here) {
  // here 방문처리
  visited |= (1 << here);
  if(visited==-1 && here==start) return 0;
  if(visited==-1) return INT_MAX;
  int ret=INT_MAX;
  for(int i=0;i<N;++i) {
    int cost=matrix[here][i];
    // 아직 방문하지 않은 도시면 방문
    if(!(visited & (1 << i))) {
      ret=min(ret,searchTSP(visited,i)+cost);
    }
  }
  return ret;
}

int main() {
  fastio;
  cin >> N;
  matrix.resize(N);
  int w;
  for(int i=0;i<N;++i) {
    for(int j=0;j<N;++j) {
      cin >> w;
      matrix[i].push_back(w);
    }
  }
  int result=INT_MAX;
  for(int i=0;i<N;++i) {
    start=i;
    result=min(result,searchTSP(0,i));
  }
  cout << result;
  return 0;
}