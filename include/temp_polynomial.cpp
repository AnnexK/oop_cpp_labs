#include <limits>

#define ABS(X) ((X) > T() ? X : X * T(-1)) // перегрузка std::abs не пройдет

namespace oop_labs
{
    template <class T>
    T zero(int idx)
    {
	return T(0);
    }

    template <class T>
    unsigned long long t_polynomial<T>::count = 0;

    template <class T>
    t_polynomial<T>::t_polynomial(int size, T (*fun)(int))
    {
	if (size <= 0)
	    throw id_exception("Ошибка: размер не может быть меньше 0", count);
        
	for (int i = 0; i < size; i++)
	{
	    data.push_back(fun(i));
	}
	id = count++;	
    }
    
    template <class T>
    t_polynomial<T>::t_polynomial(T a0)
    {
	data.push_back(a0);
    }

    template <class T>
    t_polynomial<T>::t_polynomial(std::initializer_list< std::pair<T, int> > elems)
    {
	for (std::pair<T, int> e : elems)	   
	{
	    if (e.second >= data.size())
		data.resize(e.second + 1);

	    data[e.second] = e.first;
	}

	id = count++;
    }

    template <class T>
    t_polynomial<T>::t_polynomial(const t_polynomial<T>& cp)
    {
	data = cp.data;
	id = count++;
    }

    template <class T>
    t_polynomial<T>::t_polynomial(t_polynomial<T>&& mv)
    {
	data = std::move(mv.data);
	id = count++;
    }

    template <class T>
    t_polynomial<T>::~t_polynomial(void) {}

    template <class T>
    unsigned long long t_polynomial<T>::get_id(void) const
    {
	return id;
    }

    template <class T>
    unsigned long long t_polynomial<T>::get_count(void)
    {
	return count;
    }

    template <class T>
    std::ostream& operator <<(std::ostream& out, const t_polynomial<T>& op)
    {
        int vsize = op.data.size();
        T eps = std::numeric_limits<T>::epsilon();
        
        out << '[';
    	for (int i = vsize - 1; i >= 0; --i)
    	{
	    if (ABS(op.data[i]) > eps || !i)
            {
		out << op.data[i];
                if (i) out << "x^" << i << " + ";
            }
    	}

    	return out << ']';
    }

    template <class T>
    T t_polynomial<T>::operator ()(const T& x) const
    {
        T res(0);
	int vsize = data.size();
        T power(1);
	
	for (int i = 0; i < vsize; i++)
	{
	    res += data[i] * power;
	    power *= x;
	}

	return res;
    }

    template <class T>
    t_polynomial<T>& t_polynomial<T>::norm(void)
    {
        int vsize = data.size();
        T eps = std::numeric_limits<T>::epsilon();
        
	while (vsize > 1 && ABS(data[vsize - 1]) <= eps) vsize--;

	data.resize(vsize);
    }

    template <class T>
    bool t_polynomial<T>::isNull(void) const
    {
	return (data.size() == 1 && ABS(data[0]) < std::numeric_limits<T>::epsilon());
    }

    template <class T>
    T t_polynomial<T>::operator [](int idx) const
    {
        if (idx >= data.size())
            return T();
        
	return T(data[idx]);
    }

    template <class T>
    T& t_polynomial<T>::operator [](int idx)
    {
	if (idx >= data.size())
        {
            data.resize(idx + 1);            
        }
	return data[idx];
    }

    template <class T>
    t_polynomial<T>& t_polynomial<T>::operator =(const T& x)
    {
	data.resize(1);
	data[0] = x;

	return *this;
    }

    template <class T>
    t_polynomial<T>& t_polynomial<T>::operator =(const t_polynomial<T>& op)
    {
	if (this != &op)
	    data = op.data;
	return *this;
    }

    template <class T>
    t_polynomial<T>& t_polynomial<T>::operator =(t_polynomial<T>&& mv)
    {
        if (this != &mv)
            data = std::move(mv.data);
        return *this;
    }

    template <class T>
    t_polynomial<T>& t_polynomial<T>::operator += (const t_polynomial<T>& op)
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

    template <class T>
    t_polynomial<T>& t_polynomial<T>::operator -= (const t_polynomial<T>& op)
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

    template <class T>
    t_polynomial<T>& t_polynomial<T>::operator *=(const t_polynomial<T>& op)
    {
	int op2size = op.data.size();
	int op1size = data.size();
	int newsize = op1size + op2size - 1;
	data.resize(newsize);

        T in;
	
	for (int total = newsize - 1; total >= 0; total--) // total - текущая заполняемая степень
	{
	    in = T();
	    
	    bool isInFirst = total < op1size;
	    int op1cur = (isInFirst ? total : op1size - 1);
	    int op2cur = (isInFirst ? 0 : total - (op1size - 1));

	    while (op2cur < op2size && op1cur >= 0)
	    {
		in += data[op1cur] * op.data[op2cur];
		op1cur--;
		op2cur++;
	    }

	    data[total] = in;
	    
	}
	return *this;
    }

    template <class T>
    t_polynomial<T>& t_polynomial<T>::operator /=(const t_polynomial<T>& op)
    {
	*this = std::move(modf(*this, op).first);
	return *this;
    }

    template <class T>
    t_polynomial<T>& t_polynomial<T>::operator %=(const t_polynomial<T>& op)
    {
	*this = std::move(modf(*this, op).second);
	return *this;
    }

    template <class T>
    t_polynomial<T> operator + (const t_polynomial<T>& op1, const t_polynomial<T>& op2)
    {
	t_polynomial<T> ret = op1;

	ret += op2;

	return ret;
    }

    template <class T>
    t_polynomial<T> operator - (const t_polynomial<T>& op1, const t_polynomial<T>& op2)
    {
	t_polynomial<T> ret = op1;

	ret -= op2;

	return ret;
    }

    template <class T>
    t_polynomial<T> operator * (const t_polynomial<T>& op1, const t_polynomial<T>& op2)
    {
	t_polynomial<T> ret = op1;

	ret *= op2;

	return ret;
    }

    template <class T>
    std::pair< t_polynomial<T>, t_polynomial<T> > modf(const t_polynomial<T>& op1, const t_polynomial<T>& op2)
    {
	if (op2.isNull())
	    throw id_exception("Ошибка при делении полиномов: Делитель равен 0", op2.id);

	int op1size = op1.data.size();
	int op2size = op2.data.size();

	int diff = op1size - op2size;
	
	t_polynomial<T> rem = op1;
	try
	{
	    t_polynomial<T> res(diff + 1);

	    for (int rsize = diff; rsize >= 0; --rsize)
	    {
		res[rsize] = rem.data[rsize + op2size - 1] / op2.data[op2size - 1];
		for (int subidx = rsize + op2size - 1; subidx >= rsize; --subidx)
		{
		    rem[subidx] -= res[rsize] * op2[subidx - rsize];
		}
	    }

	    rem.norm();
	    res.norm();
	    return std::make_pair(res, rem);
	}
	catch (const id_exception& ex) // левый полином "младше" правого
	{
	    return std::make_pair(t_polynomial<T>(), rem);
	}
    }

    template <class T>
    t_polynomial<T> operator /(const t_polynomial<T>& op1, const t_polynomial<T>& op2)
    {
	return modf(op1, op2).first;
    }

    template <class T>
    t_polynomial<T> operator %(const t_polynomial<T>& op1, const t_polynomial<T>& op2)
    {
	return modf(op1, op2).second;
    }
}
