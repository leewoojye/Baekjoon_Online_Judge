#include <iostream>
#include <deque>
#include <algorithm>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N, M;
    cin >> N >> M;
    
    deque<int> dq;
    for (int i = 1; i <= N; i++) {
        dq.push_back(i);
    }
    
    int total_operations = 0;
    
    for (int i = 0; i < M; i++) {
        int target;
        cin >> target;
        
        int pos = find(dq.begin(), dq.end(), target) - dq.begin();
        
        int left_rotations = pos;
        int right_rotations = dq.size() - pos;
        
        if (left_rotations <= right_rotations) {
            for (int j = 0; j < left_rotations; j++) {
                dq.push_back(dq.front());
                dq.pop_front();
            }
            total_operations += left_rotations;
        } else {
            for (int j = 0; j < right_rotations; j++) {
                dq.push_front(dq.back());
                dq.pop_back();
            }
            total_operations += right_rotations;
        }
        
        dq.pop_front();
    }
    
    cout << total_operations << endl;
    
    return 0;
}