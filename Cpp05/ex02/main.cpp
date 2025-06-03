#include "Bureaucrat.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>

int main()
{
    std::srand(std::time(NULL));

    Bureaucrat boss("Boss", 1);
    Bureaucrat intern("Intern", 150);

    ShrubberyCreationForm f1("home");
    RobotomyRequestForm   f2("Bender");
    PresidentialPardonForm f3("Ford Prefect");

    try { intern.executeForm(f1); } catch (...) {}
    try { boss.executeForm(f1); } catch (...) {}

    try { boss.executeForm(f2); } catch (...) {}
    try { intern.executeForm(f2); } catch (...) {}

    try { boss.executeForm(f3); } catch (...) {}
    try { intern.executeForm(f3); } catch (...) {}

    return 0;
}
