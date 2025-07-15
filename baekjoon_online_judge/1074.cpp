#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
#define fastio ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

int N,r,c;
int counter=0;
int result;
bool flag=false;

void zDivide(int n, int rindex, int cindex) {
  if(flag) return;
  // if(r>=rindex+n || r<rindex || c>=cindex+n || c<cindex) { counter+=pow(2,n); return; }
  if(n==1) {
    if(rindex==r && cindex==c) { result=counter; flag=true; }
    counter++;
    return;
  }
  if((rindex+n/2)<=r) {
    counter+=(n*n/2);
  } else {
    zDivide(n/2,rindex,cindex);
    zDivide(n/2,rindex,cindex+n/2);    
  }
  zDivide(n/2,rindex+n/2,cindex);
  zDivide(n/2,rindex+n/2,cindex+n/2);
}

int main() {
  fastio;
  cin >> N >> r >> c;
  zDivide(pow(2,N),0,0);
  cout << result << '\n';
  return 0;
}