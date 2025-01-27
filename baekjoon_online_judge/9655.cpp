#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;
#define fastio ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

vector<vector<int>> dp;
// 현재차례 turn, 남은돌 갯수 numStone에 대해 이기는사람 -1 OR 1 반환
// 비기는 경우
int combinationGame(int turn, int numStone) {
  if(numStone==0) return -turn;
  if(numStone<3) return combinationGame(-turn,numStone-1);
  // if(numStone==1) return 'S'+'C'-turn; // 문자열 연산, 문자 연산
  int& ret=dp[turn+1][numStone];
  if(ret!=0) return ret;
  int sum=combinationGame(-turn,numStone-1)+combinationGame(-turn,numStone-3);
  if(sum*turn<0) return ret=(-turn);
  return ret=turn;
}

int main() {
  fastio;
  int N;
  cin >> N;
  dp.resize(3,vector<int>(N+1, 0));
  string winner;
  combinationGame(1,N)==1 ? winner="SY" : winner="CY";
  cout << winner;
  return 0;
}