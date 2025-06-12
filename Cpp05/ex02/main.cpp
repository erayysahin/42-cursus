#include <iostream>
#include "Bureaucrat.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

int main() {
    std::cout << "=== ShrubberyCreationForm Test ===" << std::endl;
    Bureaucrat alice("Alice", 140);
    ShrubberyCreationForm shrub("home");
    alice.signForm(shrub);
    alice.executeForm(shrub);

    std::cout << std::endl;
    std::cout << "=== RobotomyRequestForm Test ===" << std::endl;
    Bureaucrat bob("Bob", 50);
    RobotomyRequestForm robo("Bender");
    bob.signForm(robo);
    bob.executeForm(robo);
    bob.executeForm(robo);

    std::cout << std::endl;
    std::cout << "=== PresidentialPardonForm Test ===" << std::endl;
    Bureaucrat charlie("Charlie", 1);
    PresidentialPardonForm pardon("Arthur");
    charlie.signForm(pardon);
    charlie.executeForm(pardon);

    return 0;
}
