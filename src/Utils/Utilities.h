#ifndef UTILITIES_H_
#define UTILITIES_H_

#include <iostream>
#include <vector>

#define SETW(num) std::cout << std::setw(num)
#define PRINT_VALUE(val) std::cout << val
#define PRINT_VARIABLE(var) PRINT_VALUE(#var)
#define PRINT_POD(var) PRINT_VARIABLE(var); \
						std::cout << " : " << var <<std::endl;
#define PRINT_VECTOR(var) PRINT_VARIABLE(var);\
						std::cout << " : ";\
						for (auto it = var.cbegin(); it != var.cend(); ++it)\
							std::cout << *it << " ";\
						std::cout << std::endl;

#define PRINT_LINE(line) std::cout << line << std::endl
#define PRINT_MSG(msg) SETW(8); PRINT_VALUE("msg - "); PRINT_LINE(msg);
#define PRINT_ERR(err) SETW(8); PRINT_VALUE("err - "); PRINT_LINE(err);
#define PRINT_AND_RUN_CODE(code) SETW(8); PRINT_VALUE("code - "); PRINT_LINE(#code << ";"); code 
#define PRINT_FUNCTION_NAME PRINT_LINE("Function: " << std::string(__FUNCTION__).c_str())

#define ASSERT(condition, message) if(!condition) throw std::runtime_error(message)

// copied from: http://stackoverflow.com/a/20170989
template <class T>
std::string type_name()
{
	typedef typename std::remove_reference<T>::type TR;
	std::unique_ptr<char, void(*)(void*)> own
		(
#ifndef _MSC_VER
			abi::__cxa_demangle(typeid(TR).name(), nullptr,
				nullptr, nullptr),
#else
			nullptr,
#endif
			std::free
			);
	std::string r = own != nullptr ? own.get() : typeid(TR).name();
	if (std::is_const<TR>::value)
		r += " const";
	if (std::is_volatile<TR>::value)
		r += " volatile";
	if (std::is_lvalue_reference<T>::value)
		r += "&";
	else if (std::is_rvalue_reference<T>::value)
		r += "&&";
	return r;
}


#endif //UTILITIES_H_