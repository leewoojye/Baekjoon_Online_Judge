#include <iostream>
#include <string>
#include <cmath>
using namespace std;
#define fastio ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

int main() {
  fastio;
  int N;
  cin >> N;
  string s="";
  for(int i=0;i<N;++i) {
    s+=" ";
  }
  s[N-1]='*'; // 문자는 작음따옴표, 문자열은 큰 따옴표
  string s0=s;
  for(int i=0;i<2*N-1;++i) {
    s=s0;
    for(int j=0;j<abs(abs(i-(N-1))-(N-1));++j) {
      s[N-2-j]='*';
      //s[N+j]='*';
      s+='*';
    }
    cout << s << '\n';
  }
  return 0;
}