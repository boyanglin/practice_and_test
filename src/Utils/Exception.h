#ifndef EXCEPTION_H_
#define EXCEPTION_H_

//#include <cstring>
#include <exception>
#include <iostream>
#include <sstream>
#include <string>
#include <stdexcept>

#define __FILENAME__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)

#define ERROR(error_msg) \
std::ostringstream oss; \
oss << __FUNCTION__ << "@line " << __LINE__ << "@" << __FILENAME__ << ": " << error_msg; \
throw Exception(oss.str())



class Exception : std::exception
{
	std::string error_messsage_;
public:
	Exception(const std::string & error_message) noexcept
	{
		try 
		{
			error_messsage_ = error_message;
		}
		catch (std::exception & error)
		{
			std::cout << "ERROR: An error occurs when construct Excpetion object: ";
			std::cout << error.what() << std::endl;
		}
	}

	Exception(std::string && error_message) noexcept
	{
		try 
		{
			error_messsage_ = std::move(error_message);
		}
		catch (std::exception & error)
		{
			std::cout << "ERROR: An error occurs when construct Excpetion object: ";
			std::cout << error.what() << std::endl;
		}
	}

	Exception(const Exception& other) noexcept
	{
		try 
		{
			error_messsage_ = other.error_messsage_;
		}
		catch (std::exception & error)
		{
			std::cout << "ERROR: An error occurs when construct Excpetion object: ";
			std::cout << error.what() << std::endl;
		}
	}

	Exception& operator= (const Exception& rhs) noexcept
	{
		try 
		{
			Exception local = rhs;
			std::swap(local, *this);
            return *this;
		}
		catch (std::exception & error)
		{
			std::cout << "ERROR: An error occurs when construct Excpetion object: ";
			std::cout << error.what() << std::endl;
		}
        return *this;
	}

	virtual ~Exception() override
	{}

	virtual const char* what() const noexcept override
	{
		return error_messsage_.c_str();
	}

};

#endif //EXCEPTION_H_