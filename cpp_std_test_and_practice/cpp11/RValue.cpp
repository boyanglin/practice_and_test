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

	/////////////////////////////////////////////////////////

	template<>
	double Class1::get<double>(size_t index) const {
		return mVector[index].first;
	}

	template<>
	std::string Class1::get<std::string>(size_t index) const {
		return mVector[index].second;
	}

	template<>
	void Class1::set<double>(const double value, size_t index) {
		mVector[index].first = value;
	}

	template<>
	void Class1::set<std::string>(const std::string value, size_t index){
		mVector[index].second = value;
	}

} //namespace RValue 