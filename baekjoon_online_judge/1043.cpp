#include <iostream>
#include <vector>
#include <bitset>
using namespace std;
#define fastio ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

vector<bitset<50>> party;

int main() {
  fastio;
  bitset<50> truelist;
  // vector<int> trueparty; // 진실자가 포함된 파티 집합
  bitset<50> trueman1; // 진실을 말하면 안되는 사람들의 집합

  int N, M;
  cin >> N >> M;
  party.assign(M,0);
  int trueman;
  cin >> trueman;
  int offset;
  for(int i=0;i<trueman;++i) {
    cin >> offset;
    truelist.set(offset-1); // 맨 우측 기준
  }
  int numParticipant; int member;
  for(int i=0;i<M;++i) {
    cin >> numParticipant;
    for(int p=0;p<numParticipant;++p) {
      cin >> member; party[i].set(member-1);
    }
    // if((party[i] & truelist) != 0) trueparty.push_back(i); // 비교연산자가 비트연산자보다 우선순위 높음
    if((party[i] & truelist) != 0) trueman1 |= party[i];
  }
  int numparty=0;
  for(int i=0;i<M;++i) {
    if((trueman1 & party[i]) != 0) continue;
    numparty++;
  }
  cout << numparty << '\n';
  return 0;
}