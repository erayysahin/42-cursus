#include <iostream>
#include "Bureaucrat.hpp"
#include "Form.hpp"

int main() {
    std::cout << "=== Valid Bureaucrat Creation and Modification ===" << std::endl;
    try {
        Bureaucrat alice("Alice", 2);
        std::cout << alice;
        alice.incrementGrade();
        std::cout << alice;
        alice.incrementGrade();
    } catch (const std::exception& e) {
        std::cerr << "Exception caught: " << e.what() << std::endl;
    }

    std::cout << std::endl;
    std::cout << "=== Invalid Bureaucrat Creation (Too Low) ===" << std::endl;
    try {
        Bureaucrat bob("Bob", 151);
    } catch (const std::exception& e) {
        std::cerr << "Exception caught: " << e.what() << std::endl;
    }

    std::cout << std::endl;
    std::cout << "=== Invalid Bureaucrat Creation (Too High) ===" << std::endl;
    try {
        Bureaucrat charlie("Charlie", 0);
    } catch (const std::exception& e) {
        std::cerr << "Exception caught: " << e.what() << std::endl;
    }

    std::cout << std::endl;
    std::cout << "=== Decrementing to Trigger Exception ===" << std::endl;
    try {
        Bureaucrat dave("Dave", 150);
        std::cout << dave;
        dave.decrementGrade();
    } catch (const std::exception& e) {
        std::cerr << "Exception caught: " << e.what() << std::endl;
    }

    std::cout << std::endl;
    std::cout << "=== Form Signing Tests ===" << std::endl;
    try {
        Bureaucrat john("John", 35);
        Form contract("Contract", 30, 20);
        john.signForm(contract);
        std::cout << contract;
        Bureaucrat joe("Joe", 75);
        joe.signForm(contract);
    } catch (const std::exception& e) {
        std::cerr << "Exception caught: " << e.what() << std::endl;
    }

    return 0;
}
