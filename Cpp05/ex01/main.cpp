#include "Bureaucrat.hpp"
#include "Form.hpp"
#include <iostream>

int main()
{
    Bureaucrat a("Alice", 50);
    Form        f1("FormA", 30, 20);
    std::cout << a << std::endl;
    std::cout << f1 << std::endl;
    a.signForm(f1);
    std::cout << f1 << std::endl;

    Bureaucrat b("Bob", 100);
    Form        f2("FormB", 150, 150);
    std::cout << b << std::endl;
    std::cout << f2 << std::endl;
    b.signForm(f2);
    std::cout << f2 << std::endl;

    try {
        Form f3("FormC", 40, 40);
        b.signForm(f3);
    }
    catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
