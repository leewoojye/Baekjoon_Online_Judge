#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
#define fastio ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

vector<int> heap;

void popHeap() {
    int size = heap.size();
    if(size==1) {
        heap.pop_back();
        return;
    }
    heap[0]=heap.back();
    heap.pop_back();
    size = heap.size(); // pop_back으로 사이즈 변화하므로 사이즈 변수를 한번 업데이트해줌
    int i=0;

    // 인덱스 i가 0부터 시작하므로 좌측은 2*i+1, 우측은 2*i+2임
    while (2*i + 1 <= size - 1) {
        int left = 2*i + 1; // 왼쪽 자식
        int right = 2*i + 2; // 오른쪽 자식
        int smallest = i; 

        // 왼쪽 자식이 존재하고, 부모보다 작으면 smallest 업데이트
        if (left <= size - 1 && heap[left] < heap[smallest]) {
            smallest = left;
        }

        // 오른쪽 자식이 존재하고, 현재 smallest 보다 작으면 업데이트
        if (right <= size - 1 && heap[right] < heap[smallest]) {
            smallest = right;
        }

        // 만약 smallest 가 변경되었다면 swap하고 i 업데이트
        if (smallest != i) {
            swap(heap[i], heap[smallest]);
            i = smallest; // 인덱스를 자식으로 업데이트
        } else {
            break; // 더 이상 스왑할 필요 없음
        }
    }
    return;
}

void insertHeap(long long n) {
    heap.push_back(n);
    for(int i=heap.size()-1;i>0 && heap[i]<heap[(i-1)/2];) { // (i-1/2) vs. (i-1)/2
        swap(heap[i], heap[(i-1)/2]);
        i = (i-1)/2;
    }
    return;
}

int main()
{
    fastio;
    int N;
    cin >> N;
    vector<long long> inputs(N); // 연산 입력값 최대값은 2의 31제곱이므로 long 이상의 자료형 사용
    for(auto& e : inputs) {
        cin >> e;
    }
    for(auto& c : inputs) {
        if(c==0) {
            if(heap.empty()) {
                // 시간 단축을 위한 개행문자
                cout << 0 << '\n';
            } else {
                cout << heap[0] << '\n';
                popHeap();           
            }
        } else {
            insertHeap(c);
        }
    }
    
    return 0;
}