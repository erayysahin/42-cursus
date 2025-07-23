#include "PmergeMe.hpp"
#include <iostream>
#include <sstream>
#include <ctime>
#include <iomanip>
#include <cstdlib>

PmergeMe::PmergeMe() {}
PmergeMe::PmergeMe(char **av, int ac)
{
    for (int i = 1; i < ac; ++i)
    {
        std::string token = av[i];
        if (!isPositiveInteger(token))
        {
            std::cerr << "Error" << std::endl;
        }
        long value = std::atol(token.c_str());
        if (value <= 0)
        {
            std::cerr << "Error" << std::endl;
        }
        vec.push_back(static_cast<int>(value));
        deq.push_back(static_cast<int>(value));
    }
}
PmergeMe::PmergeMe(const PmergeMe &other) { static_cast<void>(other); }
PmergeMe &PmergeMe::operator=(const PmergeMe &other)
{
    static_cast<void>(other);
    return *this;
}
PmergeMe::~PmergeMe() {}

bool PmergeMe::isPositiveInteger(const std::string &s)
{
    if (s.empty())
        return false;
    for (size_t i = 0; i < s.size(); ++i)
    {
        if (s[i] < '0' || s[i] > '9')
            return false;
    }
    return true;
}
const std::deque<int> &PmergeMe::getDeq() const
{
    return deq;
}

void PmergeMe::printDeq() const
{
    for (std::deque<int>::const_iterator it = deq.begin(); it != deq.end(); ++it)
    {
        std::cout << *it << " ";
    }
    std::cout << "\n";
}
const std::vector<int> &PmergeMe::getVec() const
{
    return vec;
}
void PmergeMe::printVec() const
{
    for (std::vector<int>::const_iterator it = vec.begin(); it != vec.end(); ++it)
    {
        std::cout << *it << " ";
    }
    std::cout << "\n";
}
int PmergeMe::Jacobsthal(int k)
{
    return (pow(2, k + 1) + pow(-1, k)) / 3;
}

void PmergeMe::mergeInsertSortVector(int left, int right)
{
    if (right - left <= 10)
    {
        std::sort(vec.begin() + left, vec.begin() + right + 1);
        return;
    }

    int mid = left + (right - left) / 2;
    mergeInsertSortVector(left, mid);
    mergeInsertSortVector(mid + 1, right);

    std::vector<int> temp;
    int i = left, j = mid + 1;
    while (i <= mid && j <= right)
    {
        if (vec[i] <= vec[j])
        {
            temp.push_back(vec[i++]);
        }
        else
        {
            temp.push_back(vec[j++]);
        }
    }
    while (i <= mid)
        temp.push_back(vec[i++]);
    while (j <= right)
        temp.push_back(vec[j++]);

    for (size_t k = 0; k < temp.size(); ++k)
    {
        vec[left + k] = temp[k];
    }
}

void PmergeMe::mergeInsertSortDeque(int left, int right)
{
    if (right - left <= 10)
    {
        std::sort(deq.begin() + left, deq.begin() + right + 1);
        return;
    }

    int mid = left + (right - left) / 2;
    mergeInsertSortDeque(left, mid);
    mergeInsertSortDeque(mid + 1, right);

    std::deque<int> temp;
    int i = left, j = mid + 1;
    while (i <= mid && j <= right)
    {
        if (deq[i] <= deq[j])
        {
            temp.push_back(deq[i++]);
        }
        else
        {
            temp.push_back(deq[j++]);
        }
    }
    while (i <= mid)
        temp.push_back(deq[i++]);
    while (j <= right)
        temp.push_back(deq[j++]);

    for (size_t k = 0; k < temp.size(); ++k)
    {
        deq[left + k] = temp[k];
    }
}
