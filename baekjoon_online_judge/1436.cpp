#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <cmath>
using namespace std;
#define fastio ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

int counter(int n) {
  if(n==3) return 1;
  return counter(n-1)+pow(9,n-3)*(n-2)-1;
}

int main() {
  fastio;
  // int N;
  // cin >> N;
  cout << counter(4) << '\n';
  return 0;
}

/*
6이 세개인경우, 네개인경우, 다섯개인경우... 6갯수로 분리
세자리=1
네자리=9*2-1+1=666의위치*선택가능한숫자-맨앞이0인경우+6666인경우=18
다섯자리=9^2*3-1+9*2-1+1=6세개인경우+6네개인경우+6다섯개인경우=260
여섯자리=9^3*4-1+9^2*3-1+9*2-1+1=3175
일곱자리=35979
-> 
*/
