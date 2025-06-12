#include <iostream>
#include "Bureaucrat.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include "Intern.hpp"

int main() {
    Intern someRandomIntern;

    std::cout << "=== ShrubberyCreationForm via Intern ===" << std::endl;
    AForm* shrubForm = nullptr;
    try {
        shrubForm = someRandomIntern.makeForm("shrubbery creation", "home");
        Bureaucrat alice("Alice", 140);
        alice.signForm(*shrubForm);
        alice.executeForm(*shrubForm);
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    delete shrubForm;

    std::cout << std::endl;
    std::cout << "=== RobotomyRequestForm via Intern ===" << std::endl;
    AForm* roboForm = nullptr;
    try {
        roboForm = someRandomIntern.makeForm("robotomy request", "Bender");
        Bureaucrat bob("Bob", 50);
        bob.signForm(*roboForm);
        bob.executeForm(*roboForm);
        bob.executeForm(*roboForm);
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    delete roboForm;

    std::cout << std::endl;
    std::cout << "=== PresidentialPardonForm via Intern ===" << std::endl;
    AForm* pardonForm = nullptr;
    try {
        pardonForm = someRandomIntern.makeForm("presidential pardon", "Arthur");
        Bureaucrat charlie("Charlie", 1);
        charlie.signForm(*pardonForm);
        charlie.executeForm(*pardonForm);
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    delete pardonForm;

    std::cout << std::endl;
    std::cout << "=== Invalid Form via Intern ===" << std::endl;
    try {
        AForm* invalid = someRandomIntern.makeForm("invalid form", "none");
        delete invalid;
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
