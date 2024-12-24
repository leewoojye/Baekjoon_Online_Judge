#include <iostream>
#include <vector>
#include <cstring>
using namespace std;
#define fastio ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define M 1000000000;

long long cache[10][100];
// back : 바로 이전의 한자리 숫자
// leftover : 남은 계단수 자릿수
long long findstairNums(int back, int leftover) {
  long long& ret=cache[back][leftover];
  if(ret!=-1) return ret;
  if(leftover == 1) {
    return ret = (back == 0 || back == 9) ? 1 : 2;
  }
  if(back==9) {
    return ret=findstairNums(8, leftover-1)%M;
  } else if(back==0) {
    return ret=findstairNums(1, leftover-1)%M;
  }
   // return ret = (findstairNums(back + 1, leftover - 1) % M + findstairNums(back - 1, leftover - 1) % M) % M; // 왜 틀림?
  long long nextUp = findstairNums(back + 1, leftover - 1) % M;
  long long nextDown = findstairNums(back - 1, leftover - 1) % M;
  return ret = (nextUp + nextDown) % M;
}

// 모듈러 연산
long long mod(long long a, long long b) {
  return ((a%b)+b)%b;
}

int main() {
  fastio;
  int N;
  cin >> N;
  long long result=0;
  for(int i=0;i<10;++i) {
    for(int j=0;j<100;++j) {
      cache[i][j]=-1;
    }
  }
  if(N==1) {
    cout << 9;
    return 0;
  }
  for(int i=1;i<=9;++i) {
    result = (result + findstairNums(i, N - 1)) % M;
  }
  cout << result;
  return 0;
}