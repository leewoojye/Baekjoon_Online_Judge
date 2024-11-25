#include <iostream>
#include <vector>
#define fastio ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

int main() {
  fastio;
  int N,M;
  cin >> N >> M;
  vector<vector<int>> matrix(N+1);
  int e1,e2;
  for(int i=0;i<M;++i) {
    cin >> e1 >> e2;
    matrix[e1].push_back(e2);
  }
  
  return 0;
}