#include "General.h"

#include <array>
#include <numeric>

namespace General {
	void VectorWrapperTestFunction() 
	{

		SHOW_FUNCTION_NAME;

		VectorWrapper<long> testVector;
		for (size_t i = 0; i < 10; ++i)
			testVector.push_back(i);

		for (auto it = testVector.begin(); it != testVector.end(); ++it)
		{}

		for (auto it = testVector.cbegin(); it != testVector.cend(); ++it) 
		{}

		decltype(testVector) testVectorCopy = testVector;
		decltype(testVector)& testVectorRef = testVector;
		const decltype(testVector)& testVectorConstRef = testVector;

		for (auto it = testVectorCopy.begin(), end = testVectorCopy.end(); it != end; ++it)
			*it = *it * 10;

		// ******* error ******* 
		// error C3892: 'it' : you cannot assign to a variable that is const
		// *********************
		//for (auto it = testVectorCopy.cbegin(), end = testVectorCopy.cend(); it != end; ++it)
		//	*it = *it * 10;
	}

	void TestAssignmentOperator() 
	{
		SHOW_FUNCTION_NAME;

		VectorWrapper<long> testVector(10, 0);

		for (auto it = testVector.begin(), end = testVector.end(); it != end; ++it)
			*it = std::distance(it, end);

		decltype(testVector) copyVector_1;
		copyVector_1 = testVector;
		VectorWrapper<long> copyVector2 = copyVector_1;
		VectorWrapper<long> copyVector3(copyVector_1);

		VectorWrapper<long> copyVector4 = VectorWrapper<long>(10, 3);

		std::string a = "100";

	}

	void TestVectorReference() 
	{
		SHOW_FUNCTION_NAME;
		std::vector<long>& testVector = std::vector<long>(10, 1);
		for (auto it = testVector.begin(), end = testVector.end(); it != end; ++it)
			*it = std::distance(it, end);

	}

	void TestStdArray() {
		std::array<double, 3> testArray1;
		testArray1.at(0) = 1;
		testArray1.at(1) = 2;
		testArray1.at(2) = 3;

		std::array<double, 3> testArray2(testArray1);
		testArray1.at(0) = 11;
		testArray1.at(1) = 12;
		testArray1.at(2) = 13;

		std::cout << "testArray1;testArray2" << std::endl;
		for (size_t i = 0; i < 3; ++i)
			std::cout << testArray1.at(i) << "\t; " << testArray2.at(i) <<std::endl;
		
		std::array<double, 6> testArray3, testArray4, testArray5;
		std::fill(testArray3.begin(), testArray3.end(), 1);
		std::fill(testArray4.begin(), testArray4.end(), 1);
		std::fill(testArray5.begin(), testArray5.end(), 1);

		testArray3[0] = 3u;
		testArray3[1] = 2u;
		testArray3[2] = 5u;

		for (auto iterator = testArray3.cbegin(), last = testArray3.cend(); iterator != last - 1; ++iterator) {
			if (*iterator == 1)
				if (!std::all_of(iterator + 1, last, [](size_t i){return i == 1; })) {
					std::cout << "testArray3 failed" << std::endl;
					break;
				}
		}

		testArray4[3] = 54u;
		testArray4[4] = 12u;
		for (auto iterator = testArray4.cbegin(), last = testArray4.cend(); iterator != last - 1; ++iterator) {
			if (*iterator == 1)
			if (!std::all_of(iterator + 1, last, [](size_t i){return i == 1; })) {
				std::cout << "testArray4 failed" << std::endl;
				break;
			}
		}

		testArray5[2] = 12u;
		testArray5[4] = 21u;
		for (auto iterator = testArray5.cbegin(), last = testArray5.cend(); iterator != last - 1; ++iterator) {
			if (*iterator == 1)
			if (!std::all_of(iterator + 1, last, [](size_t i){return i == 1; })) {
				std::cout << "testArray5 failed" << std::endl;
				break;
			}
		}

		std::cout << "Number of elements bigger than one in testArray3: " << std::count_if(testArray3.cbegin(), testArray3.cend(), [](size_t number){ return number > 1; }) << std::endl;

		std::cout << "The product of elements in testArray5: " << std::accumulate(testArray5.cbegin(), testArray5.cend(), 1, [](size_t num1, size_t num2){ return num1 * num2; }) << std::endl;

		std::array<std::pair<double, std::string>, 5> testArray6;
		testArray6[0].first = 1.1;
		testArray6[1].second = "second";
		testArray6[2].first = 3.3;
		testArray6[2].second = "third";

		std::array<std::pair<double, std::string>, 5> testArray7(testArray6);
		testArray7[0].first = 1.2;
		testArray7[1].second = "SECOND";
		testArray7[2].first = 3.4;
		testArray7[4].second = "fifth";

		typedef std::pair<double, std::string> Data;
		Data* data1 = new Data[10];
		data1->first = 0.1;
		data1->second = "0.1";
		(data1 + 1)->first = 0.2;
		(data1 + 2)->first = 0.3;
		(data1 + 3)->second = "0.4";

		Data* data2 = new Data[10];
		std::copy(data1, data1 + 10, data2);
		data2->first = 1.0;
		data2->second = "2";
		(data2 + 5)->first = 5.0;

		std::cout << "data1:" << std::endl;
		for (size_t i = 0; i < 10; ++i)
			std::cout << i+1 << " element:" << (data1+i)->first << ", " << (data1+i)->second.c_str() << std::endl;
		
		std::cout << "data2:" << std::endl;
		for (size_t i = 0; i < 10; ++i)
			std::cout << i + 1 << " element:" << (data2 + i)->first << ", " << (data2 + i)->second.c_str() << std::endl;

		delete[] data2;
		delete[] data1;
	}
}