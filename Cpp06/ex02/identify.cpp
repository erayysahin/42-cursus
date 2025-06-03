#include "identify.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"
#include <cstdlib>
#include <ctime>

Base* generate(void) {
    std::srand(static_cast<unsigned>(std::time(NULL)));
    int r = std::rand() % 3;
    if (r == 0) return new A;
    if (r == 1) return new B;
    return new C;
}

void identify(Base* p) {
    if (dynamic_cast<A*>(p)) std::cout << "A\n";
    else if (dynamic_cast<B*>(p)) std::cout << "B\n";
    else if (dynamic_cast<C*>(p)) std::cout << "C\n";
    else                     std::cout << "Unknown\n";
}

void identify(Base& p) {
    try {
        (void)dynamic_cast<A&>(p);
        std::cout << "A\n";
    } catch(...) {
        try {
            (void)dynamic_cast<B&>(p);
            std::cout << "B\n";
        } catch(...) {
            try {
                (void)dynamic_cast<C&>(p);
                std::cout << "C\n";
            } catch(...) {
                std::cout << "Unknown\n";
            }
        }
    }
}
