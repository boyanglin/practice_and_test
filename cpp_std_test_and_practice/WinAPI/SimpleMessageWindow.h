#ifndef SIMPLE_MESSAGE_WINDOW_H_
#define SIMPLE_MESSAGE_WINDOW_H_

#include <boost/test/unit_test.hpp>

namespace WinApiTrial
{
	class SimpleMessageWindow
	{
	public:
		SimpleMessageWindow(const std::string & messageOwner);
		~SimpleMessageWindow();
	private:
		class SimpleMessageWindowImp;
		SimpleMessageWindowImp *mImp;
	};
} //namespace WinApiTrial

namespace CPP_STD_TEST_AND_PRACTIVE_TS
{

	class SimpleMessageWindowTS
	{
	public:
		static  boost::unit_test_framework::test_suite* suite();
	};


} //namespace CPP_STD_TEST_AND_PRACTIVE_TS

#endif