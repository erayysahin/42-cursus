#ifndef AFORM_HPP
#define AFORM_HPP

#include <string>
#include <exception>
#include <iostream>

class Bureaucrat;

class AForm {
private:
    const std::string _name;
    bool              _isSigned;
    const int         _signGrade;
    const int         _executeGrade;

public:
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

    AForm(const std::string& name, int signGrade, int executeGrade);
    AForm(const AForm& other);
    AForm& operator=(const AForm& other);
    virtual ~AForm();

    const std::string& getName() const;
    bool                isSigned() const;
    int                 getSignGrade() const;
    int                 getExecuteGrade() const;

    void beSigned(const Bureaucrat& b);
    virtual void execute(Bureaucrat const & executor) const = 0;
};

std::ostream& operator<<(std::ostream& os, const AForm& f);

#endif