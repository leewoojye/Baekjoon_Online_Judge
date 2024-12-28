#include <iostream>
#include <vector>
using namespace std;
#define fastio ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

int main() {
  fastio;
  int T;
  cin >> T;
  int t;
  int maxt=0;

  int dp0[41];
  int dp1[41];
  dp0[0]=dp1[1]=1;
  dp0[1]=dp1[0]=0;
  for(int i=2;i<41;++i) {
    dp1[i]=dp1[i-2]+dp1[i-1];
    dp0[i]=dp0[i-2]+dp0[i-1];
  }
  for(int i=0;i<T;++i) {
    cin >> t;
    cout << dp0[t] << " " << dp1[t] << '\n';
  }
  return 0;
}