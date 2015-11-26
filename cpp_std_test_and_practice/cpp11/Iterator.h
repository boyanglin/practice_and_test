#ifndef ITERATOR_H_
#define ITERATOR_H_

#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>

#include <boost/test/unit_test.hpp>

#include <unordered_map>

namespace General
{
	class Value
	{
	public:
		
		Value(long value)
		{
			mValue = value;
		}

	private:
		long mValue;
	};

	class Iterator
	{
	public :
		typedef std::unordered_map<std::string, boost::shared_ptr<long> > MyHash;
		typedef MyHash::iterator iterator;
		typedef MyHash::const_iterator const_iterator;

		Iterator()
		{
			//mHash["Test1"] = boost::make_shared<Value>(Value(1L));
			//mHash["Test2"] = boost::make_shared<Value>(Value(2L));
			//mHash["Test3"] = boost::make_shared<Value>(Value(3L));
			mHash["Test1"] = boost::make_shared<long>(1L);
			mHash["Test2"] = boost::make_shared<long>(2L);
			mHash["Test3"] = boost::make_shared<long>(3L);
		}

		iterator begin() { return mHash.begin(); }
		iterator end() { return mHash.end(); }
		const_iterator cbegin() { return mHash.cbegin(); }
		const_iterator cend() { return mHash.cend(); }

	private:
		MyHash mHash;
	};
}


namespace CPP_STD_TEST_AND_PRACTIVE_TS
{

	class IteratorTS
	{
	public:
		static  boost::unit_test_framework::test_suite* suite();
	};
} //namespace CPP_STD_TEST_AND_PRACTIVE_TS
#endif