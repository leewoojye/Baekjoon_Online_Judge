#include <iostream>
#define fastio ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

int cache[11];

int sumCase(int leftover) {
  if(leftover==0) return 1;
  int& ret=cache[leftover];
  if(ret!=-1) return ret;
  ret=0;
  ret+=sumCase(leftover-1);
  if(leftover>1) ret+=sumCase(leftover-2);
  if(leftover>2) ret+=sumCase(leftover-3);
  return ret;
}

int main() {
  fastio;
  int n;
  int T;
  cin >> T;
  int t;
  int value;
  for(int i=0;i<11;++i) {
    cache[i]=-1;
  }
  for(int i=0;i<T;++i) {
    cin >> t;
    value=sumCase(t);
    cout << value << '\n';
  }
  return 0;
}