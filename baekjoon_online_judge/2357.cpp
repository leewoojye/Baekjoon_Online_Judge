#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
#define fastio ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

vector<int> rangeMin;

struct segmentTree {
  vector<int> list;
  segmentTree(vector<int>& vc, int N) {
    list=vc;
    init(list, 0, 0, N-1);
  }
  // 세그먼트 트리 전처리
  int init(vector<int>& v, int node, int nodeLeft, int nodeRight) {
    if(nodeLeft==nodeRight) return rangeMin[node]=v[nodeLeft];
    int mid=(nodeLeft+nodeRight)/2;
    return rangeMin[node]=min(init(v, node*2, nodeLeft, mid), init(v, node*2+1, mid+1, nodeRight));
  }
  // left,right, nodeLeft, nodeRight, node가 주어졌을 때 노드구간내 최솟값 반환
  int queryMin(int left, int right, int node, int nodeLeft, int nodeRight) {}
  int queryMax(int left, int right, int node, int nodeLeft, int nodeRight) {}
};

int main() {
  fastio;
  int N,M;
  cin >> N >> M;
  rangeMin.resize(N);
  vector<int> input(N);
  int n;
  for(int i=0;i<N;++i) {
    cin >> n;
    input.push_back(n);
  }
  segmentTree* tree=new segmentTree(input, N);
  return 0;
}