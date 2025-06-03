#include "Bureaucrat.hpp"
#include <iostream>

int main()
{
    try {
        Bureaucrat a("Alice", 2);
        std::cout << a << std::endl;
        a.incrementGrade();
        std::cout << a << std::endl;
        a.incrementGrade();
    }
    catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    try {
        Bureaucrat b("Bob", 149);
        std::cout << b << std::endl;
        b.decrementGrade();
        std::cout << b << std::endl;
        b.decrementGrade();
    }
    catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    try {
        Bureaucrat c("Charlie", 0);
    }
    catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    try {
        Bureaucrat d("Dave", 151);
    }
    catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
