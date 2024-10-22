#include <iostream>
#include <vector>
using namespace std;
#define fastio ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);

bool twoPointer(int m);
int arr[44];

int isSumoftri(int n) {
    int right=43;
    while(arr[right]>=n) {
        right--;
    }
    int leftover=n-arr[right];
    while(right>=0) {
        if(twoPointer(leftover)) {
            return 1;
        }
        right--;
        leftover=n-arr[right];
    }
    return 0;
}

bool twoPointer(int m) {
    int left=0;
    int right=43;
    while(left<=right) {
        if(arr[left]+arr[right]>m) {
            right--;
        } else if(arr[left]+arr[right]==m) {
            return true;
        } else {
            left++;
        }
    }
    return false;
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
    for(int i=0;i<44;++i) {
        arr[i]=((i+1)*(i+2))/2;
    }
    for(int n : inputs) {
        cout << isSumoftri(n) << endl;
    }

    return 0;
}