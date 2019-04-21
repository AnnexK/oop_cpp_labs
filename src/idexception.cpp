#include "idexception.hpp"
#include <cstring>

namespace oop_labs
{    
    id_exception::id_exception(void)
    {
	id = 0;
        msg = new char [1];
	*msg = '\0';
    }

    id_exception::id_exception(const char *msg, unsigned int id)
    {
	this->id = id; 
        this->msg = new char[strlen(msg) + 1];	
	strcpy(this->msg, msg);
    }
    
    id_exception::id_exception(const std::string& msg, unsigned int id)
    {
	this->id = id;
	this->msg = new char [msg.length() + 1];
	strcpy(this->msg, msg.c_str());	
    }

    id_exception::id_exception(const id_exception& op) noexcept
    {
	id = op.id;
        msg = new char[strlen(op.msg) + 1];
	strcpy(msg, op.msg);
    }
    
    id_exception::~id_exception(void)
    {
	delete[] msg;
    }

    id_exception& id_exception::operator =(const id_exception& op)
    {
        if (this != &op)
        {
            id = op.id;
            delete[] msg;
            msg = new char [strlen(op.msg) + 1];
            strcpy(msg, op.msg);
        }

	return *this;
    }

    unsigned int id_exception::get_id(void) const { return id; }
    const char *id_exception::what(void) const noexcept { return msg; }
}
