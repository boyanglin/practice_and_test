#include "RValueTS.h"

#include <vector>

#include <boost\date_time.hpp>

#include "RValue.h"

using namespace boost::unit_test_framework;

namespace CPP_STD_TEST_AND_PRACTIVE_TS {

	void RValueTS::TestFuncs() {
		size_t times = 10000000;
		{
			auto startTime = boost::posix_time::second_clock::local_time();
			for (size_t i = 0; i < times; ++i) {
				std::vector<std::string> test1 = RValue::getVector();
			}
			auto timeDuration = boost::posix_time::second_clock::local_time() - startTime;
			std::cout << "Copy: " << timeDuration.total_seconds() << " seconds" << std::endl;
		}

		{
			auto startTime = boost::posix_time::second_clock::local_time();
			for (size_t i = 0; i < times; ++i) {
				std::vector<std::string>& test1 = RValue::getVector();
			}
			auto timeDuration = boost::posix_time::second_clock::local_time() - startTime;
			std::cout << "Reference: " << timeDuration.total_seconds() << " seconds" << std::endl;
		}

		{
			auto startTime = boost::posix_time::second_clock::local_time();
			for (size_t i = 0; i < times; ++i) {
				std::vector<std::string>&& test1 = RValue::getVector();
			}
			auto timeDuration = boost::posix_time::second_clock::local_time() - startTime;
			std::cout << "Reference: " << timeDuration.total_seconds() << " seconds" << std::endl;
		}

		RValue::MyObject object1 = RValue::getMyObject();
		RValue::MyObject& object2 = RValue::getMyObject();
		RValue::MyObject&& object3 = RValue::getMyObject();
	}

	void RValueTS::TestClass1() {
		size_t vector_size = 10;
		RValue::Class1 class1 = RValue::Class1(vector_size);

		std::string szTest1 = "test1";
		std::string &szTest2 = std::string("test2");

		class1.set<std::string>(std::move(szTest1), 0);
		class1.set<double>(2, 1);
		class1.set<std::string>(std::move(szTest2), 2);
	}

	test_suite* RValueTS::suite() {
		test_suite* suite = BOOST_TEST_SUITE("RValueTS");
		//suite->add(BOOST_TEST_CASE(&first_test));
		//suite->add(BOOST_TEST_CASE(&TestFuncs));
		suite->add(BOOST_TEST_CASE(&TestClass1));
		return suite;
	}
} //namespace CPP_STD_TEST_AND_PRACTIVE_TS