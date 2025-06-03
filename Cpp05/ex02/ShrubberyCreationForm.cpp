#include "ShrubberyCreationForm.hpp"

ShrubberyCreationForm::ShrubberyCreationForm(const std::string& target)
    : AForm("ShrubberyCreationForm", 145, 137), _target(target)
{
}

ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm& other)
    : AForm(other), _target(other._target)
{
}

ShrubberyCreationForm& ShrubberyCreationForm::operator=(const ShrubberyCreationForm& other)
{
    if (this != &other) *((AForm*)this) = other;
    return *this;
}

ShrubberyCreationForm::~ShrubberyCreationForm()
{
}

void ShrubberyCreationForm::action() const
{
    std::ofstream ofs(_target + "_shrubbery");
    ofs << "   ccee88oo\n  C8O8O8Q8PoOb o8oo\n dOB69QO8PdUOpugoO9bD\nCgggbU8OU qOp qOdoUOdcb\n    6OuU  /p u gcoUodpP\n      \\\\//  /douUP\n        \\\\////\n         |||/\\\n         |||\\/\n         |||||\n   .....//||||\\....\n";
    ofs.close();
}
