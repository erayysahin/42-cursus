#ifndef FORM_HPP
#define FORM_HPP

#include <string>
#include <iostream>
#include <exception>

class Bureaucrat;

class Form {
public:
    Form(const std::string& name, int gradeToSign, int gradeToExecute);
    Form(const Form& other);
    Form& operator=(const Form& other);
    ~Form();

    const std::string& getName() const;
    bool                getSigned() const;
    int                 getSignGrade() const;
    int                 getExecuteGrade() const;
    void                beSigned(const Bureaucrat& b);

    class GradeTooHighException : public std::exception {
    public:
        GradeTooHighException() throw();
        virtual ~GradeTooHighException() throw();
        virtual const char* what() const throw();
    };

    class GradeTooLowException : public std::exception {
    public:
        GradeTooLowException() throw();
        virtual ~GradeTooLowException() throw();
        virtual const char* what() const throw();
    };

private:
    const std::string _name;
    bool              _isSigned;
    const int         _gradeToSign;
    const int         _gradeToExecute;
};

std::ostream& operator<<(std::ostream& os, const Form& f);

#endif
