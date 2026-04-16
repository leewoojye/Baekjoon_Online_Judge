#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
#define fastio ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

int main() {
  fastio;
  int n1,n2;
  cin >> n1 >> n2;
  int result1,result2;
  int c1=n1, c2=n2;
  int smaller=min(c1,c2);
  int bigger=max(c1,c2);
  for(int i=smaller;i>0;--i) {
    if(c1%i==0 && c2%i==0) {result1=i; break;}
  }
  bool flag=false;
  // Q. 이중 반복문 탈출법
  for(int i=1;i<=smaller;++i) { // 큰 수에 곱해지는 i
    for(int j=1;j*smaller<=bigger*i;++j) { // 작은 수에 곱해지는 j
      if(j*smaller==bigger*i) {result2=j*smaller;flag=true;break;}
    }
    if(flag) break;
  }
  cout << result1 << '\n' << result2 << '\n';
  return 0;
}