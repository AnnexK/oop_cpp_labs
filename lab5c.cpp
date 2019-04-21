#include "temp_polynomial.hpp"
#include "rational.hpp"

#include <iostream>

using namespace oop_labs;

int main(void)
{
    t_polynomial<my_rational> a = {{my_rational(5, 4), 0}, {my_rational(23, 10), 1}};

    t_polynomial<my_rational> b = a;
    t_polynomial<my_rational> c = a * b;
    // t_polynomial<int> c = a;
    
    std::cout << a << c << std::endl;
    return 0;
}
