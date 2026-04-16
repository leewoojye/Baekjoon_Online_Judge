#include <iostream>
using namespace std;

int main() {
    int arr[8];
    for (int i = 0; i < 8; i++) {
        cin >> arr[i];
    }

    bool asc = true, desc = true;
    for (int i = 0; i < 7; i++) {
        if (arr[i] + 1 != arr[i+1]) asc = false;
        if (arr[i] - 1 != arr[i+1]) desc = false;
    }

    if (asc)
        cout << "ascending\n";
    else if (desc)
        cout << "descending\n";
    else
        cout << "mixed\n";

    return 0;
}