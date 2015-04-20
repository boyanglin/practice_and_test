#include <iostream>

#include "Chapter4.h"
#include "Item20.h"
#include "../cpp11/Common.h"

namespace Item20
{
	//Item 20
	//Passing parameters by reference also avoids the slicing problem.When
	//a derived class object is passed(by value) as a base class object, the
	//base class copy constructor is called, and the specialized features that
	//make the object behave like a derived class object are “sliced” off.

	namespace
	{
		void printNameAndDisplay(Item20::Base object)
		{
			SHOW_FUNCTION_NAME;
			COUT_LINE("object.getName(): ");
			COUT_LINE(object.getName().c_str());
			COUT_LINE("object.showName(): ");
			object.showName();
		}
	} // anonymous namespace

	void TestFunc()
	{	
		SHOW_FUNCTION_NAME
		COUT_LINE("***** Before create a Derive object *****");
		COUT_LINE("Item20::Derive deriveObject;");
		Item20::Derive deriveObject;
		COUT_LINE("***** After create a Derive object *****");

		COUT_LINE("deriveObject.getName(): ");
		COUT_LINE(deriveObject.getName().c_str());
		COUT_LINE("deriveObject.showName(): ");
		deriveObject.showName();
		COUT_LINE("***** Call void printNameAndDisplay(Item20::Base object) *****");
		printNameAndDisplay(deriveObject);
	}

} //namespace Item20

namespace EffectiveCpp
{
	void Chapter4::operator()()
	{
		Item20::TestFunc();
	}
} // namespace EffectiveCpp
