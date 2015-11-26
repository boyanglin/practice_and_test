#ifndef UTILITIES_H_
#define UTILITIES_H_

#include <iostream>
#include <vector>

#define PRINT_VARIABLE(var) std::cout << #var
#define PRINT_POD(var) PRINT_VARIABLE(var); \
						std::cout << " : " << var <<std::endl;
#define PRINT_VECTOR(var) PRINT_VARIABLE(var);\
						std::cout << " : ";\
						for (auto it = var.cbegin(); it != var.cend(); ++it)\
							std::cout << *it << " ";\
						std::cout << std::endl;


#endif //UTILITIES_H_