
#include "Polymorphism.h"
#include "PolymorphismTS.h"

#include <vector>

#include <memory>

#include <boost\date_time.hpp>

using namespace boost::unit_test_framework;
using namespace Polymorphism;

namespace CPP_STD_TEST_AND_PRACTIVE_TS
{

	void TestVirtualFunction()
	{
		BOOST_TEST_MESSAGE("****************************************");
		BOOST_TEST_MESSAGE("TestFunction: "+ std::string(__FUNCTION__));

		std::shared_ptr<Base> base_1 = std::make_shared<Polymorphism::Deriv1_Public>();
		base_1->myVirtualFunc_1();
		base_1->myVirtualFunc_2(); 
		//*-> we can still use myVirtualFunc_2 via Base class even though it is changed to be protected in Deriv1_Public
		//http://stackoverflow.com/questions/2141188/changing-function-access-mode-in-derived-class

		std::shared_ptr<Deriv1_Public> deriv1 = std::make_shared<Polymorphism::Deriv1_Public>();
		deriv1->myVirtualFunc_1();
		//deriv1->myVirtualFunc_2();
		//*-> myVirtualFunc_2 is protected in Deriv1_Public
		//	c:\workarea\practice_and_test\cpp_std_test_and_practice\cpp11\polymorphismts.cpp(30) : error C2248 :
		//	'Polymorphism::Deriv1_Public::myVirtualFunc_2' : cannot access protected member declared in class 'Polymorphism::Deriv1_Public'

		std::shared_ptr<Base> base_2 = std::make_shared<Polymorphism::Deriv2_Public>();
		base_2->myVirtualFunc_1();
		base_2->myVirtualFunc_2();

		std::shared_ptr<Deriv2_Public> deriv2 = std::dynamic_pointer_cast<Deriv2_Public>(base_2);
		deriv2->myVirtualFunc_1();
		//deriv2->myVirtualFunc_2();
		//*-> myVirtualFunc_2 is protected in Deriv1_Public and Deriv2_Public public inherit from Deriv1_Public
		//	c:\workarea\practice_and_test\cpp_std_test_and_practice\cpp11\polymorphismts.cpp(46) : error C2248 :
		//	'Polymorphism::Deriv1_Public::myVirtualFunc_2' : cannot access protected member declared in class 'Polymorphism::Deriv1_Public'

		BOOST_TEST_MESSAGE("****************************************");
	}

	test_suite* PolymorphismTS::suite()
	{
		test_suite* suite = BOOST_TEST_SUITE("Polymorphism");
		suite->add(BOOST_TEST_CASE(&TestVirtualFunction));
		return suite;
	}
} //namespace CPP_STD_TEST_AND_PRACTIVE_T