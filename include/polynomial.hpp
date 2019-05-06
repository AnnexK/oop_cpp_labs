#ifndef OOP_LAB4_POLYNOMIAL_HEADER
#define OOP_LAB4_POLYNOMIAL_HEADER

#include "idexception.hpp"
#include <iostream>
#include <vector>
#include <utility>

namespace oop_labs
{
    double poly_kbinput(int idx);
    class my_polynomial
    {
    private:
	std::vector<double> data;
	unsigned long long id;
	static unsigned long long count;
    public:
        my_polynomial(double a0 = 0.0);
        
        explicit my_polynomial(int degree, double(*fun)(int)=nullptr);
	
	my_polynomial(const std::initializer_list< std::pair<double, unsigned int> >&);
	my_polynomial(const my_polynomial&);
	my_polynomial(my_polynomial&&);
	
	~my_polynomial(void);

	unsigned long long get_id(void) const;
	static unsigned long long get_count(void);
	
        friend std::ostream& operator <<(std::ostream&, const my_polynomial&);
	bool isNull(void) const; // полином равен 0

        int get_degree(void) const;
        
	double operator [](unsigned int idx) const; // достает коэффициент при idx-ном члене
        double& operator [](unsigned int idx);
	
	my_polynomial& operator = (const my_polynomial&);
	my_polynomial& operator = (my_polynomial&&);
	my_polynomial& operator = (double);
	
	my_polynomial& operator += (const my_polynomial&);
	my_polynomial& operator -= (const my_polynomial&);
	my_polynomial& operator *= (const my_polynomial&);
	
	my_polynomial& operator /=(const my_polynomial&);
	my_polynomial& operator %=(const my_polynomial&);
	
	friend my_polynomial operator +(const my_polynomial&, const my_polynomial&);
	friend my_polynomial operator -(const my_polynomial&, const my_polynomial&);
	friend my_polynomial operator *(const my_polynomial&, const my_polynomial&);
	
	friend std::pair<my_polynomial, my_polynomial> modf(const my_polynomial&, const my_polynomial&);
	friend my_polynomial operator %(const my_polynomial&, const my_polynomial&);
	friend my_polynomial operator /(const my_polynomial&, const my_polynomial&);
        
	double operator ()(double) const;
	my_polynomial& norm(void);
    };
}

#endif
