#include "GeneralTS.h"

#include <array>
#include <memory>
#include <utility>

#include "General.h"


using namespace boost::unit_test_framework;

namespace CPP_STD_TEST_AND_PRACTIVE_TS {

	void GeneralTS::TestFuncs() {
		BOOST_MESSAGE("TestFuncs");
		General::VectorWrapperTestFunction();
		COUT_LINE("");
		General::TestAssignmentOperator();
		COUT_LINE("");
		General::TestVectorReference();
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
			for (int i = 0; i < mSize; ++i)
				a1.destroy(interator++);
			a1.deallocate(p, mSize);
		};
	};

	void GeneralTS::TestSharedPtrOfArray() {
		size_t sizeNumber = 10;

		std::unique_ptr<double[]> ptrArrayUnique1 = std::unique_ptr<double[]>(new double[sizeNumber]);
		ptrArrayUnique1[0] = 1;
		ptrArrayUnique1[1] = 2;	
		*(ptrArrayUnique1.get() + 5) = 5;

		
		std::allocator<Data> a1;
		D d(sizeNumber);
		std::unique_ptr<Data[], D> ptrArrayUnique2 = std::unique_ptr<Data[], D>(a1.allocate(sizeNumber), d);

		Data defaultValue = std::make_pair(std::numeric_limits<double>::quiet_NaN(), "");
		std::uninitialized_fill_n(ptrArrayUnique2.get(), sizeNumber, defaultValue);
		for (size_t i = 0; i < sizeNumber; ++i)
			ptrArrayUnique2[i].first = i + 1;

		ptrArrayUnique2.reset();

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

	test_suite* GeneralTS::suite() {
		test_suite* suite = BOOST_TEST_SUITE("GeneralTS");
		suite->add(BOOST_TEST_CASE(&TestFuncs));
		suite->add(BOOST_TEST_CASE(&TestSharedPtrOfArray));
		//suite->add(BOOST_TEST_CASE(&TestDeleter));
		return suite;
	}
} //namespace CPP_STD_TEST_AND_PRACTIVE_TS