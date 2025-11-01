#include <iostream>
#include <algorithm> 

int findMin(int a[], int n) {
    if (n == 1) {
        return a[0];
    }
    
    return std::min(a[n - 1], findMin(a, n - 1));
}

int main() {
    int a[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int size = 10;
    
    int minElement = findMin(a, size);
    
    std::cout << "Min element in array = " << minElement << std::endl;
    
    return 0;
}