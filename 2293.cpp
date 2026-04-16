#include <iostream>
#include <vector>
#include <algorithm>
#define fastio ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

vector<int> coins;
int cache[100][10001];

// coins(): 현재 coins index값을 포함하여 남은 kleft를 채우는 방법의수를 반환
// index; 현재 가리키는 coins 벡터위치
// kleft: 채워야할 남은 k의 양
int coins1(int index, int kleft) {
  kleft-=coins[index];
  if(kleft==0) return 1;
  if(kleft<0) return 0;
  int& ret=cache[index][kleft];
  if(ret!=-1) return ret;
  ret=0;
  // kleft-=coins[index];
  for(int i=0;index+i<coins.size();++i) {
    ret+=coins1(index+i,kleft);
  }
  return ret;
}

int main() {
  fastio;
  int n,k;
  cin >> n >> k;
  int c;
  for(int i=0;i<n;++i) {
    cin >> c;
    coins.push_back(c);
  }
  sort(coins.begin(),coins.end());
  for(int i=0;i<100;++i) {
    for(int j=0;j<10001;++j) {
      cache[i][j]=-1;
    }
  }
  int result=0;
  for(int i=0;i<coins.size();++i) {
    result+=coins1(i,k);
  }
  cout << result;
  return 0;
}