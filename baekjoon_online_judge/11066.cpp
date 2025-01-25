#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#define fastio ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
using namespace std;

map<vector<int>, int> dp;
int minimum;

int combineFiles(vector<int>& arr, int h) {
  if(arr.size()==1) return 0;
  // arr의 참조가 아닌 복사본을 맵의 키로 사용함
  auto it=dp.find(arr);
  if(it != dp.end()) return it->second;
  int ret=987654321;
  int tmp,tmp2;
  for(int i=0;i<=arr.size()-2;++i) {
    tmp=arr[i];
    tmp2=arr[i+1];
    // 인접 두파일 합치기
    arr[i]=arr[i]+arr[i+1];
    arr.erase(arr.begin()+i+1);
    ret=min(ret,combineFiles(arr, h-1)+tmp+tmp2);
    // if(ret>minimum) 
    // 원본 arr배열 복구
    arr[i]=tmp;
    arr.insert(arr.begin()+i+1,tmp2);
  }
  // if(h==1) minimum=min(minimum, ret);
  dp.insert({arr, ret});
  return ret;
}

int main() {
  fastio;
  int T;
  int length;
  int result;
  vector<int> inputList;
  cin >> T;
  for(int i=0;i<T;++i) {
    cin >> length;
    inputList.resize(length);
    for(int j=0;j<length;++j) {
      cin >> inputList[j];
    }
    result=combineFiles(inputList, length-1);
    cout << result;
  }
  return 0;
}

/*
1
15
1 21 3 4 5 35 5 4 3 5 98 21 14 17 32

1
4
40 30 30 50
*/