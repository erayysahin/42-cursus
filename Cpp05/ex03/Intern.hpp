#ifndef INTERN_HPP
#define INTERN_HPP

#include <string>
#include <exception>
#include "AForm.hpp"

class Intern {
public:
    Intern();
    Intern(const Intern&);
    Intern& operator=(const Intern&);
    ~Intern();

    AForm* makeForm(const std::string& name, const std::string& target) const;

    class UnknownFormException : public std::exception {
    public:
        const char* what() const throw();
    };
};

#endif
