#include "vectors.hpp"
#include "idexception.hpp"
#include <cmath>
#include <limits>
#include <cstring>



namespace oop_labs
{
    /* Определение методов класса my_vector--------------------- */
    unsigned int my_vector::count = 0;    
    my_vector::my_vector(double x, double y, double z)
    {
	std::cout << "Конструктор вектора #" << count << std::endl;
	this->x = x;
	this->y = y;
	this->z = z;
	id = count++;
    }

    my_vector::my_vector(const my_vector& cp)
    {
	std::cout << "Конструктор копирования вектора #" << count << std::endl;
	x = cp.x;
	y = cp.y;
	z = cp.z;
	id = count++;
    }

    my_vector::~my_vector(void)
    {
	std::cout << "Деструктор вектора #" << id << std::endl;
    }
    
    std::istream& operator >>(std::istream& in, my_vector& vec) // Оператор ввода
    {
	in >> vec.x >> vec.y >> vec.z;

	return in;
    }

    std::ostream& operator <<(std::ostream& out, const my_vector& vec) // Оператор вывода
    {
	return out << "Вектор #" << vec.id << ":\n" << '{' << vec.x << ", " << vec.y << ", " << vec.z << '}';
    }

    my_vector& my_vector::operator =(const my_vector& rvec)
    {
	this->x = rvec.x;
	this->y = rvec.y;
	this->z = rvec.z;
	return *this;
    }

    double my_vector::abs(void) const { return sqrt(x * x + y * y + z * z); } // Получить длину (модуль) вектора

    my_vector& my_vector::operator *=(double scl)
    {
	this->x *= scl;
	this->y *= scl;
	this->z *= scl;

	return *this;
    }

    my_vector& my_vector::norm(void)
    {
	double len = abs();

	if (len < std::numeric_limits<double>::epsilon()) // len == 0
	    throw id_exception("Ошибка нормирования: abs = 0", id);
	x /= len;
	y /= len;
	z /= len;

	return *this;
    }

    /* Внешние функции ----------------------------------------- */

    bool operator ==(const my_vector& op1, const my_vector& op2)
    {
	double dx = fabs(op1.get_x() - op2.get_x()),
	    dy = fabs(op1.get_y() - op2.get_y()),
	    dz = fabs(op1.get_z() - op2.get_z()),
	    eps = std::numeric_limits<double>::epsilon();
	return dx < eps && dy < eps && dz < eps;	    
    }
    
    my_vector operator +(const my_vector& op1, const my_vector& op2) // Сложение векторов
    {
	double x = op1.get_x() + op2.get_x(),
	    y = op1.get_y() + op2.get_y(),
	    z = op1.get_z() + op2.get_z();

	return my_vector(x, y, z);
    }

    my_vector operator -(const my_vector& op1, const my_vector& op2) // Вычитание векторов
    {
	double x = op1.get_x() - op2.get_x(),
	    y = op1.get_y() - op2.get_y(),
	    z = op1.get_z() - op2.get_z();	

	return my_vector(x, y, z);
    }

    my_vector operator ^(const my_vector& op1, const my_vector& op2) // ВП векторов
    {    
	double x1 = op1.get_x(), y1 = op1.get_y(), z1 = op1.get_z();
	double x2 = op2.get_x(), y2 = op2.get_y(), z2 = op2.get_z();
    
	my_vector res(y1 * z2 - y2 * z1,
		      z1 * x2 - z2 * x1,
		      x1 * y2 - x2 * y1);

	return res;
    }

    double operator *(const my_vector& op1, const my_vector& op2) // СП векторов
    {
	double x1 = op1.get_x(), y1 = op1.get_y(), z1 = op1.get_z();
	double x2 = op2.get_x(), y2 = op2.get_y(), z2 = op2.get_z();
    
	return x1 * x2 + y1 * y2 + z1 * z2;
    }

    double cos(const my_vector& op1, const my_vector& op2) // Косинус угла между векторами
    {
	double eps = std::numeric_limits<double>::epsilon();
	double abs1 = op1.abs(), abs2 = op2.abs();
    
	if (abs1 < eps || abs2 < eps) // abs == 0
	    throw id_exception("Ошибка при вычислении cos",
			       abs1 < eps ? op1.get_id() : op2.get_id()); // а вообще cos(0)
	
	return op1 * op2 / (op1.abs() * op2.abs());
    }

    double sin(const my_vector& op1, const my_vector& op2) // Синус угла между векторами
    {
	double eps = std::numeric_limits<double>::epsilon();
	double abs1 = op1.abs(), abs2 = op2.abs();

	if (abs1 < eps || abs2 < eps) // abs == 0
	    throw id_exception("Ошибка при вычислении sin",
			       abs1 < eps ? op1.get_id() : op2.get_id()); // а вообще sin(0)
    
	my_vector op3 = op1 ^ op2;
	return op3.abs() / (op1.abs() * op2.abs());
    }

    double angle(const my_vector& op1, const my_vector& op2) // Угол между векторами [-180o; +180o]
    {
	try
	{
	    return 180 * atan2(sin(op1, op2), cos(op1, op2)) / M_PI;
	}
	catch (const id_exception& angles)
	{
	    throw id_exception("Ошибка при вычислении угла между векторами", angles.get_id());
	}
    }
}
