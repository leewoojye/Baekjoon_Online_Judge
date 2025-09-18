#include <iostream>
#include <vector>
using namespace std;

int main(int argc, const char** argv) {
    int N;
    cin >> N;
    int count = 0;
    for(int i=5;i<=N;i+=5) {
        if(i%5==0) count++;
    }
    cout << count;
    return 0;
}