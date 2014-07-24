#ifndef GENERAL_H_
#define GENERAL_H_

#include <iostream>
#include <vector>

#define COUT_LINE(msg) std::cout << msg << std::endl;
#define SHOW_FUNCTION_NAME COUT_LINE(std::string(__FUNCTION__).c_str());

namespace General {
	template<class T>
	class VectorWrapper {
	public:
		typedef std::vector<T> MyVector;
		typedef typename MyVector::iterator iterator;
		typedef typename MyVector::const_iterator const_iterator;

		VectorWrapper()
		{
			COUT_LINE("default constructor");
		}

		VectorWrapper(size_t size) : mVector(size) 
		{
			COUT_LINE("fill constructor");
		}

		VectorWrapper(size_t size, const T& t) : mVector(size, t)
		{
			COUT_LINE("fill constructor (with initial value)");
		}

		VectorWrapper(const_iterator itFirst, const_iterator itLast): mVector(itFirst, itLast) 
		{
			COUT_LINE("Constructor a VectorWrapper using const iterator");
		}

		VectorWrapper(iterator itFirst, iterator itLast) : mVector(itFirst, itLast) 
		{
			COUT_LINE("Constructor a VectorWrapper using const iterator");
		}

		VectorWrapper(const VectorWrapper& source) 
		{
			COUT_LINE("copy constructor");
			mVector = source.mVector;
		}

		VectorWrapper& operator=(const VectorWrapper& source)
		{

			COUT_LINE("assignment operator");
			mVector = source.mVector;
			return *this;
		}

		iterator begin() // can't add const
		{ 
			COUT_LINE("get begin iterator");
			return mVector.begin(); 
		}

		iterator end() // can't add const
		{ 
			COUT_LINE("get end iterator");
			return mVector.end();
		}

		const_iterator cbegin() const
		{
			COUT_LINE("get begin const_iterator");
			return mVector.begin();
		}

		const_iterator cend() const
		{
			COUT_LINE("get end const_iterator");
			return mVector.end();
		}

		void push_back(const T& t) 
		{
			mVector.push_back(t);
		}

	private:
		MyVector mVector;
	};

	void VectorWrapperTestFunction();
	void TestAssignmentOperator();
	void TestVectorReference();
	void TestStdArray();

} //namespace General

#endif //R_VALUE_H_