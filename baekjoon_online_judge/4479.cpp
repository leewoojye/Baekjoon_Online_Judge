#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
#define fastio ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);

string printTriple(int n);

string printLine(int n) {
    if(n==1) {
        return "-";
    }
    n=n/3;
    return printLine(n) + printTriple(n) + printLine(n);
}
string printTriple(int n) {
    string s="";
    for(int i=0;i<n;++i) {
        s+=" ";
    }
    return s;
}

int main() {
    fastio;
    vector<int> inputs;
    int n;
    while (cin >> n) {
        inputs.push_back(static_cast<int>(pow(3,n)));
    }
    for (int value : inputs) {
        cout << printLine(value) << endl;
    }
    return 0;
}