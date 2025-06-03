#include "identify.hpp"
#include <iostream>

int main() {
    Base* p = generate();
    std::cout << "identify(Base*): ";
    identify(p);

    std::cout << "identify(Base&): ";
    identify(*p);

    delete p;
    return 0;
}
