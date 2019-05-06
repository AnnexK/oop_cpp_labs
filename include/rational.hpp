#ifndef OOP_LAB4_RATIONAL_HEADER
#define OOP_LAB4_RATIONAL_HEADER

#include "idexception.hpp"
#include <utility>
#include <iostream>
#include <cmath>

namespace oop_labs
{
    class my_rational
    {
    private:
	int numer;
	int denom;
	
	static int gcd(int, int);
	static int lcm(int, int);	
	
        unsigned long long id;
	static unsigned long long count;
    public:
	my_rational(int n = 0, int d = 1);
	my_rational(const my_rational&);
        my_rational(my_rational&&);
        
	~my_rational(void) {}

	unsigned long long get_id(void) const;
	static unsigned long long get_count(void);

        int get_numer(void) const;
        int get_denom(void) const;
        
	my_rational& norm(void); // приведение к каноническому виду
	std::pair<int, my_rational> decompose(void) const;

	my_rational& operator +=(const my_rational&);
	my_rational& operator -=(const my_rational&);
	my_rational& operator *=(const my_rational&);
	my_rational& operator /=(const my_rational&);
	
	const my_rational& operator =(const my_rational&);
        my_rational& operator =(my_rational&&);
        
	my_rational& operator =(int);
	
	friend my_rational operator +(const my_rational&, const my_rational&);
	friend my_rational operator -(const my_rational&, const my_rational&);
	friend my_rational operator *(const my_rational&, const my_rational&);
	friend my_rational operator /(const my_rational&, const my_rational&);

	friend std::ostream& operator <<(std::ostream&, const my_rational&);

	friend bool operator ==(const my_rational&, const my_rational&);
	friend bool operator !=(const my_rational&, const my_rational&);
	friend bool operator <(const my_rational&, const my_rational&);
	friend bool operator <=(const my_rational&, const my_rational&);
	friend bool operator >(const my_rational&, const my_rational&);
	friend bool operator >=(const my_rational&, const my_rational&);
	
        operator double (void) const;
	operator int (void) const;
    };
	
}

#endif
