#include "rational.hpp"
#include "idexception.hpp"

#include <iostream>

using namespace oop_labs;

int main(void)
{
    try
    {
	my_rational a; // 0/1
	my_rational b = -3; // -3/1

	my_rational c(7, 2); // 7/2
	my_rational d(8, 2); // 4/1
	my_rational e(2, 8); // 1/4

	// my_rational err_null1(0, 0); // error
	    
	std::cout << a << ' ' << b << ' ' << c << ' ' << d << ' ' << e << std::endl;

	// std::cout << b << " / " << a << " = " << b / a << std::endl; // division by 0 error

	std::cout << "(C - E) * (D + A / B) = " << (c - e) * (d + a / b) << std::endl;

	a = 6;

	std::cout << a * b << ' ' << a / b << ' ' << a + b << ' ' << a - b << ' ' << b - a << std::endl;

	auto proper_frac_c = c.decompose();
	std::cout << proper_frac_c.first << ' ' << proper_frac_c.second << std::endl;

	c *= -1;
	proper_frac_c = c.decompose();
	
	std::cout << proper_frac_c.first << ' ' << proper_frac_c.second << std::endl;
	
	auto proper_frac_d = d.decompose();
	std::cout << proper_frac_d.first << ' ' << proper_frac_d.second << std::endl;

	e *= 16;

	std::cout << (d == e) << ' ' << (d < e) << ' ' << (d > e) << ' ' << std::endl;
    }
    catch (const id_exception& ex)
    {
	std::cerr << ex.what() << ", rat_id = " << ex.get_id() << std::endl;
    }
    return 0;
}
