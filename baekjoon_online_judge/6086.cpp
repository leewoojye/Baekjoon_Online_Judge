#include <iostream>
#include <vector>
#include <queue>
using namespace std;
#define fastio ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

int main() {
  fastio;
  int E;
  cin >> E;
  // 잔여용량이랑 유량 같은 배열로 쓰기
  vector<vector<int>> flow(26, vector<int>(26, 0));
  char c1,c2;
  int f;
  for(int i=0;i<E;++i) {
    cin >> c1 >> c2 >> f;
    flow[c1-65][c2-65]=f;
    flow[c2-65][c1-65]=f;
  }
  
  return 0;
}