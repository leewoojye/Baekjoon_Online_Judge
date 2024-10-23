#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
using namespace std;
#define fastio ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);

vector<int> heap;

void popHeap() {
    int size = heap.size();
    if(size==1) {
        heap.pop_back();
        return;
    }
    heap[0]=heap.back();
    heap.pop_back();
    int i=0;
    // while(2*i<=size-1) {
    //     if(2*i+1<=size-1 && heap[i]>min(heap[2*i], heap[2*i+1])) {
    //         if (heap[2*i] < heap[2*i+1]) {
    //             swap(heap[i], heap[2*i]);
    //             i = 2*i;
    //         } else {
    //             swap(heap[i], heap[2*i+1]);
    //             i = 2*i+1;
    //         }
    //         continue;
    //     } else if(2*i<=size-1 && heap[i]>heap[2*i]) {
    //         if(heap[2*i]<heap[i]) {
    //             swap(heap[i], heap[2*i]);
    //             i = 2*i;
    //         }
    //     }
    // }
    while (2*i <= size - 1) {
        int left = 2*i; // 왼쪽 자식
        int right = 2*i + 1; // 오른쪽 자식
        int largest = i; // 가장 큰 인덱스 초기화

        // 왼쪽 자식이 존재하고, 부모보다 크면 largest 업데이트
        if (left <= size - 1 && heap[left] > heap[largest]) {
            largest = left;
        }

        // 오른쪽 자식이 존재하고, 현재 largest보다 크면 업데이트
        if (right <= size - 1 && heap[right] > heap[largest]) {
            largest = right;
        }

        // 만약 largest가 변경되었다면 swap하고 i 업데이트
        if (largest != i) {
            swap(heap[i], heap[largest]);
            i = largest; // 인덱스를 자식으로 업데이트
        } else {
            break; // 더 이상 스왑할 필요 없음
        }
    }
    return;
}

void insertHeap(int n) {
    heap.push_back(n);
    for(int i=heap.size()-1;heap[i]<heap[(int)(i/2)];){
        swap(heap[i], heap[(int)(i/2)]);
        i = (int)(i/2);
    }
    return;
}

int main()
{
    fastio;
    int N;
    cin >> N;
    vector<int> inputs(N);
    for(auto& e : inputs) {
        cin >> e;
    }
    for(auto& c : inputs) {
        if(c==0) {
            if(heap.empty()) {
                cout << 0 << endl;
            } else {
                cout << heap[0] << endl;
                popHeap();           
            }
        } else {
            insertHeap(c);
        }
    }
    
    return 0;
}