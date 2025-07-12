#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;
#define fastio ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

int count_queen=0; // std::count 와 이름이 겹칠 수 있어 권장 x
int N;
vector<bool> rowAvailable;
// vector<bool> rowAvailable(N+2,true); // N이 초기화되지 않은 상태에선 보통 0으로 간주
map<int,bool> crossAvailable1;
map<int,bool> crossAvailable3;

void nqueenSolver(int col) {
  if(col==N+1) { count_queen+=1; return; }
  // (행,열) = (row, col)
  for(int row=1;row<=N;row++) {
    if(!rowAvailable[row] || !crossAvailable1[row+col] || !crossAvailable3[col-row]) continue;
    crossAvailable1[row+col]=false;
    crossAvailable3[col-row]=false;
    rowAvailable[row]=false;
    nqueenSolver(col+1);
    crossAvailable1[row+col]=true;
    crossAvailable3[col-row]=true;
    rowAvailable[row]=true;
  }
  return;
}

int main() {
  fastio;
  cin >> N;
  rowAvailable.assign(N + 1, true);
  rowAvailable[0]=false;
  for (int i = 2; i <= 2 * N; ++i) { // row + col 범위
    crossAvailable1[i] = true;
  }
  for (int i = -(N - 1); i <= N - 1; ++i) { // col - row 범위
    crossAvailable3[i] = true;
  }
  nqueenSolver(1);
  cout << count_queen << '\n';
  return 0;
}