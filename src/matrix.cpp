#include "matrix.hpp"

#include <cstring>
#include <iomanip>
#include <ios>
#include <stdexcept>

namespace oop_labs
{
    unsigned int my_matrix::count = 0;
    
    /* Алгоритмы заполнения матрицы ----------------------------------------- */
    
    double Emat(int i, int j) { return i == j ? 1.0 : 0.0; } // Единичная матрица
   
    double kbinput(int i, int j) // Ввод элементов с клавиатуры
    {
	double in;
	std::cout << "Введите mat[" << i <<  "][" << j << "]: ";
	std::cin >> in;
	return in;
    }
    
    double zero(int i, int j) { return 0.0; } // Тождественный ноль

    /* Методы прокси-класса ------------------------------------------------- */

    my_matrix::mrow::mrow(const my_matrix& mat, int nrow)
        : data(mat.data + mat.ncols * nrow), length(mat.ncols), id(mat.id) {}
    
    my_matrix::mrow::~mrow(void) {}

    double& my_matrix::mrow::operator [](int index)
    {
	if (index < 0 || index >= length)
	    throw id_exception("Индекс выходит за границы", id);

	return data[index];
    }

    double my_matrix::mrow::operator [](int index) const
    {
	if (index < 0 && index >= length)
	    throw id_exception("Индекс выходит за границы", id);

	return data[index];
    }

    /* Методы класса матриц ------------------------------------------------- */
    
    void my_matrix::allocm(int m, int n)
    {
	if (((m == 0) ^ (n == 0)) || (m < 0) || (n < 0)) // одна из размерностей равна 0 ИЛИ одна из размерностей меньше 0
	    throw std::bad_alloc();
	data = nullptr;

	if (m)
	    data = new double [n * m];
    }

    void my_matrix::freem(void)
    {
	if (data) delete[] data;
    }
    
    my_matrix::my_matrix(int m, int n, double (*fun)(int, int))
	: nrows(m), ncols(n), id(count)
    {
	std::cout << "Конструктор матрицы #" << id << std::endl;
	try
	{
	    allocm(m, n);
	}
	catch(const std::bad_alloc&)
	{
	    throw id_exception("Ошибка при выделении памяти", count);
	}

	if (fun != nullptr)
	{
	    for (int i = 0; i < m; i++)
	    {
		for (int j = 0; j < n; j++)
		{
		    data[i * ncols + j] = fun(i, j);
		}
	    }
	}
        count++;
    }

    my_matrix::my_matrix(int m, double (*fun)(int, int))
	: my_matrix(m, m, fun)
    {}
    
    my_matrix::my_matrix(const my_matrix& cp)
	: my_matrix(cp.nrows, cp.ncols, nullptr)
    {
	for (int i = 0; i < nrows; i++) // rows
	{
	    for (int j = 0; j < ncols; j++) // columns
	    {
		data[i * ncols + j] = cp.data[i * cp.ncols + j];
	    }
	}
    }

    my_matrix::my_matrix(my_matrix&& mv)
	: data(mv.data), nrows(mv.nrows), ncols(mv.ncols), id(count)
    {
	std::cout << "Конструктор перемещения матрицы #" << id << std::endl;
	
	mv.data = nullptr;
	mv.nrows = 0;
	mv.ncols = 0;

	count++;
    }
    
    my_matrix::~my_matrix(void)
    {
	std::cout << "Деструктор матрицы #" << id << std::endl;
        freem();
    }

    my_matrix& my_matrix::T(void)
    {
	if (!isNull())
	{
            for (int i = 0; i < ncols; i++)
            {
                double *cur = data + i * nrows;
                double swp;
	    
                for (int j = 1; j < nrows; j++)
                {
                    int cycle = (ncols - i) * j;
                    swp = cur[cycle];
                    for (int k = cycle; k > j; k--)
                    {
                        cur[k] = cur[k - 1];
                    }
                    cur[j] = swp;
                }
            }

            std::swap(nrows, ncols);
        }
        return *this;
    }
    
    unsigned int my_matrix::get_id(void) const
    {
	return id;
    }

    unsigned int my_matrix::get_count(void)
    {
	return count;
    }

    int my_matrix::get_nrows(void) const
    {
	return nrows;    
    }

    int my_matrix::get_ncols(void) const
    {
	return ncols;
    }

    bool my_matrix::isNull(void) const
    {
	return !nrows && !ncols;
    }
    
    bool my_matrix::isMultipliable(const my_matrix& b) const
    {
	return (ncols == b.nrows);
    }

    bool my_matrix::isSummable(const my_matrix& b) const
    {
	return (nrows == b.nrows && ncols == b.ncols);
    }

    double my_matrix::min(void) const
    {
	if (isNull())
	    throw id_exception("Матрица пуста", id);
	
	double ret = *data;
	for (int i = 1; i < nrows * ncols; i++)
	{
	    if (ret > data[i]) ret = data[i];
	}

	return ret;
    }

