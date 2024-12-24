#include <iostream>
#include <vector>
#include <cstring>
using namespace std;
#define fastio ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

long long cache[10][100];
// back : 바로 이전의 한자리 숫자
// leftover : 남은 계단수 자릿수
long long findstairNums(int back, int leftover) {
  if(leftover==0) return 1;
  long long& ret=cache[back][leftover];
  if(ret!=-1) return ret;
  if(back==9) {
    return ret=findstairNums(8, leftover-1);
  } else if(back==0) {
    return ret=findstairNums(1, leftover-1);
  }
  return ret=findstairNums(back+1,leftover-1)+findstairNums(back-1,leftover-1);
}

long long mod(long long a, long long b) {
  return ((a%b)+b)%b;
}

int main() {
  fastio;
  int N;
  cin >> N;
  long long result=0;
  // memset(cache, 0, sizeof(cache));
  for(int i=0;i<10;++i) {
    for(int j=0;j<100;++j) {
      cache[i][j]=-1;
    }
  }
  for(int i=1;i<=9;++i) {
    result+=findstairNums(i,N-1);
  }
  result=mod(result,1000000000);
  // result%=1000000000;
  cout << result;
  return 0;
}