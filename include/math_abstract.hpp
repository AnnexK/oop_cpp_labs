#ifndef OOP_LAB3_INHERITANCE_TABLE
#define OOP_LAB3_INHERITANCE_TABLE

#include <iostream>
#include <functional>

namespace oop_labs
{
    typedef std::function<double(int, int)> filler;
    
    class AbstractTable
    {
    private:
        void allocm(int, int);
        void freem(void);
        
    protected:
        double *data;
        int nrows;
        int ncols;

        unsigned int id;
        static unsigned int count;

        AbstractTable(int m = 0, filler fun = filler());
        AbstractTable(int, int, filler fun = filler());
        AbstractTable(const AbstractTable&);
        AbstractTable(AbstractTable&&);
        AbstractTable(double *, int, int);
        AbstractTable(double **, int, int);
        
        AbstractTable& T(void);

    public:
        virtual ~AbstractTable(void);

        virtual const AbstractTable& operator =(const AbstractTable&);
        virtual AbstractTable& operator =(AbstractTable&&);
        
        unsigned int get_id(void) const;
        static unsigned int get_count(void);

        bool isNull(void) const;
        virtual bool isSummable(const AbstractTable&) const;
        virtual bool isMultipliable(const AbstractTable&) const;
        
        double max(void) const;
        double min(void) const;

        virtual AbstractTable& operator +=(const AbstractTable&);
        virtual AbstractTable& operator -=(const AbstractTable&);
        virtual AbstractTable& operator *=(const AbstractTable&);
        virtual AbstractTable& operator *=(double);

        friend std::ostream& operator <<(std::ostream&, const AbstractTable&);

        friend AbstractTable operator +(const AbstractTable&, const AbstractTable&);
        friend AbstractTable operator -(const AbstractTable&, const AbstractTable&);
        friend AbstractTable operator *(const AbstractTable&, const AbstractTable&);
        friend AbstractTable operator *(const AbstractTable&, double);
        friend AbstractTable operator *(double, const AbstractTable&);
    };
}
#endif
