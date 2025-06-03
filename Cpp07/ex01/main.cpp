#include <iostream>
#include <string>
#include "iter.hpp"

void printInt(int& x)
{
    std::cout << x << std::endl;
}

void printConstInt(int const& x)
{
    std::cout << x << std::endl;
}

void increment(int& x)
{
    x = x + 1;
}

void printString(std::string& s)
{
    std::cout << s << std::endl;
}

void printConstString(std::string const& s)
{
    std::cout << s << std::endl;
}

int main(void)
{
    int arrInt[] = {1, 2, 3, 4, 5};
    std::size_t lenInt = 5;
    iter(arrInt, lenInt, printInt);
    iter(arrInt, lenInt, increment);
    iter(arrInt, lenInt, printInt);

    const int constArrInt[] = {10, 20, 30};
    std::size_t lenConstInt = 3;
    iter(constArrInt, lenConstInt, printConstInt);

    std::string arrStr[] = {"hello", "world", "iter"};
    std::size_t lenStr = 3;
    iter(arrStr, lenStr, printString);

    const std::string constArrStr[] = {"const", "string", "array"};
    std::size_t lenConstStr = 3;
    iter(constArrStr, lenConstStr, printConstString);

    return 0;
}
