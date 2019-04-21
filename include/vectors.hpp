#ifndef OOP_LAB1_VECTORS_HEADER
#define OOP_LAB1_VECTORS_HEADER

#include <iostream>

namespace oop_labs
{
    class my_vector
    {
    private:
	double x, y, z;
	unsigned int id;
	static unsigned int count;
    public:
	explicit my_vector(double x = 0.0, double y = 0.0, double z = 0.0); // Стд конструктор с параметрами по умолчанию

	my_vector(const my_vector&); // Конструктор копирования
	~my_vector(void); // Деструктор
    
        double get_x(void) const;  // get-функции для каждого поля
        double get_y(void) const;
        double get_z(void) const;

        unsigned int get_id(void) const;
        static unsigned int get_count(void);
    
        void set_x(double x);  // set-функции для каждого поля
        void set_y(double y);
        void set_z(double z);

	friend std::ostream& operator <<(std::ostream& out, const my_vector& vec); // Оператор вывода   
	friend std::istream& operator >>(std::istream& in, my_vector& vec); // Оператор ввода
       
	my_vector& operator =(const my_vector& rvec);
    
        double abs(void) const; // Получить длину (модуль) вектора
	my_vector& operator *=(double); // Умножить вектор на скаляр
	my_vector& norm(void); // Нормировать вектор
    };

    inline double my_vector::get_x(void) const { return x; } // get-функции для каждого поля
    inline double my_vector::get_y(void) const { return y; }
    inline double my_vector::get_z(void) const { return z; }

    inline unsigned int my_vector::get_id(void) const { return id; }
    inline unsigned int my_vector::get_count(void) { return count; }
    
    inline void my_vector::set_x(double x) { this->x = x; } // set-функции для каждого поля
    inline void my_vector::set_y(double y) { this->y = y; }	
    inline void my_vector::set_z(double z) { this->z = z; }

    bool operator ==(const my_vector& op1, const my_vector& op2);
    my_vector operator +(const my_vector& op1, const my_vector& op2); // Сложение векторов
    my_vector operator -(const my_vector& op1, const my_vector& op2); // Вычитание векторов
    my_vector operator ^(const my_vector& op1, const my_vector& op2); // ВП векторов
    double operator *(const my_vector& op1, const my_vector& op2); // СП векторов
    double cos(const my_vector& op1, const my_vector& op2); // Косинус угла между векторами
    double sin(const my_vector& op1, const my_vector& op2); // Синус угла между векторами
    double angle(const my_vector& op1, const my_vector& op2); // Угол между векторами [-pi; pi]
}
#endif
