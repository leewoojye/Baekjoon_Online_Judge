#include <iostream>
#include <vector>
using namespace std; 

void printArray(const vector<int>& arr) {
    for (int x : arr) {
        cout << x << " ";
    }
    cout << endl;
}

int main() {
    vector<int> b = {9, 6, 4, 1, 0};
    vector<int> c = {8, 7, 5, 3, 2};
    vector<int> a; 

    int i = 0, j = 0; 

    while (i < b.size() && j < c.size()) {
        if (b[i] >= c[j]) { 
            a.push_back(b[i]);
            i++;
        } else {
            a.push_back(c[j]);
            j++;
        }
    }

    while (i < b.size()) {
        a.push_back(b[i]);
        i++;
    }

    while (j < c.size()) {
        a.push_back(c[j]);
        j++;
    }

    cout << "Merged array: ";
    printArray(a);

    return 0;
}