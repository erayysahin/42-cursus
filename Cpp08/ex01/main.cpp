#include <iostream>
#include <cstdlib>
#include <vector>
#include "Span.hpp"

int main()
{
    Span sp = Span(5);
    sp.addNumber(6);
    sp.addNumber(3);
    sp.addNumber(17);
    sp.addNumber(9);
    sp.addNumber(11);
    try
    {
        std::cout << sp.shortestSpan() << std::endl;
        std::cout << sp.longestSpan() << std::endl;
    }
    catch (std::exception&)
    {
        std::cout << "Error computing spans" << std::endl;
    }

    Span large = Span(10000);
    std::vector<int> v;
    for (int i = 0; i < 10000; ++i)
        v.push_back(std::rand());
    try
    {
        large.addNumber(v.begin(), v.end());
        std::cout << large.shortestSpan() << std::endl;
        std::cout << large.longestSpan() << std::endl;
    }
    catch (std::exception&)
    {
        std::cout << "Error with large span" << std::endl;
    }
    return 0;
}
