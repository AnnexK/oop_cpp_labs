#include "math_vector.hpp"
#include "idexception.hpp"
#include <cstring>
#include <iomanip>

namespace oop_labs
{
    Vector::Vector(int len, const vfiller& fun):
	AbstractTable::AbstractTable(len, len ? 1 : 0) // создание канонического вектора 0 x 0 или len x 1
    {
        if (fun)
        {
            for (int i = 0; i < len; ++i)
            {
                data[i] = fun(i);
            }
        }
	std::cout << "Конструктор вектора #" << id << std::endl;
    }

    Vector::Vector(const Vector& other)
	: Vector(other.data, other.nrows)
    {}

    Vector::Vector(Vector&& other)
	: AbstractTable(other)
    {
	std::cout << "Конструктор вектора #" << id << std::endl;
    }

    Vector::Vector(const AbstractTable& other)
	: AbstractTable(other)
    {
        if (nrows > 1 && ncols > 1)
            throw id_exception("Невозможно построить вектор из данного объекта", other.get_id());

        if (nrows == 1)
            T();
        
	std::cout << "Конструктор вектора #" << id << std::endl;
    }
    
    Vector::Vector(AbstractTable&& other):
	AbstractTable::AbstractTable(other)
    {
        if (nrows > 1 && ncols > 1)
            throw id_exception("Невозможно построить вектор из данного объекта", other.get_id());

        if (nrows == 1)
            T();
        
	std::cout << "Конструктор вектора #" << id << std::endl;
    }

    Vector::Vector(double *arr, int m)
        : Vector(m, [arr](int i) { return arr[i]; })
    {}
    
    Vector::~Vector(void)
    {
	std::cout << "Деструктор вектора #" << id << std::endl;
    }

    const Vector& Vector::operator=(const Vector& other)
    {
        AbstractTable::operator =(other);
        return *this;
    }

    Vector& Vector::operator=(Vector&& other)
    {
        AbstractTable::operator =(other);
        return *this;
    }

    const Vector& Vector::operator=(const AbstractTable& other)
    {
        if (this != &other)
        {
            /* Проверка на преобразование other к вектору.
               Создадим вектор размера 1x1.
               Если other является вектором-строкой 1xn, то можно умножить tmp на other.
               Если other является вектором-столбцом nx1, то можно умножить other на tmp. */
            Vector tmp(1);
        
            bool transpose = tmp.isMultipliable(other), no_transpose = other.isMultipliable(tmp);
            if (transpose || no_transpose || other.isNull()) // можно произвести присваивание
            {
                AbstractTable::operator =(other);
                if (transpose) // необходимо транспонирование
                    T();
            }
            else throw id_exception("Невозможно преобразование из базы в вектор", other.get_id());
        }
        return *this;
    }

    Vector& Vector::operator=(AbstractTable&& other)
    {
        Vector tmp(1);
        
        bool transpose = tmp.isMultipliable(other), no_transpose = other.isMultipliable(tmp);
        if (transpose || no_transpose || other.isNull()) // можно произвести присваивание
        {
            AbstractTable::operator =(other);
            if (transpose) // необходимо транспонирование
                T();
        }
        else throw id_exception("Невозможно преобразование из базы в вектор", other.get_id());
        
        return *this;
    }
    
    int Vector::get_length(void) const
    {
        return nrows;
    }

    double& Vector::operator [](int i)
    {
        if (i < 0 || i >= nrows)
            throw id_exception("Индекс выходит за границы", id);

        return data[i];
    }

    double Vector::operator [](int i) const
    {
        if (i < 0 || i >= nrows)
            throw id_exception("Индекс выходит за границы", id);

        return data[i];
    }

    bool Vector::isSummable(const AbstractTable& b) const
    {
        Vector tmp(nrows);

        bool notrans = tmp.AbstractTable::isSummable(tmp);
        tmp.T();
        bool trans = tmp.AbstractTable::isSummable(b);        

        return trans || notrans;
    }
    
    bool Vector::isMultipliable(const AbstractTable& b) const
    {
        // можно умножить вектор-строку на table
        Vector tmp(nrows);
        tmp.T();
        bool trans = tmp.AbstractTable::isMultipliable(b);

        return trans; 
    }
    
    Vector& Vector::operator +=(const AbstractTable& b)
    {
        if (AbstractTable::isSummable(b))
        {
            AbstractTable::operator +=(b);
        }
        else
        {
            T();
            try
            {
                AbstractTable::operator +=(b);                
            }
            catch(const id_exception& e)
            {
                std::cout << e.what() << std::endl;
            }
            T();
        }
        return *this;
    }

    Vector& Vector::operator -=(const AbstractTable& b)
    {
        if (AbstractTable::isSummable(b))
        {
            AbstractTable::operator -=(b);
        }
        else
        {
            T();
            try
            {
                AbstractTable::operator -=(b);                
            }
            catch(const id_exception& e)
            {
                std::cout << e.what() << std::endl;
            }
            T();
        }
        return *this;
    }

    Vector& Vector::operator *=(const AbstractTable& b)
    {
        T();
        
        try
        {
            AbstractTable::operator *=(b);
        }
        catch (const id_exception& e)
        {
            std::cout << e.what() << std::endl;
        }
        
        T();
        return *this;
    }
}