    double my_matrix::max(void) const
    {
	if (isNull())
	    throw id_exception("Матрица пуста", id);
	
	double ret = *data;
	for (int i = 1; i < nrows * ncols; i++)
	{
	    if (ret < data[i]) ret = data[i];
	}

	return ret;
    }

    my_matrix::mrow my_matrix::operator [](int idx)
    {
	if (idx < 0 || idx >= nrows)
	    throw id_exception("Индекс выходит за границы", id);

	return my_matrix::mrow(*this, idx);
    }

    const my_matrix::mrow my_matrix::operator [](int idx) const
    {
	if (idx < 0 || idx >= nrows)
	    throw id_exception("Индекс выходит за границы", id);

	return my_matrix::mrow(*this, idx);
    }

    const my_matrix& my_matrix::operator =(const my_matrix& b)
    {
	if (this != &b)
	{
	    double *newdata = nullptr;
	    int total = b.nrows * b.ncols;

	    if (ncols * nrows != total)
	    {
		try
		{
		    if (total)
			newdata = new double[total];
		}
		catch (const std::bad_alloc&)
		{
		    throw id_exception("Ошибка при выделении памяти", id);
		}
	    }
	    else newdata = data;
	    
	    for (int i = 0; i < total; i++)
	    {
		newdata[i] = b.data[i];
	    }

	    if (newdata != data)
	    {
	        freem();
		data = newdata;
	    }
	}
	return *this;
    }

    my_matrix& my_matrix::operator =(my_matrix&& mv)
    {
	if (this != &mv)
	{
	    std::swap(data, mv.data);
	    std::swap(nrows, mv.nrows);
	    std::swap(ncols, mv.ncols);
	}

	return *this;
    }
    
    my_matrix& my_matrix::operator +=(const my_matrix& b)
    {
	if (!isSummable(b))
	    throw id_exception("Несоответствие размеров матриц", b.id);

	int total = nrows * ncols;
	for (int i = 0; i < total; i++)
	{
	    data[i] += b.data[i];
	}

	return *this;
    }

    my_matrix& my_matrix::operator -=(const my_matrix& b)
    {
	if (!isSummable(b))
	    throw id_exception("Несоответствие размеров матриц", b.id);

	int total = nrows * ncols;
	for (int i = 0; i < total; i++)
	{
	    data[i] -= b.data[i];
	}

	return *this;
    }

    my_matrix& my_matrix::operator *=(const my_matrix& b)
    {
	int l = nrows, m = ncols, n = b.ncols;
	if (!isMultipliable(b))
	    throw id_exception("Несоответствие размеров матриц", b.id);

        my_matrix tmp(l, n, zero);
	
	for (int i = 0; i < l; i++)
	{
	    for (int j = 0; j < n; j++)
	    {
		for (int k = 0; k < m; k++)
		{
		    tmp.data[i * n + j] += data[i * m + k] * b.data[k * n + j];
		}
	    }
	}

        *this = std::move(tmp);
	
	return *this;
    }

    my_matrix& my_matrix::operator *=(double k)
    {
	for (int i = 0; i < nrows * ncols; i++)
	{
	    data[i] *= k;	
	}

	return *this;
    }

    my_matrix transpose (const my_matrix& op1)
    {
	my_matrix ret = op1;
	ret.T();
	return ret;
    }
    
    my_matrix operator +(const my_matrix& op1, const my_matrix& op2)
    {
	my_matrix ret = op1;
	ret += op2;
	return ret;
    }

    my_matrix operator -(const my_matrix& op1, const my_matrix& op2)
    {
	my_matrix ret = op1;
	ret -= op2;
	return ret;
    }

    my_matrix operator *(const my_matrix& op1, const my_matrix& op2)
    {
	my_matrix ret = op1;
	ret *= op2;
	return ret;
    }

    my_matrix operator *(const my_matrix& op1, double op2)
    {
	my_matrix ret = op1;
	ret *= op2;
	
	return ret;
    }

    my_matrix operator *(double op1, const my_matrix& op2)
    {
	my_matrix ret = op2;
	ret *= op1;
	return ret;
    }

    std::ostream& operator <<(std::ostream& out, const my_matrix& mat)
    {	
        int w = out.width();
	if (!w) w = 12; // значение по умолчанию
	    
	int m = mat.get_nrows();
	int n = mat.get_ncols();

	if (mat.isNull()) return out << std::setw(0) << "[]" << std::endl;
	for (int i = 0; i < m; i++)
	{
	    out << std::setw(0) << '|';
	    for (int j = 0; j < n; j++)
	    {
		out << std::setw(w) << mat[i][j] << (j < n - 1 ? ", " : "\0");
	    }
	    out << "|\n";
	}

	return out;
    }
}
