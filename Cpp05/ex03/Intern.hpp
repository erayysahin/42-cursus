#ifndef INTERN_HPP
#define INTERN_HPP

#include <string>
#include <exception>

class AForm;

class Intern {
public:
    class FormNotFoundException : public std::exception {
    public:
        FormNotFoundException() throw();
        virtual ~FormNotFoundException() throw();
        virtual const char* what() const throw();
    };

    Intern();
    Intern(const Intern& other);
    Intern& operator=(const Intern& other);
    ~Intern();

    AForm* makeForm(const std::string& formName, const std::string& target) const;
};

#endif