#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

int calc(int count, int size, int* cases);
int arr[10];
string input;
int inputSize;
const int INF=987654321;

int countDigits(int number) {
    if (number == 0) return 1; // 0의 경우 자릿수는 1
    return static_cast<int>(log10(abs(number))) + 1; // 절댓값의 log10 계산 후 1 더하기
}

int main() {
  // string input;
  int deletedNum;
  int tmp;
  ios::sync_with_stdio(0);
  cin.tie(0);

  cin>>input;
  cin>>deletedNum;
  for(int i=0;i<deletedNum-1;++i) {
    cin>>tmp;
    arr[tmp]=NULL;
  }
  int digits;
  inputSize=input.size();
  vector<int> cases[3];
  int result=calc(0, inputSize, cases);
  cout<<result;

  return 0;
}
// count: 리모콘 두드린 총 횟수, size: 남은 자릿수
int calc(int count, int size, int* cases) {
  int case1=INF;
  int case2=INF;
  int case3=INF;
  if(size==0) return;
  if(arr[input[inputSize-size]]!=NULL) {
    case1=calc(count+1, size-1);
  } else {
    for(int i=input[inputSize-size];i<=inputSize;++i){
      if(arr[input[inputSize-size]]!=NULL) {
        case2=calc
      }
    }
  }
}