#include "Span.hpp"

Span::Span(unsigned int n) : _maxSize(n)
{
}

Span::Span(Span const& other) : _maxSize(other._maxSize), _vector(other._vector)
{
}

Span& Span::operator=(Span const& other)
{
    if (this != &other)
    {
        _maxSize = other._maxSize;
        _vector = other._vector;
    }
    return *this;
}

Span::~Span()
{
}

void Span::addNumber(int number)
{
    if (_vector.size() >= _maxSize)
        throw std::exception();
    _vector.push_back(number);
}

int Span::shortestSpan() const
{
    if (_vector.size() < 2)
        throw std::exception();
    std::vector<int> copy = _vector;
    std::sort(copy.begin(), copy.end());
    int minSpan = copy[1] - copy[0];
    for (size_t i = 1; i + 1 < copy.size(); ++i)
    {
        int diff = copy[i + 1] - copy[i];
        if (diff < minSpan)
            minSpan = diff;
    }
    return minSpan;
}

int Span::longestSpan() const
{
    if (_vector.size() < 2)
        throw std::exception();
    std::vector<int> copy = _vector;
    std::sort(copy.begin(), copy.end());
    return copy.back() - copy.front();
}
