#ifndef ITER_HPP
#define ITER_HPP

#include <cstddef>

template <typename T>
void iter(T* arr, std::size_t len, void (*f)(T&))
{
    for (std::size_t i = 0; i < len; ++i)
        f(arr[i]);
}

template <typename T>
void iter(T const* arr, std::size_t len, void (*f)(T const&))
{
    for (std::size_t i = 0; i < len; ++i)
        f(arr[i]);
}

#endif
