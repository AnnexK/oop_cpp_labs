#include <iostream>
#include "math_matrix.hpp"
#include "math_vector.hpp"
#include <typeinfo>

using namespace oop_labs;

double kbinput(int a, int b)
{
    std::cout << "Введите A[" << a << "][" << b << "]: ";
    double ret;
    std::cin >> ret;
    return ret;    
}

double vkbinput(int a)
{
    std::cout << "Введите A[" << a << "]: ";
    double ret;
    std::cin >> ret;
    return ret;    
}

int main(void)
{
    // AbstractTable notConstructable(3); // создание невозможно: конструктор в protected
    
    try
    {
	// // Matrix M_A(3, 3, kbinput); // cons 0
	// // Matrix M_B(2, 3); // cons 1

	// std::cout << M_A << '\n' << M_B << '\n' << std::endl;
        // // std::cout << M_A * M_B << std::endl;

        // Vector V_A(3, vkbinput);
        // Vector V_P = M_A * V_A;

        // std::cout << V_A << '\n' << V_P << std::endl;
        // M_B.T();
       
        AbstractTable *malicious_vector = new Vector(3);

        std::cout << typeid(*malicious_vector).name() << typeid(Vector).name() << std::endl;
        AbstractTable *malicious_matrix = new Matrix(3, 2);
        ((Matrix *)malicious_matrix)->T(); // не компилирует без каста

        const Matrix cons(3,3); // проверить allocm и freem
        
        Matrix M_C(3, 3);
        Matrix M_Move = std::move(M_C);
        M_C = *malicious_matrix;
        /* Если не определить оператор присваивания как виртуальный,
           то ниже будет вызван оператор присваивания только базового класса.
           С учетом отсутствия проверок в базе это может привести к тому,
           что в вектор будет записана матрица, неприводимая к вектору. */

        Matrix assignable(10, 1, [](int i, int j) { return 0.0; });
        
        *malicious_vector = assignable;
        std::cout << *malicious_vector << std::endl;

        delete malicious_matrix;
        delete malicious_vector;
        // std::cout << M_A << V_A << std::endl;
        // V_A.T();// не скомпилит
    }
    catch (const id_exception& exc)
    {
	std::cerr << exc.what() << ", id = " << exc.get_id() << std::endl;
    }
    return 0;
}
