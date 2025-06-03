#ifndef DATA_HPP
#define DATA_HPP

#include <string>

struct Data {
    int         i;
    double      d;
    char        c;
    Data(int ii = 42, double dd = 3.14, char cc = 'x')
        : i(ii), d(dd), c(cc) {}
};

#endif
