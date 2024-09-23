#include <iostream>

struct Printer final {
    Printer() { std::cout << "Printer ctor" << std::endl; }
    // Cheating!
    // ~Printer() { std::cout << "Printer dtor" << std::endl; }
};

/// [1] Can use global object
Printer p{};

/// [2] Can use static function variable
int foo() { static Printer p{}; return 1; }
auto foo_val = foo();

/// [3] Can use static class member
class Foo final {
    static Printer p;
};

Printer Foo::p{};

/// [4] Can throw on glob init
int bar = [](){
    throw std::runtime_error("No bar on this platform");
    return 1;
}();

int main() {
    return 0; // Almost empty :)
}
