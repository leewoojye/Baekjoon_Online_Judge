#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;
#define fastio ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

vector<vector<int>> dp;
// 현재차례 turn, 남은돌 갯수 numStone에 대해 현재플레이어를 기준으로 이기면 1, 지면 -1 반환
// 틱택토와 달리 비김 없음
int combinationGame(const char& turn, int numStone) { // rvalue,lvalue, 비const 참조
  if(numStone==0) return -1;
  if(numStone<3) return -combinationGame('s'+'c'-turn,numStone-1); // 문자열 연산(- 연산 없음) vs 문자 연산
  int turnInt;
  turn=='s' ? turnInt=0 : turnInt=1;
  int& ret=dp[turnInt][numStone];
  if(ret!=2) return ret;
  // combinationGame() 재귀호출을 상대방의 승리여부를 반환하기때문에 -1을 받으면 상대는 진다. 상대가 지는 경우가 하나라도 있는지 알기 위해 max가 아닌 min을 쓴다.
  // 원래는 누가 이기냐에 따라 고정된1/-1을 부여했는데 이기는 자에게 1을 고정으로 설정하니(답의형태제약?) 코드가 간결해졌다.
  int maxV=min(combinationGame('s'+'c'-turn, numStone-1),combinationGame('s'+'c'-turn, numStone-3));
  return ret=-maxV; // 상대가 지면 나는 이기고, 상대가 어떻게든 이기면 난 진다.
}

int main() {
  fastio;
  int N;
  cin >> N;
  dp.resize(2,vector<int>(N+1, 2));
  string winner;
  combinationGame('s',N)==1 ? winner="SK" : winner="CY";
  cout << winner;
  return 0;
}