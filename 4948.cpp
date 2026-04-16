#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
#define fastio ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

int findPrime(int n) {
  int start;
  int count=0;
  // 입력이 2인 특별한 경우를 처리함(유일한 짝수 소수)
  if(n==1) {
    return 1;
  }
  if(n%2==0) {
    start=n+1;
  } else {
    start=n+2;
  }
  for(int i=start;i<2*n;i+=2) {
    // 입력값=2~8인 경우 루트값이 3보다 작기 때문에 소수 후보 j는 1부터 시작해야함
    for(int j=1;j<=(int)sqrt(i);j+=2) {
      if(i%j==0 && j>1) {
        break;
      } else if (j==(int)sqrt(i) || j==(int)sqrt(i)-1) {
        count++;
      }
    }
  }
  return count;
}

int main() {
  fastio;
  vector<int> input;
  int tmp;
  while(1) {
    cin >> tmp;
    if(tmp==0) {
      break;
    }
    input.push_back(tmp);
  }
  for(auto& n : input) {
    cout << findPrime(n) << '\n';
  }
  return 0;
}