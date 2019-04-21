#include "matrix.hpp"
#include <iostream>
#include <iomanip>

using namespace oop_labs;

int main(void)
{
    // my_matrix t1 = 2;
    // std::cout << t1 << std::endl;
    // std::cout << 3.24 << std::endl;
    try
    {
	// const my_matrix constm(3, Emat);
        my_matrix a; // cons 0
	my_matrix b(2); // cons 1
	my_matrix c(3, 2, kbinput); // cons 2

	// (a = b) = constm; //если = вернет const T&, то это не скомпилируется
	// std::cout << a << b << constm << std::endl;
	
    	std::cout << a << b << c << std::endl;

    	b = my_matrix(3, 2, kbinput);	// cons 3 assign dest 3

    	std::cout << b + c << std::endl; // consc 4 consm 5 dest 4 out dest 5
    	std::cout << b - c << std::endl; // consc 6 consm 7 dest 6 out dest 7
    	std::cout << c - b << std::endl; // consc 8 consm 9 dest 8 out dest 9
	
    	c *= 2.5; // nop
    	std::cout << c << std::endl;

    	c = c * 2.5; // consc 10 consm 11 dest 10 assign dest 11
    	std::cout << c << std::endl;

    	c.T(); // nop
    	std::cout << c << std::endl;

    	std::cout << std::fixed << std::setw(20) << b * c << std::setw(17) << c * b << std::endl; // consc 12 consm 13 dest 12 consc 14 consm 15 dest 14 dest 15 dest 13
    } // dest 2 dest 1 dest 0
    catch (const id_exception& e)
    {
	std::cerr << e.what() << ", mat_id = " << e.get_id() << std::endl;
    }
    
    return 0;
}
