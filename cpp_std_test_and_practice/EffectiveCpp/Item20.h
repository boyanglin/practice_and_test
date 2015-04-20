//Item 20
//Passing parameters by reference also avoids the slicing problem.When
//a derived class object is passed(by value) as a base class object, the
//base class copy constructor is called, and the specialized features that
//make the object behave like a derived class object are “sliced” off.

#ifndef ITEM20_TS_H_
#define ITEM20_TS_H_

#include <iostream>
#include <string>

namespace Item20
{
	class Base
	{
	public:
		Base()
			:mName("Name 1")
		{
			std::cout << "Create a Base Class.\n";
		}

		std::string getName()
		{
			return mName;
		}

		virtual void showName()
		{
			std::cout << "This is the " + mName << ".\n";
		}
	protected:
		std::string mName;
	};

	class Derive : public Base
	{
	public:
		Derive()
			:Base(), mAdditionalInfo("Name 2")
		{
			std::cout << "Create a Derive Class.\n";
		}

		void showName()
		{
			std::cout << "This is the " + mName + " and the " + mAdditionalInfo + ".\n";
		}
	private:
		std::string mAdditionalInfo;
	};
}

#endif //ITEM20_TS_H_