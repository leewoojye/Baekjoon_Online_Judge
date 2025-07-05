#include <iostream>
#include <vector>
#include <string>
#include <queue>
using namespace std;
#define fastio ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

int main() {
  fastio;
  int tc;
  int count, sum;
  queue<int> q;
  string s;
  cin >> tc;
  for(int i=0;i<tc;++i) {
    cin >> s;
    sum=count=0;
    for(int index=0;index<s.length();++index) {
      if(s[index]=='O') {
        count++;
        if(index==s.length()-1) { sum+=count; break; }
        sum+=count;
        continue;
      }
      sum+=count;
      count=0;
    }
    q.push(sum);
  }
  while(!q.empty()) {
    int front=q.front();
    cout << front << '\n';
    q.pop();
  }
  return 0;
}