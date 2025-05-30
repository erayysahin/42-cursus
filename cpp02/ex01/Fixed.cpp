#include "Fixed.hpp"

const int Fixed::fractionValue = 256;

Fixed::Fixed() : fixedPointValue(0)
{
    std::cout << "Default constructor called" << std::endl;
}

Fixed::Fixed(const int value)
{
    std::cout << "Int constructor called" << std::endl;
    fixedPointValue = value * fractionValue;
}

Fixed::Fixed(const float value)
{
    std::cout << "Float constructor called" << std::endl;
    fixedPointValue = roundf(value * fractionValue);
}

Fixed::Fixed(const Fixed& other)
{
    std::cout << "Copy constructor called" << std::endl;
    *this = other;
}

Fixed::~Fixed()
{
    std::cout << "Destructor called" << std::endl;
}

Fixed& Fixed::operator=(const Fixed& other)
{
    std::cout << "Copy assignment operator called" << std::endl;

    if (this != &other)
    {
        fixedPointValue = other.fixedPointValue;
    }
    return *this;
}

float Fixed::toFloat() const {
    return static_cast<float>(fixedPointValue) / fractionValue;
}

int Fixed::toInt() const {
    return fixedPointValue / fractionValue;
}

int Fixed::getRawBits() const {
    return fixedPointValue;
}

void Fixed::setRawBits(int const raw) {
    fixedPointValue = raw;
}

std::ostream& operator<<(std::ostream& out, const Fixed& value) {
    out << value.toFloat();
    return out;
}
