#include "General.h"


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
}