#include "Iterator.h"

#include <iterator>
#include <iostream>


namespace General
{
	namespace
	{
		//template<template<typename K, typename V, typename... rest> class H, typename K, typename V, typename... rest>
		//void DisplayContents(typename H<K, V, rest...>::const_iterator  begin,
		//					 typename H<K, V, rest...>::const_iterator  end)
		//{
		//	for (auto it = begin; it != end; ++it)
		//	{
		//		//std::cout << it->first << ": " << it->second;
		//	}
		//}
	}

	void TestFunc1()
	{
		BOOST_MESSAGE("TestFunc1");
		Iterator aObject;
		//std::cout << typeid(aObject.cbegin()).name() << std::endl;
		//std::cout << typeid(aObject.cbegin()).raw_name() << std::endl;
		//DisplayContents<std::unordered_map, std::string, boost::shared_ptr<long> >(aObject.cbegin(), aObject.cend());
	}
}

namespace CPP_STD_TEST_AND_PRACTIVE_TS
{
	using namespace boost::unit_test_framework;

	test_suite* IteratorTS::suite()
	{
		test_suite* suite = BOOST_TEST_SUITE("IteratorTS");
		suite->add(BOOST_TEST_CASE(&General::TestFunc1));
		return suite;
	}
} //namespace CPP_STD_TEST_AND_PRACTIVE_TS