#include "RValue.h"


namespace RValue {

	std::vector<std::string> getVector() {
		//std::vector<std::string> testVector;
		//testVector.resize(5);
		//testVector.at(0) = "this";
		//testVector.at(1) = "is";
		//testVector.at(2) = "a";
		//testVector.at(3) = "test";
		return std::move(std::vector<std::string>(100,"Test"));
	}

	MyObject getMyObject() {
		MyObject myObject;
		return myObject;
	}
} //namespace RValue 