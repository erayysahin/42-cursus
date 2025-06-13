#ifndef SCALARCONVERTER_HPP
#define SCALARCONVERTER_HPP

#include <string>

class ScalarConverter {
public:
    static void convert(const std::string& literal);

private:
    ScalarConverter();
    ScalarConverter(const ScalarConverter&);
    ScalarConverter& operator=(const ScalarConverter&);
    ~ScalarConverter();

    static bool isChar(const std::string& s);
    static bool isInt(const std::string& s);
    static bool isFloat(const std::string& s);
    static bool isDouble(const std::string& s);

    static void fromChar(const std::string& s);
    static void fromInt(const std::string& s);
    static void fromFloat(const std::string& s);
    static void fromDouble(const std::string& s);

    static void printScalarResult(double value, bool impossibleChar, bool impossibleInt, bool impossibleFloat, const std::string& specialFloat = "", const std::string& specialDouble = "");
};

#endif
