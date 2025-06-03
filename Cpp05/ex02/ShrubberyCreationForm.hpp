#ifndef SHRUBBERYCREATIONFORM_HPP
#define SHRUBBERYCREATIONFORM_HPP

#include "AForm.hpp"
#include <string>
#include <fstream>

class ShrubberyCreationForm : public AForm
{
public:
    ShrubberyCreationForm(const std::string& target);
    ShrubberyCreationForm(const ShrubberyCreationForm& other);
    ShrubberyCreationForm& operator=(const ShrubberyCreationForm& other);
    ~ShrubberyCreationForm();

protected:
    void action() const;

private:
    const std::string _target;
};

#endif
