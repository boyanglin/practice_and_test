#ifndef COMMON_H_
#define COMMON_H_

#include <iostream>
#include <vector>

#define COUT_LINE(msg) std::cout << msg << std::endl;
#define SHOW_FUNCTION_NAME COUT_LINE(std::string(__FUNCTION__).c_str());

#endif