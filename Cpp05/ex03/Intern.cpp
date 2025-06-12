#include "Intern.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include <iostream>

Intern::FormNotFoundException::FormNotFoundException() throw() {}
Intern::FormNotFoundException::~FormNotFoundException() throw() {}
const char* Intern::FormNotFoundException::what() const throw() {
    return "InternException: form type not found";
}

Intern::Intern() {}
Intern::Intern(const Intern& other) { (void)other; }
Intern& Intern::operator=(const Intern& other) { (void)other; return *this; }
Intern::~Intern() {}

AForm* Intern::makeForm(const std::string& formName, const std::string& target) const {
    AForm* form = nullptr;
    if (formName == "shrubbery creation")
        form = new ShrubberyCreationForm(target);
    else if (formName == "robotomy request")
        form = new RobotomyRequestForm(target);
    else if (formName == "presidential pardon")
        form = new PresidentialPardonForm(target);
    else
        throw FormNotFoundException();
    std::cout << "Intern creates " << form->getName() << std::endl;
    return form;
}
