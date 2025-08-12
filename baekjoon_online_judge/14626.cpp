#include <iostream>
#include <vector>
#include <string>
using namespace std;
#define fastio ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

int main() {
  fastio;
  string s;
  cin >> s;
  int multiplier;
  int sum=0;
  for(int i=0;i<13;++i) {
    if(s[i]=='*') {
      i%2==0 ? multiplier=1 : multiplier=3;
      continue;
    }
    i%2==0 ? sum+=(s[i]-'0') : sum+=(3*(s[i]-'0'));
  }
  int result;
  for(int s=0;s<10;++s) {
    if((sum+s*multiplier)%10==0) {result=s;break;}
  }
  cout << result << '\n';
  return 0;
}