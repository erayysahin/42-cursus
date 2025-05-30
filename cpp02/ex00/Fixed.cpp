#include "Fixed.hpp"

Fixed::Fixed() : _fixedPointNumbers(0) {
    std::cout << "Default constructor called" << std::endl;
}


Fixed::Fixed(const Fixed& other) {
    std::cout << "Copy constructor called" << std::endl;
    this->_fixedPointNumbers = other._fixedPointNumbers;  
}

Fixed& Fixed::operator=(const Fixed& other) {
    std::cout << "Copy assignment operator called" << std::endl;
    if (this != &other) {
        this->_fixedPointNumbers = other._fixedPointNumbers;
    }
    return *this;
}

Fixed::~Fixed() {
    std::cout << "Destructor called" << std::endl;
}

int Fixed::getRawBits() const {
    std::cout << "getRawBits member function called" << std::endl;
    return this->_fixedPointNumbers;
}

void Fixed::setRawBits(int const raw) {
    std::cout << "setRawBits member function called" << std::endl;
    this->_fixedPointNumbers = raw;
}
