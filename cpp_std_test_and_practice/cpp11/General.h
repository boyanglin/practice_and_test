#ifndef GENERAL_H_
#define GENERAL_H_

#include "Common.h"

#include <boost/tr1/cmath.hpp>
#define _SCL_SECURE_NO_WARNINGS

#pragma warning( disable : 4521 4522 )

void GeneralFuncTest();

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

	class Either
	{
	public:
		Either(const std::string& value)
			:mHasDouble(false)
		{
			memset(&mValue, 0, sizeof(mValue));
			mValue.mText = new std::string(value);
		}
		Either(const double value)
			:mHasDouble(false)
		{
			memset(&mValue, 0, sizeof(mValue));
			mValue.mDouble = value;
			mHasDouble = true;
		}

		Either()
			:mHasDouble(false)
		{
			memset(&mValue, 0, sizeof(mValue));
			mValue.mDouble = std::numeric_limits<double>::quiet_NaN();
		}

		~Either()
		{
			clear();
		}

		void Set(const double value)
		{
			clear();
			mValue.mDouble = value;
			mHasDouble = true;
		}

		void Set(const std::string& value)
		{
			clear();
			mValue.mText = new std::string(value);
		}


		double GetDouble()
		{
			if (mHasDouble)
				return mValue.mDouble;
			else
				throw std::runtime_error("Not a number");
		}

		std::string GetString()
		{
			if (!mHasDouble)
				return *(mValue.mText);
			else
				throw std::runtime_error("Not a string");
		}

		bool IsEmpty()
		{
			return !mHasDouble &&  (!mValue.mText);
		}

	private:
		union 
		{
			double mDouble;
			std::string* mText;
		} mValue;

		bool mHasDouble;

		void clear()
		{
			if (mHasDouble)
			{
				mHasDouble = false;
			} 
			else
			{
				if (mValue.mText)
					delete mValue.mText;
			}
			memset(&mValue, 0, sizeof(mValue));
		}
	};

	class MockObject
	{
		std::string mString;

		void swap(MockObject & other)
		{
			std::swap(this->mString, other.mString);
		}
	public:
		MockObject();

		MockObject(const std::string & string)
			:mString(string)
		{
		}

		MockObject(const MockObject & mockObject)
		{
			std::cout << "Call: MockObject(const MockObject & mockObject)" << std::endl;
			this->mString = mockObject.mString;
		}

		MockObject(MockObject & mockObject)
		{
			std::cout << "Call: MockObject(MockObject & mockObject)" << std::endl;
			this->mString = mockObject.mString;
		}

		//	c:\workarea\practice_and_test\cpp_std_test_and_practice\cpp11\general.h(195) : error C2652 : 'General::MockObject' : illegal copy constructor : first parameter must not be a 'General::MockObject'
		//MockObject(MockObject mockObject)
		//{
		//	this->mString = mockObject.mString;
		//}
		
		MockObject & operator=(MockObject rhs)
		{
			std::cout << "Call: MockObject & operator=(MockObject rhs)" << std::endl;
			swap(rhs);
			return *this;
		}

		MockObject & operator=(const MockObject & rhs)
		{
			std::cout << "Call: MockObject & operator=(const MockObject & rhs)" << std::endl;
			MockObject aTemp = rhs;
			swap(aTemp);
			return *this;
		}

		MockObject & operator=( MockObject & rhs)
		{
			std::cout << "Call: MockObject & operator=( MockObject & rhs)" << std::endl;
			MockObject aTemp = rhs;
			swap(aTemp);
			return *this;
		}


		std::string GetString() const
		{
			return mString;
		}

	};

	MockObject TestFunc_ReturnConstArg(const MockObject & mockObject);

	class ChainAssignmentObject
	{
	public:
		ChainAssignmentObject() {}
		ChainAssignmentObject(std::string msg)
			: mMessage(msg)
		{
		}

		ChainAssignmentObject(const ChainAssignmentObject & rhs)
		{
			std::cout << "ChainAssignmentObject(const ChainAssignmentObject & rhs)" << std::endl;
			this->mMessage = rhs.mMessage;
		}

		ChainAssignmentObject operator=(const ChainAssignmentObject & rhs)
		{
			std::cout << "ChainAssignmentObject operator=(const ChainAssignmentObject & rhs)" << std::endl;
			ChainAssignmentObject aTemp = rhs;
			std::swap(this->mMessage, aTemp.mMessage);
			return *this;
		}

		ChainAssignmentObject operator=(const std::string & rhs)
		{
			std::cout << "ChainAssignmentObject operator=(const std::string & rhs)" << std::endl;
			operator=(ChainAssignmentObject(rhs));
			return *this;
		}

		std::string GetMessage()
		{
			return mMessage;
		}
	private:
		std::string mMessage;
	};


} //namespace General

#endif //R_VALUE_H_