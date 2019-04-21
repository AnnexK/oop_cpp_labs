#include <iostream>
#include "vectors.hpp"
#include "idexception.hpp"

using namespace oop_labs;

int main(void)
{
    /*
    my_vector test = 1;

    test.conPrint(); // {1, 0, 0} без explicit, ошибка с explicit
    */

    /*
    my_vector two_args(1, 2);
    two_args.conPrint(); // {1, 2, 0}
    */
    
    try
    {
	my_vector a;
	my_vector b(1, 2, 2);

	std::cout << a << '\n' << b << std::endl;

	std::cout << std::boolalpha << (a == b) << std::endl;
	std::cout << "Модуль вектора #" << b.get_id() << " = " << b.abs() << std::endl;   

	//a.norm(); ошибка нормирования
	b.norm();

	std::cout << b << std::endl;
   
	std::cout << "модуль вектора #" << b.get_id() << " = " << b.abs() << std::endl;

	my_vector c;

	std::cout << "Введите вектор #" << c.get_id() << std::endl;
	std::cin >> c;

	double k;
	std::cout << "Введите коэффициент k:" << std::endl;
	std::cin >> k;

	c *= k;

	my_vector d = c;

	my_vector e = c + b;
	my_vector f = c - b;
	my_vector g = c ^ b;
    
	std::cout << c << '\n' << d << '\n' << e << '\n' << f << '\n' << g << std::endl;

	std::cout << b << '\n' << c << std::endl;
	std::cout << "Скалярное произведение векторов #" << b.get_id() << " и #" << c.get_id() << " = "<< b * c << std::endl;
	std::cout << "sin(" << b.get_id() << '^' << c.get_id() << ") = " << sin(b, c) << std::endl;
	std::cout << "cos(" << b.get_id() << '^' << c.get_id() << ") = " << cos(b, c) << std::endl;	
	std::cout << b.get_id() << '^' << c.get_id() << " = " << angle(b, c) << " градусов." << std::endl;

	std::cout << "a ^ c = " << angle(a, c) << " градусов." << std::endl;
    }    
    catch(const id_exception& error)
    {
	std::cout << error.what() << ", vec_id = " << error.get_id() << std::endl;
    }
    
    return 0;
}
