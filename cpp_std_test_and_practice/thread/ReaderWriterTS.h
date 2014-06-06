#ifndef READER_WRITER_TS_H_
#define READER_WRITER_TS_H_

#include <boost/test/unit_test.hpp>

namespace CPP_STD_TEST_AND_PRACTIVE_TS
{

	class ReaderWriterTS
	{
	public:
		//static void first_test();static SharedData sharedData
		static void TestUpdateRouter();
		static  boost::unit_test_framework::test_suite* suite();
	};


} //namespace KapUtilsUnitTests


#endif