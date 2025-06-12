#ifndef BUREAUCRAT_HPP
#define BUREAUCRAT_HPP

#include <string>
#include <exception>
#include <iostream>

class AForm;

class Bureaucrat {
private:
    const std::string name;
    int               grade;

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

    Bureaucrat(const std::string& name, int grade);
    Bureaucrat(const Bureaucrat& other);
    ~Bureaucrat();
    Bureaucrat& operator=(const Bureaucrat& other);

    std::string getName() const;
    int         getGrade() const;

    void incrementGrade();
    void decrementGrade();
    void signForm(AForm& f);
    void executeForm(AForm const & form) const;

};

std::ostream& operator<<(std::ostream& os, const Bureaucrat& b);

#endif