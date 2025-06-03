#include "AForm.hpp"
#include "Bureaucrat.hpp"

AForm::AForm(const std::string& name, int gradeToSign, int gradeToExecute)
    : _name(name), _isSigned(false),
      _gradeToSign(gradeToSign), _gradeToExecute(gradeToExecute)
{
    if (_gradeToSign < 1 || _gradeToExecute < 1)
        throw GradeTooHighException();
    if (_gradeToSign > 150 || _gradeToExecute > 150)
        throw GradeTooLowException();
}

AForm::AForm(const AForm& other)
    : _name(other._name), _isSigned(other._isSigned),
      _gradeToSign(other._gradeToSign), _gradeToExecute(other._gradeToExecute)
{
}

AForm& AForm::operator=(const AForm& other)
{
    if (this != &other)
        _isSigned = other._isSigned;
    return *this;
}

AForm::~AForm()
{
}

const std::string& AForm::getName() const
{
    return _name;
}

bool AForm::isSigned() const
{
    return _isSigned;
}

int AForm::getGradeToSign() const
{
    return _gradeToSign;
}

int AForm::getGradeToExecute() const
{
    return _gradeToExecute;
}

void AForm::beSigned(const Bureaucrat& b)
{
    if (b.getGrade() > _gradeToSign)
        throw GradeTooLowException();
    _isSigned = true;
}

void AForm::execute(const Bureaucrat& executor) const
{
    if (!_isSigned) throw FormNotSignedException();
    if (executor.getGrade() > _gradeToExecute)
        throw GradeTooLowException();
    action();
}

const char* AForm::GradeTooHighException::what() const throw()
{
    return "AForm::GradeTooHighException";
}

const char* AForm::GradeTooLowException::what() const throw()
{
    return "AForm::GradeTooLowException";
}

const char* AForm::FormNotSignedException::what() const throw()
{
    return "AForm::FormNotSignedException";
}

std::ostream& operator<<(std::ostream& os, const AForm& f)
{
    os << "Form " << f.getName() << ", signed "
       << (f.isSigned() ? "yes" : "no")
       << ", grade to sign " << f.getGradeToSign()
       << ", grade to execute " << f.getGradeToExecute() << ".";
    return os;
}
