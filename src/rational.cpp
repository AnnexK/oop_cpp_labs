#include "rational.hpp"

namespace oop_labs
{
    unsigned long long my_rational::count = 0;
    
    my_rational::my_rational(int n, int d)
    {
	id = count;
	if (!d)
	    throw id_exception("Ошибка: знаменатель не может быть равен 0", id);
	numer = n;
	denom = d;
        norm();
	count++;
    }

    my_rational::my_rational(const my_rational& cp)
    {
        id = count++;
	numer = cp.numer;
	denom = cp.denom;
    }

    my_rational::my_rational(my_rational&& mv)
    {
        id = count++;
        numer = mv.numer;
        denom = mv.denom;
    }
    
    int my_rational::gcd(int a, int b)
    {
        return !b ? a : gcd(b, a % b);
    }

    int my_rational::lcm(int a, int b)
    {
	return a / gcd(a, b) * b;
    }

    my_rational& my_rational::norm(void)
    {
	int cd = gcd(numer, denom);
	numer /= cd;
	denom /= cd;

        if (denom < 0)
	{
	    numer = -numer;
	    denom = -denom;
	}
	return *this;
    }

    int my_rational::get_numer(void) const
    {
        return numer;
    }

    int my_rational::get_denom(void) const
    {
        return denom;
    }
    
    unsigned long long my_rational::get_id(void) const
    {
	return id;
    }

    unsigned long long my_rational::get_count(void)
    {
	return count;
    }
    
    std::pair<int, my_rational> my_rational::decompose(void) const
    {
	my_rational frac(numer % denom, denom);
	return std::make_pair(numer / denom, frac);
    }

    my_rational& my_rational::operator +=(const my_rational& op)
    {
	numer = numer * op.denom + op.numer * denom;
	denom *= op.denom;

	return this->norm();
    }

    my_rational& my_rational::operator -=(const my_rational& op)
    {
	numer = numer * op.denom - op.numer * denom;
	denom *= op.denom;

	return this->norm();
    }

    my_rational& my_rational::operator *=(const my_rational& op)
    {      
	denom *= op.denom;	
	numer *= op.numer;
	
	return this->norm();
    }

    my_rational& my_rational::operator /=(const my_rational& op)
    {
	if (!(op.numer))
	    throw id_exception("Ошибка при делении: делитель равен нулю", op.get_id());
	
        denom *= op.numer;
	numer *= op.denom;
		
	return this->norm();
    }
    
    const my_rational& my_rational::operator =(const my_rational& op)
    {
	numer = op.numer;
	denom = op.denom;
	return *this;
    }

    my_rational& my_rational::operator =(my_rational&& mv)
    {
        numer = mv.numer;
        denom = mv.denom;
        return *this;
    }
    
    my_rational& my_rational::operator =(int op)
    {
	numer = op;
	denom = 1;
	return *this;
    }
    my_rational operator + (const my_rational& op1, const my_rational& op2)
    {
	my_rational ret = op1;
	ret += op2;
	return ret;
    }

    my_rational operator - (const my_rational& op1, const my_rational& op2)
    {
	my_rational ret = op1;
	ret -= op2;
	return ret;
    }
    
    my_rational operator * (const my_rational& op1, const my_rational& op2)
    {
	my_rational ret = op1;
	ret *= op2;
	return ret;
    }
    
    my_rational operator / (const my_rational& op1, const my_rational& op2)
    {
	my_rational ret = op1;
	
        ret /= op2;
	
	return ret;
    }

    std::ostream& operator <<(std::ostream& out, const my_rational& op)
    {
	return out << op.numer << '/' << op.denom;
    }

    my_rational::operator double(void) const
    {
	return (double) numer / (double) denom;
    }

    my_rational::operator int(void) const
    {
	return numer / denom;
    }

    bool operator == (const my_rational& op1, const my_rational& op2)
    {
	return op1.numer == op2.numer && op1.denom == op2.denom; // инвариант: все дроби несократимые
    }

    bool operator != (const my_rational& op1, const my_rational& op2)
    {
	return !(op1 == op2);
    }

    bool operator < (const my_rational& op1, const my_rational& op2)
    {
        long long int cmp = op1.numer * op2.denom - op2.numer * op1.denom;
	return cmp < 0LL;
    }

    bool operator <= (const my_rational& op1, const my_rational& op2)
    {
	return op1 < op2 || op1 == op2;
    }

    bool operator > (const my_rational& op1, const my_rational& op2)
    {
	return !(op1 <= op2);
    }

    bool operator >= (const my_rational& op1, const my_rational& op2)
    {
	return !(op1 < op2);
    }
}
