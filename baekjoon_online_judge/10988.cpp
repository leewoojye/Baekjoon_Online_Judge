#include <iostream>
#include <stack>
#include <string>
using namespace std;
#define fastio ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

int main() {
  fastio;
  string input;
  stack<int> s;
  cin >> input;
  int size=input.length();
  for(int i=0;i<(int)(size/2);++i) {
    s.push(input[i]);
  }

  int start;
  bool flag=true;
  if(size%2==0) {
    start=(size/2);
    while(!s.empty()) {
      if(input[start]!=s.top()) {
        flag=false;
        break;
      }
      s.pop();
      start++;
    }
  } else {
    // string index는 0부터 시작하기 때문에 비교를 시작할 지점도 1 줄인 값에서 시작해야함.
    start=(size/2)+1;
    while(!s.empty()) {
      if(input[start]!=s.top()) {
        flag=false;
        break;
      }
      s.pop();
      start++;
    }
  }

  if(flag) {
    cout << 1;
  } else {
    cout << 0;
  }
  return 0;
}