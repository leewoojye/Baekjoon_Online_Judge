#include <iostream>
#include <vector>
#include <string>
#define fastio ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

using namespace std;

int main() {
  fastio;
  string s;
  // vector<int> stack;
  cout << "문자열을 입력하시오: ";
  cin >> s;
  int i;
  for(i=0;i<s.length()/2;i++) {
    if(s.length()%2!=0 && i==s.length()/2-1) {
      continue;
    }
  }
  if(s.length()%2!=0) i++;
  for(int j=s.length()/2-1;j>0;j--) {
    if(s[i]!=s[j]) {
      cout << "회문이 아닙니다.";
      return 0;
    }
  }
  cout << "회문입니다.";
  return 0;
}