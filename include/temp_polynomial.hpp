#ifndef OOP_LAB5C_POLYNOMIAL
#define OOP_LAB5C_POLYNOMIAL

#include "idexception.hpp"
#include <vector>
#include <iostream>

namespace oop_labs
{
    template <class T>
    T zero(int);
    
    template <class T>
    class t_polynomial
    {
    private:
	std::vector<T> data;
	unsigned long long id;
	static unsigned long long count;
    public:
        explicit t_polynomial(T a0 = T());
	t_polynomial(int size, T (*fun)(int));
	
	t_polynomial(std::initializer_list< std::pair<T, int> >);
	t_polynomial(const t_polynomial&);
	t_polynomial(t_polynomial&&);
	
	~t_polynomial(void);

	unsigned long long get_id(void) const;
	static unsigned long long get_count(void);

	template <class U>
        friend std::ostream& operator <<(std::ostream&, const t_polynomial<U>&);
	
	bool isNull(void) const;
	
        T operator [](int idx) const; // достает коэффициент при idx-ном члене
        T& operator [](int idx);
	
	t_polynomial& operator = (const t_polynomial&);
	t_polynomial& operator = (t_polynomial&&);
	t_polynomial& operator = (const T&);
	
	t_polynomial& operator += (const t_polynomial&);
	t_polynomial& operator -= (const t_polynomial&);
	t_polynomial& operator *= (const t_polynomial&);
	
	t_polynomial& operator /=(const t_polynomial&);
	t_polynomial& operator %=(const t_polynomial&);

	template <class U>
	friend t_polynomial<U> operator +(const t_polynomial<U>&, const t_polynomial<U>&);

	template <class U>
	friend t_polynomial<U> operator -(const t_polynomial<U>&, const t_polynomial<U>&);

	template <class U>
	friend t_polynomial<U> operator *(const t_polynomial<U>&, const t_polynomial<U>&);

	template <class U>
	friend std::pair< t_polynomial<U>, t_polynomial<U> > modf(const t_polynomial<U>&, const t_polynomial<U>&);

	template <class U>
	friend t_polynomial<U> operator %(const t_polynomial<U>&, const t_polynomial<U>&);

	template <class U>
	friend t_polynomial<U> operator /(const t_polynomial<U>&, const t_polynomial<U>&);
        
        T operator ()(const T&) const;
	t_polynomial& norm(void);
    };
}

#include "temp_polynomial.cpp"

#endif
