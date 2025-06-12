#include "AForm.hpp"
#include "Bureaucrat.hpp"

AForm::GradeTooHighException::GradeTooHighException() throw() {}
AForm::GradeTooHighException::~GradeTooHighException() throw() {}
const char* AForm::GradeTooHighException::what() const throw() {
    return "AFormException: grade too high";
}

AForm::GradeTooLowException::GradeTooLowException() throw() {}
AForm::GradeTooLowException::~GradeTooLowException() throw() {}
const char* AForm::GradeTooLowException::what() const throw() {
    return "AFormException: grade too low";
}

AForm::AForm(const std::string& name, int signGrade, int executeGrade)
    : _name(name), _isSigned(false), _signGrade(signGrade), _executeGrade(executeGrade)
{
    if (_signGrade < 1 || _executeGrade < 1)
        throw GradeTooHighException();
    if (_signGrade > 150 || _executeGrade > 150)
        throw GradeTooLowException();
}

AForm::AForm(const AForm& other)
    : _name(other._name), _isSigned(other._isSigned), _signGrade(other._signGrade), _executeGrade(other._executeGrade)
{}

AForm& AForm::operator=(const AForm& other) {
    if (this != &other)
        _isSigned = other._isSigned;
    return *this;
}

AForm::~AForm() {}

const std::string& AForm::getName() const { return _name; }
bool AForm::isSigned() const { return _isSigned; }
int AForm::getSignGrade() const { return _signGrade; }
int AForm::getExecuteGrade() const { return _executeGrade; }

void AForm::beSigned(const Bureaucrat& b) {
    if (b.getGrade() > _signGrade)
        throw GradeTooLowException();
    _isSigned = true;
}

std::ostream& operator<<(std::ostream& os, const AForm& f) {
    os << "Form " << f.getName()
       << ", signed: " << (f.isSigned() ? "yes" : "no")
       << ", sign grade: " << f.getSignGrade()
       << ", execute grade: " << f.getExecuteGrade()
       << std::endl;
    return os;
}
