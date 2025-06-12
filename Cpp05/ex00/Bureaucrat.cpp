#include "Bureaucrat.hpp"

Bureaucrat::GradeTooHighException::GradeTooHighException() throw() {}
Bureaucrat::GradeTooHighException::~GradeTooHighException() throw() {}
const char* Bureaucrat::GradeTooHighException::what() const throw() {
    return "GradeTooHighException: grade is too high";
}

Bureaucrat::GradeTooLowException::GradeTooLowException() throw() {}
Bureaucrat::GradeTooLowException::~GradeTooLowException() throw() {}
const char* Bureaucrat::GradeTooLowException::what() const throw() {
    return "GradeTooLowException: grade is too low";
}

Bureaucrat::Bureaucrat(const std::string& name, int grade) : name(name) {
    if (grade < 1)
        throw GradeTooHighException();
    if (grade > 150)
        throw GradeTooLowException();
    this->grade = grade;
}

Bureaucrat::Bureaucrat(const Bureaucrat& other) : name(other.name), grade(other.grade) {}

Bureaucrat::~Bureaucrat() {}

Bureaucrat& Bureaucrat::operator=(const Bureaucrat& other) {
    if (this != &other) {
        this->grade = other.grade;
    }
    return *this;
}

std::string Bureaucrat::getName() const {
    return name;
}

int Bureaucrat::getGrade() const {
    return grade;
}

void Bureaucrat::incrementGrade() {
    if (grade <= 1)
        throw GradeTooHighException();
    --grade;
}

void Bureaucrat::decrementGrade() {
    if (grade >= 150)
        throw GradeTooLowException();
    ++grade;
}

std::ostream& operator<<(std::ostream& os, const Bureaucrat& b) {
    os << b.getName() << ", bureaucrat grade " << b.getGrade() << ".\n";
    return os;
}
