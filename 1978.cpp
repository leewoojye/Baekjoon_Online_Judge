#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;
#define fastio ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

int main() {
  fastio;
  int N;
  vector<int> input;
  int in, maxi;
  cin >> N;
  for(int i=0;i<N;++i) {
    cin >> in;
    input.push_back(in);
    if(i!=0) maxi=max(maxi,input[i]);
  }
  for(int i=1;i<=sqrt(maxi);++i) {
    for(int index=0;index<input.size();++index) {
      if(input[index]==1) {input.erase(input.begin()+index); continue;}
      if(i!=1 && i!=input[index] && input[index]%i==0) input.erase(input.begin()+index);
    }
  }
  cout << input.size() << '\n';
  return 0;
}