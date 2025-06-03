#include "Form.hpp"
#include "Bureaucrat.hpp"

Form::Form(const std::string& name, int gradeToSign, int gradeToExecute)
    : _name(name), _isSigned(false),
      _gradeToSign(gradeToSign), _gradeToExecute(gradeToExecute)
{
    if (_gradeToSign < 1 || _gradeToExecute < 1)
        throw GradeTooHighException();
    if (_gradeToSign > 150 || _gradeToExecute > 150)
        throw GradeTooLowException();
}

Form::Form(const Form& other)
    : _name(other._name), _isSigned(other._isSigned),
      _gradeToSign(other._gradeToSign),
      _gradeToExecute(other._gradeToExecute)
{
}

Form& Form::operator=(const Form& other)
{
    if (this != &other)
        _isSigned = other._isSigned;
    return *this;
}

Form::~Form()
{
}

const std::string& Form::getName() const
{
    return _name;
}

bool Form::isSigned() const
{
    return _isSigned;
}

int Form::getGradeToSign() const
{
    return _gradeToSign;
}

int Form::getGradeToExecute() const
{
    return _gradeToExecute;
}

void Form::beSigned(const Bureaucrat& b)
{
    if (b.getGrade() > _gradeToSign)
        throw GradeTooLowException();
    _isSigned = true;
}

const char* Form::GradeTooHighException::what() const throw()
{
    return "Form::GradeTooHighException";
}

const char* Form::GradeTooLowException::what() const throw()
{
    return "Form::GradeTooLowException";
}

std::ostream& operator<<(std::ostream& os, const Form& f)
{
    os << "Form " << f.getName() << ", signed " << (f.isSigned() ? "yes" : "no")
       << ", grade to sign " << f.getGradeToSign()
       << ", grade to execute " << f.getGradeToExecute() << ".";
    return os;
}
