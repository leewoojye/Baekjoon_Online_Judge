#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;
#define fastio ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

int count=0;
int N;
vector<vector<int>> board;
vector<bool> rowAvailable(N+2,true);
vector<bool> crossAvailable1(N,true);
// vector<bool> crossAvailable2(N,true);
map<int,bool> crossAvailable3;

void nqueenSolver(int col) {
  if(col==N) { ::count+=1; return; }
  // (행,열) = (i, col)
  for(int i=1;i<=N;i++) {
    if(board[i][col]==1 || !rowAvailable[i] || !crossAvailable1[i+col] || !crossAvailable3[col-i]) continue;
    crossAvailable1[i+col]=false;
    crossAvailable3[col-i]=false;
    rowAvailable[i]=false;
    nqueenSolver(col+1);
    crossAvailable1[i+col]=true;
    crossAvailable3[col-i]=true;
    rowAvailable[i]=true;
  }
  return;
}

int main() {
  fastio;
  cin >> N;
  board.assign(N+2,vector<int>(N,0));
  rowAvailable[0]=rowAvailable[N+1]=false;
  nqueenSolver(0);
  cout << ::count << '\n';
  return 0;
}