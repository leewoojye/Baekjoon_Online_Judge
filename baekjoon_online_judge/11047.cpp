#include <iostream>
#include <vector>
#define fastio ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
using namespace std;

int main() {
  fastio;
  int N,K;
  int count=0;
  cin >> N >> K;
  vector<int> coins(N);
  for(auto& e : coins) {
    cin >> e;
  }
  while(K>=0) {
    if(K==0) {
      break;
    }
    for(int i=coins.size()-1;i>=0;--i) {
      if(coins[i]<=K) {
        K -= coins[i];
        count++;
        break;
      } else {
        coins.pop_back();
      }
    }
  }
  cout << count <<endl;
  return 0;
}