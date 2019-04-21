#include "polynomial.hpp"

using namespace oop_labs;

int main(void)
{    
    my_polynomial a({{2.0, 0}, {0.0, 1}, {9.2, 2}, {5.4, 3}});
    my_polynomial b;
    my_polynomial c(5, poly_kbinput);
    my_polynomial nonexplicit = 4.0;

    std::cout << nonexplicit << std::endl;
    
    try
    {
	std::cout << a + c << '\n' << a - c << '\n' <<  a * c << std::endl;

	auto div_result = modf(c, a);
	std::cout << div_result.first << ' ' << div_result.second << std::endl;
	// std::cout << modf(a, b).first << std::endl; // ошибка деления на 0

	my_polynomial squared = a * a;
	std::cout << a << '\n' << squared << std::endl;
    }
    catch(const id_exception& e)
    {
	std::cerr << e.what() << std::endl;
    }

    return 0;
}
