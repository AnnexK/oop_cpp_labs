#ifndef OOP_LAB3_INHERITANCE_MATRIX
#define OOP_LAB3_INHERITANCE_MATRIX

#include "math_abstract.hpp"
#include "idexception.hpp"
#include <iostream>

namespace oop_labs
{
    class Matrix : public AbstractTable
    {
    private:
        class Row
        {
        private:
            double *data;
            int length;
            unsigned int id;
        public:
            Row(const Matrix&, int);
            ~Row(void);

            double& operator [](int);
            double operator [](int) const;
        };
    public:
        using AbstractTable::T;
        
        explicit Matrix(int m = 0, filler fun = filler());
        Matrix(int, int, filler fun = filler());
        
        Matrix(const Matrix&);
        Matrix(Matrix&&);
        
        Matrix(const AbstractTable&);
        Matrix(AbstractTable&&);

        Matrix(double *, int, int);
        
        virtual ~Matrix(void);

        Row operator [](int);
        const Row operator [](int) const;

        virtual const Matrix& operator =(const Matrix&);
        virtual Matrix& operator =(Matrix&&);

        virtual const Matrix& operator =(const AbstractTable&) override;
        virtual Matrix& operator =(AbstractTable&&) override;        
    };

    Matrix transpose(const Matrix&);
}
#endif
