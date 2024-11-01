#include <iostream>
using namespace std;
#define fastio ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

int arr[101];

int main() {
  fastio;
  arr[0]=0;
  for(int i=1;i<101;++i) {
    arr[i]=i*i;
  }
  int M, N;
  cin >> M;
  cin >> N;
  int p1=1, p2=100;
  while(arr[p1]<M || arr[p2]>N) {
    if(arr[p1]<M) {
      p1++;
    }
    if(arr[p2]>N) {
      p2--;
    }
  }
  int sum=0;
  for(int i=p1;i<=p2;++i) {
    sum+=arr[i];
  }
  if(sum==0) {
    cout << -1 << '\n';
  } else {
    cout << sum << '\n';
    cout << arr[p1];
  }
  return 0;
}