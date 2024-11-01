#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
#define fastio ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

int findPrime(int n) {
  int start;
  int count=0;
  if(n==1) {
    return 1;
  }
  if(n%2==0) {
    start=n+1;
  } else {
    start=n+2;
  }
  for(int i=start;i<2*n;i+=2) {
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