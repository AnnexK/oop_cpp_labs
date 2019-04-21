#include "temp_polynomial.hpp"
#include <algorithm>

namespace oop_labs
{
    unsigned long long my_polynomial::count = 0;
    
    template <class C_Type>
    my_polynomial<C_Type>::my_polynomial(int size)
    {
	if (size <= 0)
	    throw id_exception("Ошибка: размер не может быть меньше 0", count);

	data.resize(size);
	
	for (int i = 0; i < size; i++)
	{
	    data.push_back(0.0);
	}
	id = count++;	
    }
    
    template<class C_Type>
    my_polynomial<C_Type>::my_polynomial(C_Type a0)
    {
	data.push_back(a0);
    }

    template<class C_Type>
    my_polynomial<C_Type>::my_polynomial(std::initializer_list< std::pair<C_Type, int> > elems)
    {
	for (std::pair<C_Type, int> e : elems)	   
	{
	    if (e.second >= data.size())
		data.resize(e.second + 1);

	    data[e.second] = e.first;
	}

	id = count++;
    }

    template<class C_Type>
    my_polynomial::my_polynomial(const my_polynomial<C_Type>& cp)
    {
	data = cp.data;
	id = count++;
    }

    template<class C_Type>
    my_polynomial<C_Type>::~my_polynomial(void) {}

    template<class C_Type>
    unsigned long long my_polynomial<C_Type>::get_id(void) const
    {
	return id;
    }

    template<class C_Type>
    std::ostream& operator <<(std::ostream& out, const my_polynomial<C_Type> op)
    {
	double eps = std::numeric_limits<C_Type>::epsilon();
	
        int vsize = op.data.size();

	out << '[';
	
    	for (int i = 0; i < vsize; ++i)
    	{
	    if (std::abs(op.data[i]) > eps)
		out << '(' << op.data[i] << ", " << i << ')';
    	}

    	return out << ']' << std::endl;
    }

    template<class C_Type>
    C_Type my_polynomial<C_Type>::operator ()(const C_Type& x) const
    {
	C_Type res, mult(1); // C_Type(void)
	int vsize = data.size();
	
	for (int i = 0; i < vsize; i++)
	{
	    res += data[i] * mult;
            mult *= res;
	}

	return res;
    }

    template<class C_Type>
    my_polynomial& my_polynomial<C_Type>::norm(void)
    {
	double eps = std::numeric_limits<C_Type>::epsilon();
        int vsize = data.size();

	while (vsize > 1 && std::abs(data[vsize - 1]) <= eps) vsize--;

	data.resize(vsize);
    }

    template<class C_Type>
    bool my_polynomial<C_Type>::isNull(void) const
    {
	return (data.size() == 1 && std::abs(data[0]) <= std::numeric_limits<C_Type>::epsilon());
    }

    template<class C_Type>
    const C_Type& my_polynomial<C_Type>::operator [](int idx) const
    {
	if (idx >= data.size())
	    return C_Type(); // 0
	return data[idx];
    }

    template<class C_Type>
    C_Type& my_polynomial<C_Type>::operator [](int idx)
    {
	if (idx >= data.size())
	    data.resize(idx+1);
	return data[idx];
    }

    template<class C_Type>
    my_polynomial<C_Type>& my_polynomial<C_Type>::operator =(const my_polynomial<C_Type>& op)
    {
        if (this != &op)
            data = op.data;
        return *this;
    }

    template<class C_Type>
    my_polynomial<C_Type>& my_polynomial<C_Type>::operator =(my_polynomial<C_Type>&& mv)
    {
        if (this != &mv)
            data = std::move(mv.data);
        return *this;
    }
    
    template<class C_Type>
    my_polynomial<C_Type>& my_polynomial<C_Type>::operator += (const my_polynomial<C_Type>& op)
    {
	int opsize = op.data.size();
	
        if (data.size() < opsize)
	    data.resize(opsize);
	
	for (int i = 0; i < opsize; ++i)
	{
	    data[i] += op.data[i];
	}

	norm();
	return *this;
    }

