#ifndef FIXED_HPP
#define FIXED_HPP

#include <iostream>
#include <cmath>

class Fixed {

    int fixedPointValue;
    static const int fractionValue;

public:
    Fixed();
    Fixed(const int value);
    Fixed(const float value);
    Fixed(const Fixed& other);
    ~Fixed();

    Fixed& operator=(const Fixed& other);

    float toFloat() const;
    int toInt() const;

    int getRawBits() const;
    void setRawBits(int const raw);
};
std::ostream& operator<<(std::ostream& out, const Fixed& value);

#endif
