#include "polynomial.hpp"
#include <algorithm>
#include <cmath>
#include <limits>

namespace oop_labs
{
    unsigned long long my_polynomial::count = 0;

    double poly_kbinput(int idx)
    {
	double ret;
	std::cout << "Введите a" << idx << ": ";
	std::cin >> ret;
	return ret;
    }
    
    my_polynomial::my_polynomial(int degree, double (*fun)(int))
    {        
	if (degree < 0)
	    throw id_exception("Ошибка: максимальная степень не может быть меньше 0", count);
        
	for (int i = 0; i <= degree; i++)
	{
	    data.push_back(fun != nullptr ? fun(i) : 0.0);
	}
	id = count++;	
    }

    my_polynomial::my_polynomial(double a0)
    {
	data.push_back(a0);
        id = count++;
    }
    
    my_polynomial::my_polynomial(const std::initializer_list< std::pair<double, unsigned int> >& elems)
    {
	for (auto e : elems)	   
	{
	    if (e.second >= data.size())
		data.resize(e.second + 1);

	    data[e.second] = e.first;
	}

	id = count++;
    }

    my_polynomial::my_polynomial(const my_polynomial& cp)
    {
	data = cp.data;
	id = count++;
    }

    my_polynomial::my_polynomial(my_polynomial&& mv)
    {
	data = std::move(mv.data);
	id = count++;
    }
    
    my_polynomial::~my_polynomial(void) {}

    unsigned long long my_polynomial::get_id(void) const
    {
	return id;
    }

    unsigned long long my_polynomial::get_count(void)
    {
	return count;
    }
    
    std::ostream& operator <<(std::ostream& out, const my_polynomial& op)
    {
	double eps = std::numeric_limits<double>::epsilon();
	
        int vsize = op.data.size();

        out << '[';
    	for (int i = vsize - 1; i >= 0; --i)
    	{
	    if (std::abs(op.data[i]) > eps || !i)
            {
		out << op.data[i];
                if (i) out << "x^" << i << " + ";
            }
    	}

    	return out << ']';
    }
   
    double my_polynomial::operator ()(double x) const
    {
	double res = 0.0;
	int vsize = data.size();
	double power = 1.0;
	
	for (int i = 0; i < vsize; i++)
	{
	    res += data[i] * power;
	    power *= x;
	}

	return res;
    }

    my_polynomial& my_polynomial::norm(void)
    {
	double eps = std::numeric_limits<double>::epsilon();
        int vsize = data.size();

	while (vsize > 1 && std::abs(data[vsize - 1]) < eps) vsize--;

	data.resize(vsize);
        return *this;
    }

    bool my_polynomial::isNull(void) const
    {
	return (data.size() == 1 && std::abs(data[0]) < std::numeric_limits<double>::epsilon());
    }

    int my_polynomial::get_degree(void) const
    {
        return data.size() - 1;
    }
    
    double my_polynomial::operator [](unsigned int idx) const
    {
        if (idx >= data.size())
            return 0.0;
        
	return data[idx];
    }

    double& my_polynomial::operator [](unsigned int idx)
    {
	if (idx >= data.size())
        {
            data.resize(idx + 1);            
        }
	return data[idx];
    }

    my_polynomial& my_polynomial::operator =(double x)
    {
	data.resize(1);
	data[0] = x;

	return *this;
    }
    
    my_polynomial& my_polynomial::operator =(const my_polynomial& op)
    {
	if (this != &op)
	    data = op.data;
	return *this;
    }

    my_polynomial& my_polynomial::operator =(my_polynomial&& mv)
    {
        if (this != &mv)
            data = std::move(mv.data);
        return *this;
    }
    
    my_polynomial& my_polynomial::operator += (const my_polynomial& op)
    {
        unsigned int opsize = op.data.size();
	
        if (data.size() < opsize)
	    data.resize(opsize);
	
	for (unsigned int i = 0; i < opsize; ++i)
	{
	    data[i] += op.data[i];
	}

	norm();
	return *this;
    }

    my_polynomial& my_polynomial::operator -= (const my_polynomial& op)
    {
        unsigned int opsize = op.data.size();
	
        if (data.size() < opsize)
	    data.resize(opsize);
	
	for (unsigned int i = 0; i < opsize; ++i)
	{
	    data[i] -= op.data[i];
	}

	norm();
	return *this;
    }

    my_polynomial& my_polynomial::operator *=(const my_polynomial& op)
    {
        int op2size = op.data.size();
        int op1size = data.size();
	int newsize = op1size + op2size - 1;
	data.resize(newsize);

	double in;
	
	for (int total = newsize - 1; total >= 0; total--) // total - текущая заполняемая степень
	{
	    in = 0.0;
	    
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

    my_polynomial& my_polynomial::operator /=(const my_polynomial& op)
    {
	*this = std::move(modf(*this, op).first);
	return *this;
    }
    
    my_polynomial& my_polynomial::operator %=(const my_polynomial& op)
    {
	*this = std::move(modf(*this, op).second);
	return *this;
    }

    my_polynomial operator + (const my_polynomial& op1, const my_polynomial& op2)
    {
	my_polynomial ret = op1;

	ret += op2;

	return ret;
    }

    my_polynomial operator - (const my_polynomial& op1, const my_polynomial& op2)
    {
	my_polynomial ret = op1;

	ret -= op2;

	return ret;
    }

    my_polynomial operator * (const my_polynomial& op1, const my_polynomial& op2)
    {
	my_polynomial ret = op1;

	ret *= op2;

	return ret;
    }

    std::pair<my_polynomial, my_polynomial> modf(const my_polynomial& op1, const my_polynomial& op2)
    {
        unsigned int op1size = op1.data.size();
	unsigned int op2size = op2.data.size();

        if (std::abs(op2.data.back()) < std::numeric_limits<double>::epsilon())
	    throw id_exception("Ошибка при делении полиномов: Делитель равен 0", op2.id);

        int diff = op1size - op2size;
	
	my_polynomial rem = op1;
        if (diff >= 0)
	{
	    my_polynomial res(diff + 1);

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
        else // левый полином "младше" правого
	{
	    return std::make_pair(my_polynomial(), rem);
	}
    }

    my_polynomial operator /(const my_polynomial& op1, const my_polynomial& op2)
    {
	return modf(op1, op2).first;
    }
    
    my_polynomial operator %(const my_polynomial& op1, const my_polynomial& op2)
    {
	return modf(op1, op2).second;
    }    
}
