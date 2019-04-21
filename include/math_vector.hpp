#ifndef OOP_LAB3_INHERITANCE_VECTOR
#define OOP_LAB3_INHERITANCE_VECTOR

#include "math_abstract.hpp"
#include <iostream>

namespace oop_labs
{
    typedef std::function<double(int)> vfiller;
    
    class Vector : public AbstractTable
    {
    public:
        explicit Vector(int m = 0, vfiller fun = vfiller());

        Vector(const Vector&);
        Vector(Vector&&);
        
        Vector(const AbstractTable&);
        Vector(AbstractTable &&);

        Vector(double *, int);
        
        virtual ~Vector(void);

        virtual const Vector& operator=(const Vector&);
        virtual Vector& operator=(Vector&&);

        virtual const Vector& operator=(const AbstractTable&) override;
        virtual Vector& operator=(AbstractTable&&) override;
        
        int get_length(void) const;

        double& operator [](int);
        double operator [](int) const;

        virtual bool isSummable(const AbstractTable&) const override;
        virtual bool isMultipliable(const AbstractTable&) const override;
        
        virtual Vector& operator +=(const AbstractTable&) override;
        virtual Vector& operator -=(const AbstractTable&) override;
        virtual Vector& operator *=(const AbstractTable&) override;
    };
    
}
#endif
