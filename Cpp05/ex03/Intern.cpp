#include "Intern.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include <iostream>

static AForm* makeShrub(const std::string& target) { return new ShrubberyCreationForm(target); }
static AForm* makeRobot(const std::string& target) { return new RobotomyRequestForm(target); }
static AForm* makePres(const std::string& target) { return new PresidentialPardonForm(target); }

Intern::Intern() {}
Intern::Intern(const Intern&) {}
Intern& Intern::operator=(const Intern&) { return *this; }
Intern::~Intern() {}

AForm* Intern::makeForm(const std::string& name, const std::string& target) const {
    const std::string names[3] = {
        "shrubbery creation",
        "robotomy request",
        "presidential pardon"
    };
    AForm* (*creators[3])(const std::string&) = {
        makeShrub,
        makeRobot,
        makePres
    };

    for (int i = 0; i < 3; ++i) {
        if (name == names[i]) {
            AForm* form = creators[i](target);
            std::cout << "Intern creates " << form->getName() << std::endl;
            return form;
        }
    }
    throw UnknownFormException();
}

const char* Intern::UnknownFormException::what() const throw() {
    return "Intern: Form type unknown";
}
