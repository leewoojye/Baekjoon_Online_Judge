#include <iostream>
using namespace std;

class Vehicle {
public:
    virtual void Type() {}
    virtual void Usage() { cout << "Transportation, "; }
    // virtual 제거
    void Wheel() { cout << "4 wheels, "; } 
    // virtual 제거
    void Door() { cout << "No door" << endl; } 
    void Print() { Type(); Usage(); Wheel(); Door(); } 
};

class Motorcycle: public Vehicle {
public:
    void Type() { cout << "Motorcycle: "; }
    void Wheel() { cout << "2 wheels, "; } // 
};

class Car: public Vehicle {
public:
    void Door() { cout << "4 doors" << endl; } // 
};

class Sedan: public Car {
public:
    void Type() { cout << "Sedan: "; }
};

class Coupe: public Car {
public:
    void Type() { cout << "Coupe: "; }
    void Door() { cout << "2 doors" << endl; } // 
};

class Hatchback: public Car {
public:
    void Type() { cout << "Hatchback: "; }
    void Door() { cout << "5 doors" << endl; } // 
};

int main() {
    Motorcycle m;
    Sedan s;
    Coupe c;
    Hatchback h;
    m.Print(); s.Print(); c.Print(); h.Print(); 
    return 0;
}