#ifndef SPAN_HPP
#define SPAN_HPP

#include <vector>
#include <algorithm>
#include <exception>

class Span
{
public:
    Span(unsigned int n);
    Span(Span const& other);
    Span& operator=(Span const& other);
    ~Span();

    void addNumber(int number);
    template <typename InputIt>
    void addNumber(InputIt begin, InputIt end)
    {
        if (std::distance(begin, end) + static_cast<long>(_vector.size()) > static_cast<long>(_maxSize))
            throw std::exception();
        _vector.insert(_vector.end(), begin, end);
    }

    int shortestSpan() const;
    int longestSpan() const;

private:
    Span();
    unsigned int _maxSize;
    std::vector<int> _vector;
};

#endif
