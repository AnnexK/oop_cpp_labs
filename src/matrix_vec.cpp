#include "matrix_vec.hpp"

namespace oop_labs
{
    int my_matvec::get_len(void) const
    {
	return ncols;
    }

    double my_matvec::operator [](int idx) const
    {
	if (idx < 0 || idx > ncols)
	    throw id_exception("Ошибка: индекс выходит за границы", id);

	return data[idx];
    }

    double& my_matvec::operator [](int idx)
    {
	if (idx < 0 || idx > ncols)
	    throw id_exception("Ошибка: индекс выходит за границы", id);

	return data[idx];
    }

    my_matvec& my_matvec::operator *=(const my_matrix& op2)
    {
	if (!isMultipliable(op2))
	    throw id_exception("Несоответствие размеров матриц", op2.id);
    
	int retlen = op2.get_ncols();
	double *newdata;
	
	try
	{
	    newdata = new double[retlen];
	}
	catch (const std::bad_alloc&)
	{
	    throw id_exception("Ошибка при выделении памяти", id);
	}
	
	for (int i = 0; i < retlen; i++)
	{
	    newdata[i] = 0.0;
	    for (int j = 0; j < ncols; j++)
	    {
		newdata[i] += data[j] * op2[j][i];
	    }
	}

	delete[] data;
	data = newdata;

	return *this;
    }

    double operator * (const my_matvec& op1, const my_matvec& op2)
    {
	if (!op1.isMultipliable(op2))
	    throw id_exception("Несоответствие размеров матриц", op2.id);

	double ret = 0.0;
	for (int i = 0; i < ncols; i++)
	{
	    ret += op1[i] * op2[i];
	}

	return ret;
    }

    my_matvec operator * (const my_matrix& op1, const my_matvec& op2)
    {
	
    }
}
