#include <vector>
#include <list>
#include <iostream>
#include "easyfind.hpp"

int main()
{
    std::vector<int> v;
    for (int i = 0; i < 5; ++i)
        v.push_back(i * 2);
    try
    {
        std::vector<int>::iterator it = easyfind(v, 4);
        std::cout << *it << std::endl;
        easyfind(v, 5);
    }
    catch (std::exception&)
    {
        std::cout << "Value not found" << std::endl;
    }

    std::list<int> l;
    for (int i = 1; i <= 5; ++i)
        l.push_back(i);
    try
    {
        std::list<int>::iterator it2 = easyfind(l, 3);
        std::cout << *it2 << std::endl;
        easyfind(l, 6);
    }
    catch (std::exception&)
    {
        std::cout << "Value not found" << std::endl;
    }
    return 0;
}
