#include <iostream>
#include <vector>
#include <bitset>
#define fastio ios::sync_with_stdio(0), cin.tie(NULL), cout.tie(NULL);
using namespace std;

vector<int> updatedResult;
vector<int> inputList;
bitset<501> iscombined;

void combineFiles(vector<bool> arr) {

}

int main() {
  fastio;
  int T;
  int length;
  for(int i=0;i<T;++i) {
    cin >> length;
    inputList.resize(length);
    updatedResult.resize((1<<length - 1));
    for(int j=0;j<length;++j) {
      cin >> inputList[j];
    }
  }
  return 0;
}