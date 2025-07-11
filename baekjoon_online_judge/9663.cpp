#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;
#define fastio ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

int count=0;
int N;
vector<bool> rowAvailable;
map<int,bool> crossAvailable1;
map<int,bool> crossAvailable3;

void nqueenSolver(int col) {
  if(col==N+1) { ::count+=1; return; }
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
  cout << ::count << '\n';
  return 0;
}