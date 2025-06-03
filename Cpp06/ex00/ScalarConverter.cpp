#include "ScalarConverter.hpp"
#include <iostream>
#include <iomanip>
#include <limits>
#include <cstdlib>
#include <cerrno>

static bool isSpecial(const std::string& s) {
    return s == "nan" || s == "+nan" || s == "-nan"
        || s == "nanf"|| s == "+nanf"|| s == "-nanf"
        || s == "inf" || s == "+inf" || s == "-inf"
        || s == "inff"|| s == "+inff"|| s == "-inff";
}

bool ScalarConverter::isChar(const std::string& s) {
    return s.size() == 3 && s.front()=='\'' && s.back()=='\'';
}

bool ScalarConverter::isInt(const std::string& s) {
    char* end;
    errno = 0;
    long val = std::strtol(s.c_str(), &end, 10);
    return *end == '\0' && errno==0 && val >= std::numeric_limits<int>::min()
           && val <= std::numeric_limits<int>::max();
}

bool ScalarConverter::isFloat(const std::string& s) {
    if (!s.empty() && s.back()=='f') {
        std::string t = s.substr(0, s.size()-1);
        char* end; errno=0;
        std::strtof(t.c_str(), &end);
        return *end=='\0' && errno==0;
    }
    return false;
}

bool ScalarConverter::isDouble(const std::string& s) {
    if (isSpecial(s)) return s.find('f')==std::string::npos;
    char* end; errno=0;
    std::strtod(s.c_str(), &end);
    return *end=='\0' && errno==0;
}

void ScalarConverter::printChar(double d) {
    std::cout << "char: ";
    if (std::isnan(d) || d < 0 || d > 127)
        std::cout << "impossible\n";
    else if (!std::isprint(static_cast<char>(d)))
        std::cout << "Non displayable\n";
    else
        std::cout << "'" << static_cast<char>(d) << "'\n";
}

void ScalarConverter::printInt(double d) {
    std::cout << "int: ";
    if (std::isnan(d) || d < std::numeric_limits<int>::min()
        || d > std::numeric_limits<int>::max())
        std::cout << "impossible\n";
    else
        std::cout << static_cast<int>(d) << "\n";
}

void ScalarConverter::printFloat(double d) {
    float f = static_cast<float>(d);
    std::cout << "float: ";
    if (std::isnan(f))
        std::cout << "nanf\n";
    else if (std::isinf(f))
        std::cout << (f < 0 ? "-inff\n" : "+inff\n");
    else {
        std::cout << std::fixed << std::setprecision(1)
                  << f << "f\n";
    }
}

void ScalarConverter::printDouble(double d) {
    std::cout << "double: ";
    if (std::isnan(d))
        std::cout << "nan\n";
    else if (std::isinf(d))
        std::cout << (d < 0 ? "-inf\n" : "+inf\n");
    else {
        std::cout << std::fixed << std::setprecision(1)
                  << d << "\n";
    }
}

void ScalarConverter::convert(const std::string& lit) {
    double d;

    if (isChar(lit)) {
        d = static_cast<double>(lit[1]);
    }
    else if (isInt(lit)) {
        d = static_cast<double>(std::atoi(lit.c_str()));
    }
    else if (isFloat(lit)) {
        std::string t = lit.substr(0, lit.size()-1);
        d = static_cast<double>(std::atof(t.c_str()));
    }
    else if (isDouble(lit)) {
        d = std::atof(lit.c_str());
    }
    else {
        std::cerr << "Error: invalid literal\n";
        return;
    }

    printChar(d);
    printInt(d);
    printFloat(d);
    printDouble(d);
}
