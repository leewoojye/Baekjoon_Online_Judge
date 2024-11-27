#include <iostream>
#include <vector>
#define fastio ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

int main() {
  fastio;
  int N;
  cin >> N;
  int min=0;
  // X+Y=k, 3X+5Y=N 두 일차방정식의 교집합
  while(1) {
    if((5*min-N)%2==0 && (5*min-N)>=0) {
      if((5*min-N)/2 > min) {
        min=-1;
        break;
      }
      break;
    }
    min++;
  }
  cout << min;
  return 0;
}