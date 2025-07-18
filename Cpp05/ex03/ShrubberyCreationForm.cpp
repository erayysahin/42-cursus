#include "ShrubberyCreationForm.hpp"
#include "Bureaucrat.hpp"
#include <fstream>

ShrubberyCreationForm::ShrubberyCreationForm(const std::string& target)
    : AForm("ShrubberyCreationForm", 145, 137), _target(target) {}

ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm& other)
    : AForm(other), _target(other._target) {}

ShrubberyCreationForm& ShrubberyCreationForm::operator=(const ShrubberyCreationForm& other) {
    if (this != &other)
        AForm::operator=(other);
    return *this;
}

ShrubberyCreationForm::~ShrubberyCreationForm() {}

void ShrubberyCreationForm::execute(Bureaucrat const& executor) const {
    if (!isSigned())
        throw AForm::GradeTooLowException();
    if (executor.getGrade() > getExecuteGrade())
        throw AForm::GradeTooLowException();

    std::ofstream ofs((_target + "_shrubbery").c_str());
    ofs << "       _-_\n";
    ofs << "    /~~   ~~\\\\\n";
    ofs << " /~~         ~~\\\\\n";
    ofs << "{               }\n";
    ofs << " \\\\  _-     -_  /\n";
    ofs << "   ~  \\\\ //  ~\n";
    ofs << "_- -   | | _- _\n";
    ofs << "  _ -  | |   -_\n";
    ofs << "      //  \\\\\n";
}
