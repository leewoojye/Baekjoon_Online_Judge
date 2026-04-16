#include <iostream>
#include <string>
using namespace std;

int main() {
    string num;
    
    while (cin >> num && num != "0") {
        bool isPalindrome = true;
        int len = num.length();
        
        for (int i = 0; i < len / 2; i++) {
            if (num[i] != num[len - 1 - i]) {
                isPalindrome = false;
                break;
            }
        }
        
        if (isPalindrome) {
            cout << "yes" << endl;
        } else {
            cout << "no" << endl;
        }
    }
    
    return 0;
  }