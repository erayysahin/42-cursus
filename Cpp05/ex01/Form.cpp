#include "Form.hpp"
#include "Bureaucrat.hpp"

Form::GradeTooHighException::GradeTooHighException() throw() {}
Form::GradeTooHighException::~GradeTooHighException() throw() {}
const char* Form::GradeTooHighException::what() const throw() {
    return "FormException: grade too high";
}

Form::GradeTooLowException::GradeTooLowException() throw() {}
Form::GradeTooLowException::~GradeTooLowException() throw() {}
const char* Form::GradeTooLowException::what() const throw() {
    return "FormException: grade too low";
}

Form::Form(const std::string& name, int gradeToSign, int gradeToExecute)
    : _name(name), _isSigned(false), _gradeToSign(gradeToSign), _gradeToExecute(gradeToExecute)
{
    if (_gradeToSign < 1 || _gradeToExecute < 1)
        throw GradeTooHighException();
    if (_gradeToSign > 150 || _gradeToExecute > 150)
        throw GradeTooLowException();
}

Form::Form(const Form& other)
    : _name(other._name), _isSigned(other._isSigned), _gradeToSign(other._gradeToSign), _gradeToExecute(other._gradeToExecute)
{}

Form& Form::operator=(const Form& other) {
    if (this != &other) {
        _isSigned = other._isSigned;
    }
    return *this;
}

Form::~Form() {}

const std::string& Form::getName() const { return _name; }
bool Form::getSigned() const { return _isSigned; }
int Form::getSignGrade() const { return _gradeToSign; }
int Form::getExecuteGrade() const { return _gradeToExecute; }

void Form::beSigned(const Bureaucrat& b) {
    if (b.getGrade() > _gradeToSign)
        throw GradeTooLowException();
    _isSigned = true;
}

std::ostream& operator<<(std::ostream& os, const Form& f) {
    os << "Form " << f.getName()
       << ", signed: " << (f.getSigned() ? "yes" : "no")
       << ", sign grade: " << f.getSignGrade()
       << ", execute grade: " << f.getExecuteGrade()
       << std::endl;
    return os;
}
