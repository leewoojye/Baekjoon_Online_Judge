#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
#include <utility>
#define fastio ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

vector<int> rangeMin;
vector<int> rangeMax;

struct segmentTree {
  vector<int> list;
  int n=list.size();
  int left,right;
  segmentTree(vector<int>& vc, int N) {
    list=vc;
    init(list, 0, 0, N-1);
  }
  // 세그먼트 트리 전처리
  // pair<min, max>
  pair<int,int> init(vector<int>& v, int node, int nodeLeft, int nodeRight) {
    if(nodeLeft==nodeRight) {
      rangeMin[node]=v[nodeLeft];
      return {v[nodeLeft], v[nodeLeft]};
    }
    int mid=(nodeLeft+nodeRight)/2;
    rangeMin[node]=min(init(v, node*2, nodeLeft, mid).first, init(v, node*2+1, mid+1, nodeRight).first);
    rangeMax[node]=max(init(v, node*2, nodeLeft, mid).second, init(v, node*2+1, mid+1, nodeRight).second);
    return {rangeMin[node], rangeMax[node]};
  }
  // left,right, nodeLeft, nodeRight, node가 주어졌을 때 노드구간내 최솟값 반환
  int queryMin(int node, int nodeLeft, int nodeRight) {
    if(nodeLeft==nodeRight) return rangeMin[nodeLeft];
    if(nodeLeft>left || nodeRight<right) return INT_MAX;
    int mid=(nodeLeft+nodeRight)/2;
    return min(queryMin(node*2, nodeLeft, mid), queryMin(node*2+1, mid+1, nodeRight));
  }
  int queryMax(int node, int nodeLeft, int nodeRight) {
    if(nodeLeft==nodeRight) return rangeMax[nodeLeft];
    if(nodeLeft>left || nodeRight<right) return -1;
    int mid=(nodeLeft+nodeRight)/2;
    return max(queryMax(node*2, nodeLeft, mid), queryMax(node*2+1, mid+1, nodeRight));
  }
  pair<int,int> queryInterface(int left, int right) {
    this->left=left-1;

    this->right=right-1;
    return {queryMin(0, 0, n-1), queryMax(0,0,n-1)};
  }
};

int main() {
  fastio;
  int N,M;
  cin >> N >> M;
  rangeMin.resize(N);
  rangeMax.resize(N);
  vector<int> input;
  int n;
  for(int i=0;i<N;++i) {
    cin >> n;
    input.push_back(n);
  }
  segmentTree* tree=new segmentTree(input, N);
  int l,r;
  for(int i=0;i<M;++i) {
    cin >> l >> r;
    pair<int,int> result=tree->queryInterface(l,r);
    cout << result.first << result.second << '\n';
  }
  return 0;
}