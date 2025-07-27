#include "PmergeMe.hpp"
#include <iostream>
#include <sstream>
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
            std::exit(1);
        }
        long value = std::atol(token.c_str());
        if (value <= 0)
        {
            std::cerr << "Error" << std::endl;
            std::exit(1);
        }
        vec.push_back(static_cast<int>(value));
        deq.push_back(static_cast<int>(value));
    }
}
PmergeMe::PmergeMe(const PmergeMe &other) : vec(other.vec), deq(other.deq) {}
PmergeMe &PmergeMe::operator=(const PmergeMe &other)
{
    if (this != &other)
    {
        vec = other.vec;
        deq = other.deq;
    }
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
const std::deque<int> &PmergeMe::getDeq() const { return deq; }
void PmergeMe::printDeq() const
{
    for (std::deque<int>::const_iterator it = deq.begin(); it != deq.end(); ++it)
        std::cout << *it << " ";
    std::cout << "\n";
}
const std::vector<int> &PmergeMe::getVec() const { return vec; }
void PmergeMe::printVec() const
{
    for (std::vector<int>::const_iterator it = vec.begin(); it != vec.end(); ++it)
        std::cout << *it << " ";
    std::cout << "\n";
}
int PmergeMe::Jacobsthal(int k)
{
    std::vector<size_t> order;
    std::set<size_t> added;
    size_t j = 1;

    while (true)
    {
        int idx = (j == 0) ? 1 : Jacobsthal(j);
        if (idx >= static_cast<int>(n))
            break;

        if (added.find(idx) == added.end())
        {
            order.push_back(idx);
            added.insert(idx);
        }

        ++j;
    }

    for (size_t i = 0; i < n; ++i)
    {
        if (added.find(i) == added.end())
        {
            order.push_back(i);
            added.insert(i);
        }
    }

    return order;
}


void PmergeMe::fordJohnsonSortVector()
{
    fordJohnsonSort(vec);
}

void PmergeMe::fordJohnsonSortDeque()
{
    fordJohnsonSort(deq);
}

void PmergeMe::fordJohnsonSort(std::vector<int> &data)
{
    if (data.size() < 2)
        return;

    std::vector<int> mins, maxs;
    size_t i = 0;
    for (; i + 1 < data.size(); i += 2)
    {
        if (data[i] < data[i + 1])
        {
            mins.push_back(data[i]);
            maxs.push_back(data[i + 1]);
        }
        else
        {
            mins.push_back(data[i + 1]);
            maxs.push_back(data[i]);
        }
    }

    int last = -1;
    bool hasLast = false;
    if (i < data.size())
    {
        last = data[i];
        hasLast = true;
    }

    fordJohnsonSort(mins);

    std::vector<size_t> insertionOrder = getJacobsthalInsertionOrder(maxs.size());

    for (size_t k = 0; k < insertionOrder.size(); ++k)
    {
        size_t j = insertionOrder[k];
        if (j >= maxs.size())
            continue;

        std::vector<int>::iterator pos = std::upper_bound(mins.begin(), mins.end(), maxs[j]);
        mins.insert(pos, maxs[j]);
    }

    if (hasLast)
    {
        std::vector<int>::iterator pos = std::upper_bound(mins.begin(), mins.end(), last);
        mins.insert(pos, last);
    }

    data = mins;
}

void PmergeMe::fordJohnsonSort(std::deque<int> &data)
{
    if (data.size() < 2)
        return;

    std::deque<int> mins, maxs;
    size_t i = 0;
    for (; i + 1 < data.size(); i += 2)
    {
        if (data[i] < data[i + 1])
        {
            mins.push_back(data[i]);
            maxs.push_back(data[i + 1]);
        }
        else
        {
            mins.push_back(data[i + 1]);
            maxs.push_back(data[i]);
        }
    }
    int last = -1;
    bool hasLast = false;
    if (i < data.size())
    {
        last = data[i];
        hasLast = true;
    }

    std::vector<int> minsVec(mins.begin(), mins.end());
    fordJohnsonSort(minsVec);

    mins.assign(minsVec.begin(), minsVec.end());

    std::vector<size_t> insertionOrder = getJacobsthalInsertionOrder(maxs.size());

    for (size_t k = 0; k < insertionOrder.size(); ++k)
    {
        size_t j = insertionOrder[k];
        if (j >= maxs.size())
            continue;

        std::deque<int>::iterator pos = std::upper_bound(mins.begin(), mins.end(), maxs[j]);
        mins.insert(pos, maxs[j]);
    }

    if (hasLast)
    {
        std::deque<int>::iterator pos = std::upper_bound(mins.begin(), mins.end(), last);
        mins.insert(pos, last);
    }

    data = mins;
}

