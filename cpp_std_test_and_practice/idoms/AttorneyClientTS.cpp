#include "AttorneyClientTS.h"

#include "AttorneyClient.h"

#include <boost\thread\thread.hpp>

#include <iostream>

using namespace boost::unit_test_framework;

namespace Idioms_TS 
{
	void AttorneyClientTS::testAttorney()
	{
		long aVar1 = 10;
		long aVar2 = 20;

		std::cout << "Idioms::substractFunc(aVar1, aVar2) = " << Idioms::substractFunc(aVar1, aVar2) << std::endl;
		
		Idioms::Modifier aModifier;
		std::cout << "aModifier.CallPrivateFunc(aVar1, aVar2) = " << aModifier.CallPrivateFunc(aVar1, aVar2) << std::endl;

		Idioms::BaseClass aBaseClass;
		double aVar3 = 100;
		std::cout << "Before call aModifier.setNumberInBaseClass(aBaseClass, aVar3)" << std::endl;
		std::cout << "aBaseClass.getNumber() = " << aBaseClass.getNumber() << std::endl;
		aModifier.setNumberInBaseClass(aBaseClass, aVar3);
		std::cout << "After call aModifier.setNumberInBaseClass(aBaseClass, aVar3)" << std::endl;
		std::cout << "aBaseClass.getNumber() = " << aBaseClass.getNumber() << std::endl;

		BOOST_CHECK(true);
	}
	test_suite* AttorneyClientTS::suite()
	{
		test_suite* suite = BOOST_TEST_SUITE("AttorneyClientTS");

		suite->add(BOOST_TEST_CASE(&testAttorney));
		return suite;
	}
} // namespace Idioms_TS 