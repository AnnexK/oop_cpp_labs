#include "math_matrix.hpp"
#include <iomanip>
#include <cstring>

namespace oop_labs
{
    double mat_kbinput(int i, int j) // Ввод элементов с клавиатуры
    {
	double in;
	std::cout << "Введите mat[" << i <<  "][" << j << "]: ";
	std::cin >> in;
	return in;
    }

    Matrix::Row::Row(const Matrix& m, int i)
        : data(m.data + m.ncols * i), length(m.ncols), id(m.id)
    {}

    Matrix::Row::~Row(void) {}

    double& Matrix::Row::operator [](int i)
    {
        if (i < 0 || i >= length)
            throw id_exception("Индекс выходит за границы", id);
        return data[i];
    }

    double Matrix::Row::operator [](int i) const
    {
        if (i < 0 || i >= length)
            throw id_exception("Индекс выходит за границы", id);
        return data[i];
    }
    
    Matrix::Matrix(int m, filler fun):
	AbstractTable::AbstractTable(m, m, fun)
    {
	std::cout << "Конструктор матрицы #" << id << std::endl;
    }
    
    Matrix::Matrix(int m, int n, filler fun):
	AbstractTable::AbstractTable(m, n, fun)
    {
	std::cout << "Конструктор матрицы #" << id << std::endl;
    }
    
    Matrix::Matrix(const Matrix& other):
	AbstractTable::AbstractTable(other)
    {
	std::cout << "Конструктор матрицы #" << id << std::endl;
    }

    Matrix::Matrix(Matrix&& other):
	AbstractTable::AbstractTable(other)
    {
	std::cout << "Конструктор матрицы #" << id << std::endl;
    }
    
    Matrix::Matrix(const AbstractTable& other):
	AbstractTable::AbstractTable(other)
    {
	std::cout << "Конструктор матрицы #" << id << std::endl;
    }
    
    Matrix::Matrix(AbstractTable&& other):
	AbstractTable::AbstractTable(other)
    {
	std::cout << "Конструктор матрицы #" << id << std::endl;
    }

    Matrix::Matrix(double *arr, int m, int n)
        : AbstractTable::AbstractTable(arr, m, n)
    {
	std::cout << "Конструктор матрицы #" << id << std::endl;        
    }
    
    Matrix::~Matrix(void)
    {
	std::cout << "Деструктор матрицы #" << id << std::endl;
    }

    Matrix::Row Matrix::operator [](int i)
    {
        if (i < 0 || i >= nrows)
            throw id_exception("Индекс выходит за границы", id);
        return Matrix::Row(*this, i);
    }

    const Matrix::Row Matrix::operator [](int i) const
    {
        if (i < 0 || i >= nrows)
            throw id_exception("Индекс выходит за границы", id);
        return Matrix::Row(*this, i);
    }

    const Matrix& Matrix::operator=(const Matrix& other)
    {
        AbstractTable::operator=(other);
        return *this;
    }

    Matrix& Matrix::operator=(Matrix&& other)
    {
        AbstractTable::operator=(other);
        return *this;
    }
  
    const Matrix& Matrix::operator=(const AbstractTable& other)
    {
        AbstractTable::operator=(other);
        return *this;
    }

    Matrix& Matrix::operator=(AbstractTable&& other)
    {
        AbstractTable::operator=(other);
        return *this;
    }  

    Matrix transpose(const Matrix& a)
    {
        Matrix ret = a;
        ret.T();
        return ret;
    }
}
