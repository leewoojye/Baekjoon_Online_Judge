//
//  main.cpp
//  baekjoon_online_judge
//
//  Created by Woo Jye Lee on 1/1/24.
//

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main2(int argc, const char * argv[]) {
    
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    int N;
    cout << "input: ";
    cin >> N;
    cout<<"\n";
    vector<int> A(N,0);
    
    for (int i =0; i<N; i++) {
        cout<<"A input: ";
        cin>>A[i];
        cout<<"\n";
    }
    
    sort(A.begin(), A.end());
    int count=0;
    
    for (int k=0; k<N; k++) {
        int find = A[k];
        int i = 0;
        int j = N-1;
        
        while (i<j) {
            if (A[i]+A[j]>find) {
                j--;
            }
            else if (A[i]+A[j]<find) {
                i++;
            }
            else {
                if(i != k && j != k) { // 두 포인터에 해당하는 숫자는 모두 k가 아니어야 함
                    count++;
                }
            }
        }
    }
    
    cout<<"total: "  << count;
    
    return 0;
}
// change added 24.3.22