#include <iostream>
using namespace std;

struct Complex {
    double real;
    double imag;
};

Complex Subtract(Complex c1, Complex c2) {
    Complex result;
    result.real = c1.real - c2.real;
    result.imag = c1.imag - c2.imag;
    return result;
}

int main() {
    Complex c1 = {4.8, 3.2};
    Complex c2 = {2.1, 7.5};
    
    Complex res = Subtract(c1, c2);
    cout << "Result: " << res.real << " + " << res.imag << "i" << endl;
    return 0;
}