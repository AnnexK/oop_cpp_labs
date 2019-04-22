#include "math_abstract.hpp"
#include "idexception.hpp"

#include <cstring>
#include <stdexcept>
#include <iomanip>
#include <typeinfo>

namespace oop_labs
{
    /* Алгоритмы заполнения матрицы ----------------------------------------- */

    double zero(int a, int b)
    {
        return 0.0;
    }
    
    unsigned int AbstractTable::count = 0;

    void AbstractTable::allocm(int m, int n)
    {
        data = nullptr;
	if (((m == 0) ^ (n == 0)) || (m < 0) || (n < 0)) // ровно одна из размерностей равна 0 ИЛИ одна из размерностей меньше 0
	    throw std::bad_alloc();

	if (m)
	    data = new double [n * m];
    }

    void AbstractTable::freem(void)
    {
        if (data) delete[] data;
    }

    AbstractTable::AbstractTable(int m, filler fun)
        : AbstractTable::AbstractTable(m, m, fun)
    {}
    
    AbstractTable::AbstractTable(int m, int n, filler fun)
	: nrows (m), ncols (n), id (count)
    {
	try
	{
	    allocm(m, n);
	}
	catch(const std::bad_alloc&)
	{
	    throw id_exception("Ошибка при выделении памяти", count);
	}
        if (fun) // true если есть что вызывать
        {
            for (int i = 0; i < m; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    data[i * n + j] = fun(i, j);
                }
            }
        }
        
        count++;
    }

    AbstractTable::AbstractTable(const AbstractTable& cp)
        : AbstractTable(cp.data, cp.nrows, cp.ncols)
    {}

    AbstractTable::AbstractTable(AbstractTable&& mv)
	: data(mv.data), nrows(mv.nrows), ncols(mv.ncols), id(count)
    {
	mv.data = nullptr;
	mv.nrows = 0;
	mv.ncols = 0;
        count++;
    }

    AbstractTable::AbstractTable(double *arr, int m, int n)
        : AbstractTable(m, n, arr ? filler() : [arr, n](int i, int j) { return arr[i * n + j]; })
    {}

    AbstractTable::~AbstractTable(void)
    {
        freem();
    }

    AbstractTable& AbstractTable::T(void)
    {
	if (isNull()) return *this;

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

	int swp = nrows;
	nrows = ncols;
	ncols = swp;

        return *this;
    }
    
    unsigned int AbstractTable::get_id(void) const
    {
	return id;
    }

    unsigned int AbstractTable::get_count(void)
    {
	return count;
    }
    
    bool AbstractTable::isNull(void) const
    {
	return !nrows && !ncols;
    }

    bool AbstractTable::isSummable(const AbstractTable& b) const
    {
        return nrows == b.nrows && ncols == b.ncols;
    }

    bool AbstractTable::isMultipliable(const AbstractTable& b) const
    {
        return ncols == b.nrows;
    }
    
    double AbstractTable::min(void) const
    {
	if (isNull())
	    throw id_exception("Ошибка: Контейнер не содержит элементов", id);
	
	double ret = *data;
	for (int i = 1; i < nrows * ncols; i++)
	{
	    if (ret > data[i]) ret = data[i];
	}

	return ret;
    }

    double AbstractTable::max(void) const
    {
	if (isNull())
	    throw id_exception("Ошибка: Контейнер не содержит элементов", id);
	
	double ret = *data;
	for (int i = 1; i < nrows * ncols; i++)
	{
	    if (ret < data[i]) ret = data[i];
	}

	return ret;
    }

    const AbstractTable& AbstractTable::operator =(const AbstractTable& b)
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

            nrows = b.nrows;
            ncols = b.ncols;
	}
	return *this;
    }

    AbstractTable& AbstractTable::operator =(AbstractTable&& mv)
    {
	if (this != &mv)
	{
            freem();

            data = mv.data;
            nrows = mv.nrows;
            ncols = mv.ncols;

            mv.data = nullptr;
	}

	return *this;
    }
    
    AbstractTable& AbstractTable::operator +=(const AbstractTable& b)
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

    AbstractTable& AbstractTable::operator -=(const AbstractTable& b)
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

    AbstractTable& AbstractTable::operator *=(const AbstractTable& b)
    {
	int l = nrows, m = ncols, n = b.ncols;
	if (!isMultipliable(b))
	    throw id_exception("Несоответствие размеров матриц", b.id);

        AbstractTable tmp(l, n, zero);
	
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

    AbstractTable& AbstractTable::operator *=(double k)
    {
	for (int i = 0; i < nrows * ncols; i++)
	{
	    data[i] *= k;	
	}

	return *this;
    }

    std::ostream& operator <<(std::ostream& out, const AbstractTable& tab)
    {	
        int w = out.width();
	if (!w) w = 12; // значение по умолчанию
	    
	int m = tab.nrows;
	int n = tab.ncols;

	if (tab.isNull()) return out << std::setw(0) << "[]" << std::endl;
	for (int i = 0; i < m; i++)
	{
	    out << std::setw(0) << '|';
	    for (int j = 0; j < n; j++)
	    {
		out << std::setw(w) << tab.data[i * n + j] << (j < n - 1 ? ", " : "\0");
	    }
	    out << "|\n";
	}

	return out;
    }

    AbstractTable operator +(const AbstractTable& a, const AbstractTable& b)
    {
        AbstractTable ret(a);
        ret += b;
        return ret;
    }

    AbstractTable operator -(const AbstractTable& a, const AbstractTable& b)
    {
        AbstractTable ret(a);
        ret -= b;
        return ret;
    }

    AbstractTable operator *(const AbstractTable& a, const AbstractTable& b)
    {
        AbstractTable ret(a);
        ret *= b;
        return ret;
    }

    AbstractTable operator *(const AbstractTable& a, double b)
    {
        AbstractTable ret(a);
        ret *= b;
        return ret;
    }

    AbstractTable operator *(double a, const AbstractTable& b)
    {
        AbstractTable ret(b);
        ret *= a;
        return ret;
    }
}
