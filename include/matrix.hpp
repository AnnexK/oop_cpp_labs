#ifndef OOP_LAB2_MATRIX_HEADER
#define OOP_LAB2_MATRIX_HEADER

#include <iostream>
#include "idexception.hpp"

namespace oop_labs
{
    // Алгоритмы заполнения матрицы
    double Emat(int i, int j);
    double kbinput(int i, int j);
    double zero(int i, int j);
    
    /* Класс матрицы */
    class my_matrix
    {	
    private:	
	/* Прокси-класс для контроля доступа к элементам строк матрицы */

	class mrow
	{
	private:
	    double *data;
	    int length;
	    unsigned int id;	    
	public:
	    mrow(const my_matrix&, int);
	    ~mrow(void);
	    
	    double& operator [] (int); // lvalue
	    double operator [] (int) const; // not lvalue
	};
	
	double  *data; 
	int      nrows;
	int      ncols;

	unsigned int id;
	static unsigned int count;

	void allocm(int, int);
	void freem(void);
	
    public:        
	explicit my_matrix(int m = 0, double (*fun)(int, int) = nullptr);
	my_matrix(int, int, double (*fun)(int, int) = nullptr);
	my_matrix(const my_matrix&);
	my_matrix(my_matrix&&);

	~my_matrix(void);
	
	my_matrix& T(void);
	
	unsigned int get_id(void) const;
	static unsigned int get_count(void);
	int get_nrows(void) const;
	int get_ncols(void) const;

	bool isNull(void) const;
        bool isMultipliable(const my_matrix&) const;	
	bool isSummable(const my_matrix&) const;       

	double max(void) const;
	double min(void) const;

        mrow operator [](int);
        const mrow operator [](int) const;

        const my_matrix& operator =(const my_matrix&);
	my_matrix& operator =(my_matrix&&);
	
	my_matrix& operator +=(const my_matrix&);
	my_matrix& operator -=(const my_matrix&);
        my_matrix& operator *=(const my_matrix&);	
	my_matrix& operator *=(double);

	friend std::ostream& operator <<(std::ostream&, const my_matrix&);
    };

    my_matrix transpose(const my_matrix&);
    
    my_matrix operator +(const my_matrix&, const my_matrix&);
    my_matrix operator -(const my_matrix&, const my_matrix&);
    my_matrix operator *(const my_matrix&, const my_matrix&);
    my_matrix operator *(const my_matrix&, double);
    my_matrix operator *(double, const my_matrix&);
}
#endif
