#include <iostream>
#include <vector>
using namespace std;
#define fastio ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

vector<vector<int>> matrix;
// visited 목록의 도시를 거쳐 here까지 왔을 때 시작점부터 here를 포함한 경로의 최소비용을 반환
int searchTSP(short visited, int here) {
  
}

int main() {
  fastio;
  int N;
  cin >> N;
  matrix.resize(N);
  int w;
  for(int i=0;i<N;++i) {
    for(int j=0;j<N;++j) {
      cin >> w;
      matrix[i].push_back(w);
    }
  }

  return 0;
}