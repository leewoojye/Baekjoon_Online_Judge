#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int X;
    cin >> X;

    int line = 1; 

    while (X > line) {
        X -= line;
        line++;
    }
    
    int k = X;

    if (line % 2 == 0) {
        cout << k << "/" << (line - k + 1) << "\n";
    } else {
        cout << (line - k + 1) << "/" << k << "\n";
    }

    return 0;
}