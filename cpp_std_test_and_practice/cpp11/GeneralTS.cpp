#include "GeneralTS.h"

#include <array>
#include <memory>
#include <utility>

#include <boost\date_time.hpp>

#include "General.h"

#include "ArrayTest.h"


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

	void TestAssignmentOperator()
	{
		General::ChainAssignmentObject x, y, z;
		x = y = z = "5";
		std::cout << x.GetMessage() << std::endl;
		std::cout << y.GetMessage() << std::endl;
		std::cout << z.GetMessage() << std::endl;
	}

	void TestDefaultValueOfArray()
	{
		size_t aArray[10];
		for (auto i = 0; i < 10; ++i)
		{
			std::cout << i << std::setw(20) << aArray[i] << std::endl;
		}
	}

	void TestArrayOfCharArray()
	{
		char * aCharArray[100];
		aCharArray[0] = "This";
		aCharArray[1] = "is";
		aCharArray[2] = "a";
		aCharArray[3] = "shit";
		aCharArray[4] = "job";
		aCharArray[5] = ".";
		for (auto i = 0; i < 100; ++i)
		{
			std::cout << aCharArray[i] << " " << std::endl;
		}
	}


	void TestArrayOfStructure()
	{
		/* initialize random seed: */
		srand(time(NULL));

		const unsigned long test_number = 262144;
		const size_t test_times = 512;
		unsigned short indices[test_number];
		/* generate secret number between 1 and 10: */
		for (unsigned long i = 0; i < test_number; ++i)
		{
			indices[i] = rand() % 500;
		}

		size_t stats_depre_1[5] = { 0 };
		boost::posix_time::ptime p_start1 = boost::posix_time::microsec_clock::local_time();
		for (auto j = 0; j < test_times; ++j)
		for (unsigned long i = 0; i < test_number; i++)
		{
			unsigned short depre_number = General::getFuncDepre1(indices[i]);
			if (depre_number == 4)
				++stats_depre_1[4];
			else if (depre_number == 3)
				++stats_depre_1[3];
			else if (depre_number == 2)
				++stats_depre_1[2];
			else if (depre_number == 1)
				++stats_depre_1[1];
			else
				++stats_depre_1[0];
		}
		boost::posix_time::time_duration dur1 = boost::posix_time::microsec_clock::local_time() - p_start1;

		size_t stats_depre_2[5] = { 0 };
		boost::posix_time::ptime p_start2 = boost::posix_time::microsec_clock::local_time();
		for (auto j = 0; j < test_times; ++j)
		for (unsigned long i = 0; i < test_number; i++)
		{
			unsigned char depre_number = General::getFuncDepre2(indices[i]);
			if (depre_number == '4')
				++stats_depre_2[4];
			else if (depre_number == '3')
				++stats_depre_2[3];
			else if (depre_number == '2')
				++stats_depre_2[2];
			else if (depre_number == '1')
				++stats_depre_2[1];
			else
				++stats_depre_2[0];
		}
		boost::posix_time::time_duration dur2 = boost::posix_time::microsec_clock::local_time() - p_start2;

		size_t stats_depre_3[5] = { 0 };
		boost::posix_time::ptime p_start3 = boost::posix_time::microsec_clock::local_time();
		for (auto j = 0; j < test_times; ++j)
			for (unsigned long i = 0; i < test_number; i++)
			{
				unsigned char depre_number = General::getFuncDepre3(indices[i]);
				if (depre_number == 4)
					++stats_depre_3[4];
				else if (depre_number == 3)
					++stats_depre_3[3];
				else if (depre_number == 2)
					++stats_depre_3[2];
				else if (depre_number == 1)
					++stats_depre_3[1];
				else
					++stats_depre_3[0];
			}
		boost::posix_time::time_duration dur3 = boost::posix_time::microsec_clock::local_time() - p_start3;


		size_t total_1(0), total_2(0), total_3(0);
		for (auto i = 0; i < 5; ++i)
		{
			std::cout << "deprecation " << i << ": " << std::endl;
			std::cout << "\t" << "Case 1: " << stats_depre_1[i] << "; " << "Case 2: " << stats_depre_2[i] << "; " << "Case 3: " << stats_depre_3[i] << std::endl;
			total_1 += stats_depre_1[i];
			total_2 += stats_depre_2[i];
			total_3 += stats_depre_3[i];
		}
		std::cout << "total:" << std::endl;
		std::cout << "\t" << "Case 1: " << total_1 << "; " << "Case 2: " << total_2 << "; " << "Case 3: " << total_3<< std::endl;


		std::cout << "time duration: \n";
		std::cout << "\t" << "Case 1: " << dur1.total_microseconds() << std::endl; 
		std::cout << "\t" << "Case 2: " << dur2.total_microseconds() << std::endl;
		std::cout << "\t" << "Case 3: " << dur3.total_microseconds() << std::endl;
	}

	test_suite* GeneralTS::suite() {
		test_suite* suite = BOOST_TEST_SUITE("GeneralTS");
		suite->add(BOOST_TEST_CASE(&TestFuncs));
		suite->add(BOOST_TEST_CASE(&TestSharedPtrOfArray));
		suite->add(BOOST_TEST_CASE(&TestDeleter));
		suite->add(BOOST_TEST_CASE(&TestNumberLimit));
		suite->add(BOOST_TEST_CASE(&TestEither));
		suite->add(BOOST_TEST_CASE(&TestReturnConstArg));
		suite->add(BOOST_TEST_CASE(&TestAssignmentOperator));
		suite->add(BOOST_TEST_CASE(&TestDefaultValueOfArray));
		suite->add(BOOST_TEST_CASE(&TestArrayOfCharArray));
		suite->add(BOOST_TEST_CASE(&TestArrayOfStructure));
		return suite;
	}
} //namespace CPP_STD_TEST_AND_PRACTIVE_TS