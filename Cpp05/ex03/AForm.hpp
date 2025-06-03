#ifndef AFORM_HPP
#define AFORM_HPP

#include <string>
#include <iostream>
#include <exception>

class Bureaucrat;

class AForm
{
public:
    AForm(const std::string& name, int gradeToSign, int gradeToExecute);
    AForm(const AForm& other);
    AForm& operator=(const AForm& other);
    virtual ~AForm();

    const std::string& getName() const;
    bool                isSigned() const;
    int                 getGradeToSign() const;
    int                 getGradeToExecute() const;

    void beSigned(const Bureaucrat& b);
    void execute(const Bureaucrat& executor) const;

    class GradeTooHighException : public std::exception {
    public:
        const char* what() const throw();
    };

    class GradeTooLowException : public std::exception {
    public:
        const char* what() const throw();
    };

    class FormNotSignedException : public std::exception {
    public:
        const char* what() const throw();
    };

protected:
    virtual void action() const = 0;

private:
    const std::string _name;
    bool               _isSigned;
    const int          _gradeToSign;
    const int          _gradeToExecute;
};

std::ostream& operator<<(std::ostream& os, const AForm& f);

#endif
