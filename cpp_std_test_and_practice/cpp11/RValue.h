#ifndef R_VALUE_H_
#define R_VALUE_H_

#include <string>
#include <vector>

namespace RValue {

std::vector<std::string> getVector();

class MyObject {
public:
	MyObject() :mString("MyObject"){}
private:
	std::string mString;
};

MyObject getMyObject();

} //namespace RValue

#endif //R_VALUE_H_