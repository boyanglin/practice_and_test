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

/////////////////////////////////////////////////////////

class Class1 {
public:
	typedef std::pair<double, std::string> Data;

	template<class T>
	T get(size_t index) const;

	template<class T>
	void set(const T t, size_t index);

	Class1(size_t size_num){ mVector.resize(size_num); }

private:
	std::vector<Data> mVector;
};

	class Wedgit
	{
	public:
		//class Member
		//{
		//public:
		//	Member(const )

		//};
		//
		//Member move_;
		//Member not_move_;
		std::string move_;
		std::string not_move_;
	public:
		Wedgit(std::string &&not_to_move, std::string &&to_move)
			:not_move_(not_to_move), move_(std::move(to_move))
		{}
	};

} //namespace RValue

#endif //R_VALUE_H_