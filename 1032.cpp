#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<string> files(n);

    for (int i = 0; i < n; i++)
        cin >> files[i];

    int len = files[0].size();
    string pattern(len, '?');

    for (int i = 0; i < len; i++) {
        char ch = files[0][i];
        bool same = true;
        for (int j = 1; j < n; j++) {
            if (files[j][i] != ch) {
                same = false;
                break;
            }
        }
        if (same) pattern[i] = ch;
    }

    cout << pattern << endl;
    return 0;
}