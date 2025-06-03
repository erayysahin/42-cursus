#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <cstddef>
#include <exception>

template <typename T>
class Array
{
public:
    Array() : _size(0), _data(0) {}

    Array(unsigned int n) : _size(n), _data(0)
    {
        if (_size > 0)
            _data = new T[_size];
    }

    Array(Array const& other) : _size(other._size), _data(0)
    {
        if (_size > 0)
        {
            _data = new T[_size];
            for (std::size_t i = 0; i < _size; ++i)
                _data[i] = other._data[i];
        }
    }

    Array& operator=(Array const& other)
    {
        if (this != &other)
        {
            clear();
            _size = other._size;
            if (_size > 0)
            {
                _data = new T[_size];
                for (std::size_t i = 0; i < _size; ++i)
                    _data[i] = other._data[i];
            }
        }
        return *this;
    }

    ~Array()
    {
        clear();
    }

    T& operator[](std::size_t index)
    {
        if (index >= _size)
            throw std::exception();
        return _data[index];
    }

    T const& operator[](std::size_t index) const
    {
        if (index >= _size)
            throw std::exception();
        return _data[index];
    }

    std::size_t size() const
    {
        return _size;
    }

private:
    std::size_t _size;
    T* _data;

    void clear()
    {
        if (_data)
            delete[] _data;
        _data = 0;
        _size = 0;
    }
};

#endif
