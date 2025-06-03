#include <iostream>
#include <string>
#include "Array.hpp"

int main(void)
{
    Array<int> emptyArr;
    std::cout << "emptyArr size: " << emptyArr.size() << std::endl;

    Array<int> intArr(5);
    for (std::size_t i = 0; i < intArr.size(); ++i)
        intArr[i] = static_cast<int>(i) * 2;
    for (std::size_t i = 0; i < intArr.size(); ++i)
        std::cout << intArr[i] << " ";
    std::cout << std::endl;

    Array<int> copyArr(intArr);
    for (std::size_t i = 0; i < copyArr.size(); ++i)
        std::cout << copyArr[i] << " ";
    std::cout << std::endl;

    copyArr[2] = 100;
    std::cout << intArr[2] << std::endl;
    std::cout << copyArr[2] << std::endl;

    Array<std::string> strArr(3);
    strArr[0] = "foo";
    strArr[1] = "bar";
    strArr[2] = "baz";
    for (std::size_t i = 0; i < strArr.size(); ++i)
        std::cout << strArr[i] << " ";
    std::cout << std::endl;

    try
    {
        std::cout << intArr[10] << std::endl;
    }
    catch (std::exception& e)
    {
        std::cout << "Exception caught: out of bounds" << std::endl;
    }

    Array<int> assignArr;
    assignArr = intArr;
    for (std::size_t i = 0; i < assignArr.size(); ++i)
        std::cout << assignArr[i] << " ";
    std::cout << std::endl;

    return 0;
}
