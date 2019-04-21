#ifndef OOP_LAB_ID_EXCEPTION_HEADER
#define OOP_LAB_ID_EXCEPTION_HEADER

#include <exception>
#include <string>

namespace oop_labs
{
    class id_exception : public std::exception
    {
    private:
	unsigned int id;
	char *msg;
    public:
	id_exception(void);
	id_exception(const char *, unsigned int);
	id_exception(const std::string&, unsigned int);
	id_exception(const id_exception&) noexcept;
	~id_exception(void);

	id_exception& operator =(const id_exception&);
	unsigned int get_id(void) const;
	const char *what(void) const noexcept override;
    };
}

#endif
