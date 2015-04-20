#include "GeneralTS.h"

#include <array>
#include <memory>
#include <utility>

#include <boost\date_time.hpp>
#include "General.h"


using namespace boost::unit_test_framework;

namespace CPP_STD_TEST_AND_PRACTIVE_TS {

	void GeneralTS::TestFuncs() {
		//BOOST_MESSAGE("TestFuncs");
		//General::VectorWrapperTestFunction();
		//COUT_LINE("");
		//General::TestAssignmentOperator();
		//COUT_LINE("");
		//General::TestVectorReference();
		COUT_LINE("");
		General::TestStdArray();
	}

	typedef	std::pair<double, std::string> Data;

	class D { // deleter
		std::allocator<Data> a1;
		size_t mSize;
	public:
		D(size_t n) { mSize = n; }
		void operator()(Data* p) {
			if (p == nullptr) return;
			auto interator = p;
			for (size_t i = 0; i < mSize; ++i)
				a1.destroy(interator++);
			a1.deallocate(p, mSize);
		};
	};

	void GeneralTS::TestSharedPtrOfArray() {
		size_t testLoopNumber = 10000;
		size_t sizeNumber = 2000;
		static const Data defaultValue = std::make_pair(std::numeric_limits<double>::quiet_NaN(), "");

		boost::posix_time::ptime p_start1 = boost::posix_time::second_clock::local_time();

		for (size_t loop = 0; loop < testLoopNumber; ++loop) {
			std::unique_ptr<Data[]> ptrArrayUnique1 = std::unique_ptr<Data[]>(new Data[sizeNumber]);
			std::fill(ptrArrayUnique1.get(), ptrArrayUnique1.get() + sizeNumber, std::move(defaultValue));
			for (size_t i = 0; i < sizeNumber; ++i)
				ptrArrayUnique1[i].first = i + 1;
		}
		
		boost::posix_time::time_duration dur1 = boost::posix_time::second_clock::local_time() - p_start1;
		std::cout << "test1: " << dur1.total_seconds() << std::endl;

		boost::posix_time::ptime p_start2 = boost::posix_time::second_clock::local_time();

		for (size_t loop = 0; loop < testLoopNumber; ++loop) {
			std::allocator<Data> a1;
			D d(sizeNumber);
			std::unique_ptr<Data[], D> ptrArrayUnique2 = std::unique_ptr<Data[], D>(a1.allocate(sizeNumber), d);

			auto p = ptrArrayUnique2.get();
			std::uninitialized_fill(ptrArrayUnique2.get(), ptrArrayUnique2.get() + sizeNumber, defaultValue);
			for (size_t i = 0; i < sizeNumber; ++i)
				ptrArrayUnique2[i].first = i + 1;
		}
		boost::posix_time::time_duration dur2 = boost::posix_time::second_clock::local_time() - p_start2;
		std::cout << "test2: " << dur2.total_seconds() << std::endl;
	}

	void GeneralTS::TestDeleter() {
		size_t sizeNumber = 10;
		std::allocator<Data> a1;
		Data* data = a1.allocate(sizeNumber);
		Data defaultValue = std::make_pair(std::numeric_limits<double>::quiet_NaN(), "");
		std::uninitialized_fill_n(data, sizeNumber, defaultValue);
		auto q = data;
		for (size_t i = 0; i < sizeNumber; ++i)
			(q++)->first = i + 1;

		auto p = data;
		for (size_t i = 0; i < sizeNumber; ++i) {
			a1.destroy(p++);
		}
		a1.deallocate(data, sizeNumber);
		
	}

	void GeneralTS::TestNumberLimit() {
		double testDouble = std::numeric_limits<double>::quiet_NaN();
		if (testDouble == std::numeric_limits<double>::quiet_NaN())
			std::cout << "got not a number" << std::endl;
		std::cout << testDouble << std::endl;
	}

	void GeneralTS::TestEither()
	{
		double aDouble = 1.12;
		std::string aString = "Test";
		General::Either aEither_1 = aDouble;
		General::Either aEither_2 = aString;
		General::Either aEither_3;
		BOOST_CHECK(!aEither_1.IsEmpty());
		BOOST_CHECK(!aEither_2.IsEmpty());
		BOOST_CHECK(aEither_3.IsEmpty());

		General::Either aEither_4 = aEither_1;
		BOOST_CHECK(aEither_4.GetDouble() == aEither_1.GetDouble());
		aEither_1.Set(aString);
		BOOST_CHECK_THROW(aEither_1.GetDouble(), std::runtime_error);
		BOOST_CHECK(aEither_1.GetString() == aString);

	}

	void TestReturnConstArg()
	{
		General::MockObject aMockObject_1 = "new one";
		General::MockObject aMockObject_2 = General::TestFunc_ReturnConstArg(aMockObject_1);

		General::MockObject aMockObject_3 = "move old one";
		General::MockObject aMockObject_4 = General::TestFunc_ReturnConstArg(aMockObject_3);

		General::MockObject aMockObject_5 = "copy old one";
		General::MockObject aMockObject_6 = General::TestFunc_ReturnConstArg(aMockObject_5);

	}

	test_suite* GeneralTS::suite() {
		test_suite* suite = BOOST_TEST_SUITE("GeneralTS");
		//suite->add(BOOST_TEST_CASE(&TestFuncs));
		//suite->add(BOOST_TEST_CASE(&TestSharedPtrOfArray));
		//suite->add(BOOST_TEST_CASE(&TestDeleter));
		//suite->add(BOOST_TEST_CASE(&TestNumberLimit));
		//suite->add(BOOST_TEST_CASE(&TestEither));
		suite->add(BOOST_TEST_CASE(&TestReturnConstArg));
		return suite;
	}
} //namespace CPP_STD_TEST_AND_PRACTIVE_TS