    template<class C_Type>
    my_polynomial<C_Type>& my_polynomial<C_Type>::operator -= (const my_polynomial<C_Type>& op)
    {
	int opsize = op.data.size();
	
        if (data.size() < opsize)
	    data.resize(opsize);
	
	for (int i = 0; i < opsize; ++i)
	{
	    data[i] -= op.data[i];
	}

	norm();
	return *this;
    }

    template<class C_Type>
    my_polynomial<C_Type>& my_polynomial<C_Type>::operator *=(const my_polynomial<C_Type>& op)
    {
	int opsize = op.data.size();
	int tsize = data.size();
	data.resize(opsize + tsize - 1);

	C_Type in;
	
	for (int i = opsize + tsize - 2; i >= 0; --i)
	{
	    in = C_Type(); // 0
	    for (int j = 0; j < opsize; j++)
	    {
	        in += data[i - j] * op.data[j];
	    }
	    data[i] = in;
	}

	return *this;
    }

    template<class C_Type>
    my_polynomial<C_Type>& my_polynomial<C_Type>::operator /=(const my_polynomial<C_Type>& op)
    {
	*this = std::move(modf(*this, op).first);
	return *this;
    }

    template<class C_Type>
    my_polynomial<C_Type>& my_polynomial<C_Type>::operator %=(const my_polynomial<C_Type>& op)
    {
	*this = std::move(modf(*this, op).second);
	return *this;
    }

    template<class C_Type>
    my_polynomial<C_Type> operator + (const my_polynomial<C_Type>& op1, const my_polynomial<C_Type>& op2)
    {
        my_polynomial<C_Type> ret = op1;

	ret += op2;

	return ret;
    }
    
    template<class C_Type>
    my_polynomial<C_Type> operator - (const my_polynomial<C_Type>& op1, const my_polynomial<C_Type>& op2)
    {
        my_polynomial<C_Type> ret = op1;

	ret -= op2;

	return ret;
    }
    
    template<class C_Type>
    my_polynomial<C_Type> operator * (const my_polynomial<C_Type>& op1, const my_polynomial<C_Type>& op2)
    {
        my_polynomial<C_Type> ret = op1;

	ret *= op2;

	return ret;
    }

    template<class C_Type>
    std::pair< my_polynomial<C_Type>, my_polynomial<C_Type> > modf(const my_polynomial<C_Type>& op1, const my_polynomial<C_Type>& op2)
    {
	if (op2.isNull())
	    throw id_exception("Ошибка при делении полиномов: Делитель равен 0", op2.id);

	int op1size = op1.data.size();
	int op2size = op2.data.size();

	int diff = op1size - op2size;
	
	my_polynomial<C_Type> rem = op1;
	try
	{
	    my_polynomial<C_Type> res(diff + 1);

	    for (int rsize = diff; rsize >= 0; --rsize)
	    {
		res[rsize] = rem.data[rsize + op2size - 1] / op2.data[op2size - 1];
		for (int subidx = rsize + op2size - 1; subidx >= rsize; --subidx)
		{
		    rem[subidx] -= res[rsize] * op2[subidx - rsize];
		}
	    }

	    return std::make_pair(res, rem);
	}
	catch (const id_exception& ex) // левый полином "младше" правого
	{
	    return std::make_pair(my_polynomial<C_Type>(), rem);
	}
    }

    template<class C_Type>
    my_polynomial<C_Type> operator /(const my_polynomial<C_Type>& op1, const my_polynomial<C_Type>& op2)
    {
	return modf(op1, op2).first;
    }

    template<class C_Type>
    my_polynomial<C_Type> operator %(const my_polynomial<C_Type>& op1, const my_polynomial<C_Type>& op2)
    {
	return modf(op1, op2).second;
    }    
}
