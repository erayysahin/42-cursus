#include "ScalarConverter.hpp"
#include <iostream>
#include <limits>
#include <cmath>
#include <cstdlib>
#include <cerrno>
#include <iomanip>
#include <cctype>

void ScalarConverter::convert(const std::string& literal) {
    if      (isChar(literal))   
        fromChar(literal);
    else if (isInt(literal))    
        fromInt(literal);
    else if (isFloat(literal))  
        fromFloat(literal);
    else if (isDouble(literal)) 
        fromDouble(literal);
    else
        std::cerr << "Literal tipi anlaşılamadı\n";
}

bool ScalarConverter::isChar(const std::string& s) {
    return s.size() == 1 && !std::isdigit(static_cast<unsigned char>(s[0]));
}

bool ScalarConverter::isInt(const std::string& s) {
    char* end;
    errno = 0;
    std::strtol(s.c_str(), &end, 10);
    return end != s.c_str() && *end == '\0' && errno != ERANGE;
}

bool ScalarConverter::isFloat(const std::string& s) {
    if (s == "nanf" || s == "+inff" || s == "-inff")
        return true;
    if (s.size() < 2 || s[s.size() - 1] != 'f')
        return false;
    std::string body = s.substr(0, s.size() - 1);
    char* end;
    errno = 0;
    std::strtod(body.c_str(), &end);
    return end != body.c_str() && *end == '\0' && errno != ERANGE;
}

bool ScalarConverter::isDouble(const std::string& s) {
    if (s == "nan" || s == "+inf" || s == "-inf")
        return true;
    char* end;
    errno = 0;
    std::strtod(s.c_str(), &end);
    return end != s.c_str() && *end == '\0' && errno != ERANGE;
}

void ScalarConverter::printScalarResult(double value, bool impossibleChar, bool impossibleInt, bool impossibleFloat, const std::string& specialFloat, const std::string& specialDouble) {

    if (!specialFloat.empty() && !specialDouble.empty()) {
        std::cout << "char: impossible\n";
        std::cout << "int: impossible\n";
        std::cout << "float: " << specialFloat << "\n";
        std::cout << "double: " << specialDouble << "\n";
        return;
    }

    if (impossibleChar)
        std::cout << "char: impossible\n";
    else if (!std::isprint(static_cast<unsigned char>(static_cast<char>(value))))
        std::cout << "char: Non displayable\n";
    else
        std::cout << "char: '" << static_cast<char>(value) << "'\n";

    if (impossibleInt)
        std::cout << "int: impossible\n";
    else
        std::cout << "int: " << static_cast<int>(value) << "\n";

    if (impossibleFloat)
        std::cout << "float: impossible\n";
    else
        std::cout << std::fixed << std::setprecision(1)
                  << "float: " << static_cast<float>(value) << "f\n";
    std::cout << std::fixed << std::setprecision(1)
              << "double: " << value << "\n";
}

void ScalarConverter::fromChar(const std::string& s) {
    char c = s[0];
    double value = static_cast<double>(c);
    printScalarResult(value, false, false, false);
}

void ScalarConverter::fromInt(const std::string& s) {
    char* end;
    errno = 0;
    long val = std::strtol(s.c_str(), &end, 10);
    double value = static_cast<double>(val);

    bool impChar  = (val < std::numeric_limits<char>::min() || val > std::numeric_limits<char>::max());
    bool impInt   = false;
    bool impFloat = false;
    printScalarResult(value, impChar, impInt, impFloat);
}

void ScalarConverter::fromFloat(const std::string& s) {
    if (s == "nanf" || s == "+inff" || s == "-inff") {
        std::string dval = s.substr(0, s.size() - 1);
        printScalarResult(0, false, false, false, s, dval);
        return;
    }

    std::string body = s.substr(0, s.size() - 1);
    char* end;
    errno = 0;
    float f = static_cast<float>(std::strtod(body.c_str(), &end));
    double value = static_cast<double>(f);

    bool impChar  = (isnan(f) || isinf(f) ||
                     f < std::numeric_limits<char>::min() || f > std::numeric_limits<char>::max());
    bool impInt   = (isnan(f) || isinf(f) ||
                     f < std::numeric_limits<int>::min() || f > std::numeric_limits<int>::max());
    bool impFloat = false;

    printScalarResult(value, impChar, impInt, impFloat);
}

void ScalarConverter::fromDouble(const std::string& s) {
    if (s == "nan" || s == "+inf" || s == "-inf") {
        printScalarResult(0, false, false, false, s + "f", s);
        return;
    }

    char* end;
    errno = 0;
    double d = std::strtod(s.c_str(), &end);

    bool impChar  = (isnan(d) || isinf(d) ||
                     d < std::numeric_limits<char>::min() || d > std::numeric_limits<char>::max());
    bool impInt   = (isnan(d) || isinf(d) ||
                     d < std::numeric_limits<int>::min() || d > std::numeric_limits<int>::max());
    bool impFloat = (d < -std::numeric_limits<float>::max() || d > std::numeric_limits<float>::max());

    printScalarResult(d, impChar, impInt, impFloat);
}