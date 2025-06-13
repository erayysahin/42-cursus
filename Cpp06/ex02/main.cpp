#include "identify.hpp"
#include <iostream>

int main() {
    Base* p = generate();
    std::cout << "Pointer ile identify: ";
    identify(p);
    std::cout << "Referans ile identify: ";
    identify(*p);
    delete p;
    return 0;
}
