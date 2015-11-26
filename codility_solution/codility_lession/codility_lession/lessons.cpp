#include "lessons.h"
#include "Utilities.h"


////////////////////////////////////////////////////////////////////////////////////////////////////
//	Lesson 1
////////////////////////////////////////////////////////////////////////////////////////////////////

// TapeEquilibrium
/*
///not
#include <vector>

/// yes
#include <numeric>


using namespace std;
int solutionTapeEquilibrium(vector<int> &A)
{
	// write your code in C++11
	long minDiff = abs(std::accumulate(A.cbegin(), A.cend(), 0) - *(A.cbegin()) * 2);
	for (auto it = ++(A.cbegin()); it != --(A.cend()); ++it)
	{
		if (abs(minDiff - *it * 2) < minDiff)
		{
			minDiff = abs(minDiff - *it * 2);
		}
	}
	return minDiff;
}

void Lesson1_TapeEquilibrium()
{
	std::cout << __FUNCTION__ << std::endl;
	std::vector<int> test1 = { 3, 1, 2, 4, 3 };
	std::cout << "Test 1 : " << solutionTapeEquilibrium(test1) << std::endl;

	std::vector<int> test2 = { 1,1,1,1,1 };
	std::cout << "Test 2 : " << solutionTapeEquilibrium(test2) << std::endl;

	std::vector<int> test3 = { 1,2,3,4,5 };
	std::cout << "Test 3 : " << solutionTapeEquilibrium(test3) << std::endl;

	std::vector<int> test4 = { 5,4,3,2,1 };
	std::cout << "Test 4 : " << solutionTapeEquilibrium(test4) << std::endl;

	std::vector<int> test5 = { 0, 0, 0, 0, 0 };
	std::cout << "Test 5 : " << solutionTapeEquilibrium(test5) << std::endl;

	std::vector<int> test6 = { 1, 1};
	std::cout << "Test 2 : " << solutionTapeEquilibrium(test6) << std::endl;

}

*/

//--------------------------------------------------------------------------------------------------

// FrogJmp 
/*
///not
#include <vector>

/// yes

using namespace std;
int solution_FrogJmp(int X, int Y, int D)
{
	// write your code in C++11
	int steps = static_cast<int>(ceil(static_cast<double>(abs(Y - X)) / D));
	return steps;
}

void Lesson1_FrogJmp()
{
	std::cout << __FUNCTION__ << std::endl;
	int X1 = 10, Y1 = 85, D1 = 30;
	std::cout << solution_FrogJmp(X1, Y1, D1) << std::endl;
}
*/

//--------------------------------------------------------------------------------------------------

//PermMissingElem
/*
//not
#include <vector>

//yes

using namespace std;
int solution(vector<int> &A)
{
	// write your code in C++11
	int result = 0;
	for (size_t index = 0; index < A.size(); ++index)
	{
		result = result ^ A[index] ^ (index + 1);
	}
	return result ^ (1 + A.size());

}
*/

//--------------------------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////////////////////////
//	Lesson 2
////////////////////////////////////////////////////////////////////////////////////////////////////

//FrogRiverOne
/*
A small frog wants to get to the other side of a river.The frog is currently located at position 0, and wants to get to position X.Leaves fall from a tree onto the surface of the river.

You are given a non - empty zero - indexed array A consisting of N integers representing the falling leaves.A[K] represents the position where one leaf falls at time K, measured in seconds.

The goal is to find the earliest time when the frog can jump to the other side of the river.The frog can cross only when leaves appear at every position across the river from 1 to X.You may assume that the speed of the current in the river is negligibly small, i.e.the leaves do not change their positions once they fall in the river.

For example, you are given integer X = 5 and array A such that :

A[0] = 1
A[1] = 3
A[2] = 1
A[3] = 4
A[4] = 2
A[5] = 3
A[6] = 5
A[7] = 4

In second 6, a leaf falls into position 5. This is the earliest time when leaves appear in every position across the river.

Write a function :

int solution(int X, int A[], int N);

that, given a non - empty zero - indexed array A consisting of N integers and integer X, returns the earliest time when the frog can jump to the other side of the river.

If the frog is never able to jump to the other side of the river, the function should return −1.

For example, given X = 5 and array A such that :

A[0] = 1
A[1] = 3
A[2] = 1
A[3] = 4
A[4] = 2
A[5] = 3
A[6] = 5
A[7] = 4

the function should return 6, as explained above.

Assume that :

N and X are integers within the range[1..100, 000];
each element of array A is an integer within the range[1..X].

Complexity:

expected worst - case time complexity is O(N);
expected worst - case space complexity is O(X), beyond input storage(not counting the storage required for input arguments).

Elements of input arrays can be modified.
*/

//--------------------------------------------------------------------------------------------------

//PermCheck
/*
A non - empty zero - indexed array A consisting of N integers is given.

A permutation is a sequence containing each element from 1 to N once, and only once.

For example, array A such that :

A[0] = 4
A[1] = 1
A[2] = 3
A[3] = 2

is a permutation, but array A such that :

A[0] = 4
A[1] = 1
A[2] = 3

is not a permutation, because value 2 is missing.

The goal is to check whether array A is a permutation.

Write a function :

int solution(int A[], int N);

that, given a zero - indexed array A, returns 1 if array A is a permutation and 0 if it is not.

For example, given array A such that :

A[0] = 4
A[1] = 1
A[2] = 3
A[3] = 2

the function should return 1.

Given array A such that :

A[0] = 4
A[1] = 1
A[2] = 3

the function should return 0.

Assume that :

N is an integer within the range[1..100, 000];
each element of array A is an integer within the range[1..1, 000, 000, 000].

Complexity:

expected worst - case time complexity is O(N);
expected worst - case space complexity is O(N), beyond input storage(not counting the storage required for input arguments).

Elements of input arrays can be modified.
*/
/*
//no
#include <vector>

//yes

using namespace std;
int solutionPermCheck(vector<int>& A)
{
	const long length = A.size();
	bool * count = new bool[length];
	for (long index = 0; index < length; ++index)
	{
		count[index] = true;
	}

	for (long index = 0; index < length; ++index)
	{
		if (A[index] > length) return 0;
		count[A[index]-1] = false;
	}

	for (long index = 0; index < length; ++index)
	{
		if (count[index])
			return 0;
	}
	return 1;

}

void Lesson1_PermCheck()
{
	vector<int> A1 = { 4, 1, 3, 2 };
	std::cout << solutionPermCheck(A1) << std::endl;

	vector<int> A2 = { 4, 1, 3};
	std::cout << solutionPermCheck(A2) << std::endl;
}
*/

//--------------------------------------------------------------------------------------------------

//MissingInteger
/*


Write a function:

    int solution(int A[], int N);

that, given a non-empty zero-indexed array A of N integers, returns the minimal positive integer (greater than 0) that does not occur in A.

For example, given:

  A[0] = 1
  A[1] = 3
  A[2] = 6
  A[3] = 4
  A[4] = 1
  A[5] = 2

the function should return 5.

Assume that:

        N is an integer within the range [1..100,000];
        each element of array A is an integer within the range [−2,147,483,648..2,147,483,647].

Complexity:

        expected worst-case time complexity is O(N);
        expected worst-case space complexity is O(N), beyond input storage (not counting the storage required for input arguments).

*/
/*
//yes
#include <vector>

//no

using namespace std;
int solutionMissingInteger(vector<int> &A)
{
	// write your code in C++11
	vector<bool> included(A.size() + 1, true);
	for (size_t index = 0; index < A.size() + 1; ++index)
	{
		if (A[index] > 0 && A[index] < static_cast<int>(A.size()) + 2)
			included[A[index] - 1] = false;
	}

	for (auto it = included.cbegin(); it != included.cend(); ++it)
	{
		if (*it)
			return std::distance(included.cbegin(), it) + 1;
	}

	return 0;
}

void Lesson2_MissingInteger()
{
	vector<int> A1 = { 1, 3, 6, 4, 1, 2 };
	std::cout << solutionMissingInteger(A1) << std::endl;
}
*/

//--------------------------------------------------------------------------------------------------

//MaxCounters
/*
You are given N counters, initially set to 0, and you have two possible operations on them:

        increase(X) − counter X is increased by 1,
        max counter − all counters are set to the maximum value of any counter.

A non-empty zero-indexed array A of M integers is given. This array represents consecutive operations:

        if A[K] = X, such that 1 ≤ X ≤ N, then operation K is increase(X),
        if A[K] = N + 1 then operation K is max counter.

For example, given integer N = 5 and array A such that:

    A[0] = 3
    A[1] = 4
    A[2] = 4
    A[3] = 6
    A[4] = 1
    A[5] = 4
    A[6] = 4

the values of the counters after each consecutive operation will be:

    (0, 0, 1, 0, 0)
    (0, 0, 1, 1, 0)
    (0, 0, 1, 2, 0)
    (2, 2, 2, 2, 2)
    (3, 2, 2, 2, 2)
    (3, 2, 2, 3, 2)
    (3, 2, 2, 4, 2)

The goal is to calculate the value of every counter after all operations.

Write a function:

    vector<int> solution(int N, vector<int> &A);

that, given an integer N and a non-empty zero-indexed array A consisting of M integers, returns a sequence of integers representing the values of the counters.

The sequence should be returned as:

        a structure Results (in C), or
        a vector of integers (in C++), or
        a record Results (in Pascal), or
        an array of integers (in any other programming language).

For example, given:

    A[0] = 3
    A[1] = 4
    A[2] = 4
    A[3] = 6
    A[4] = 1
    A[5] = 4
    A[6] = 4

the function should return [3, 2, 2, 4, 2], as explained above.

Assume that:

        N and M are integers within the range [1..100,000];
        each element of array A is an integer within the range [1..N + 1].

Complexity:

        expected worst-case time complexity is O(N+M);
        expected worst-case space complexity is O(N), beyond input storage (not counting the storage required for input arguments).

elements of input arrays can be modified.
*/
/*
//no
#include <vector>

//yes


using namespace std;
vector<int> solutionMaxCounters(int N, vector<int> &A)
{
	// write your code in C++11
	long max = 0;
	long current = 0;
	vector<int> result(N, 0);
	for (size_t index = 0; index < A.size(); ++index)
	{
		if (A[index] < N + 1)
		{
			if (result[A[index] - 1] <= max)
				result[A[index] - 1] = max;
			++result[A[index] - 1];
			if (result[A[index] - 1] > current)
				current = result[A[index] - 1];
		}
		else
		{
			max = current;
		}
	}
	for (size_t index = 0; index < result.size(); ++index)
	{
		if (result[index] < max)
			result[index] = max;
	}
	return std::move(result);
}

void Lesson2_MaxCounters()
{
	vector<int> A1 = { 3, 4, 4, 6, 1, 4, 4 };
	int N1 = 5;
	vector<int> R1 = solutionMaxCounters(5, A1);
	for (auto it = R1.cbegin(); it != R1.cend(); ++it)
		std::cout << *it << " " ;
	std::cout << std::endl;
}
*/

//--------------------------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////////////////////////
//	Lesson 5
////////////////////////////////////////////////////////////////////////////////////////////////////

//Nesting
/*
A string S consisting of N characters is called properly nested if:

S is empty;
S has the form "(U)" where U is a properly nested string;
S has the form "VW" where V and W are properly nested strings.

For example, string "(()(())())" is properly nested but string "())" isn't.

Write a function :

int solution(string &S);

that, given a string S consisting of N characters, returns 1 if string S is properly nested and 0 otherwise.

For example, given S = "(()(())())", the function should return 1 and given S = "())", the function should return 0, as explained above.

Assume that :

N is an integer within the range[0..1, 000, 000];
string S consists only of the characters "(" and / or ")".

Complexity:

expected worst - case time complexity is O(N);
expected worst - case space complexity is O(1) (not counting the storage required for input arguments).
*/
/*
int solution(std::string &S)
{
	using namespace std;
	size_t stringLength = S.length();

	if (stringLength % 2 != 0)
		return 0;

	int numOfPara = 0;
	for (size_t index = 0; index < stringLength; ++index)
	{
		if (S.c_str()[index] == '(')
			++numOfPara;
		else
		{
			--numOfPara;
			if (numOfPara < 0)
				// the case more ')' than '('
				return 0;
		}
	}

	if (numOfPara == 0)
		return 1;
	else
		// the case more '(' than ')'
		return 0;
}

void Lesson5_NestingTest()
{
	using namespace std;
	std::cout << string(__FUNCTION__) << std::endl;
	string testString_1 = "((()()))";
	std::cout << "Test string 1: " << testString_1 << std::endl;
	std::cout << "Test result: " << solution(testString_1) << std::endl;;
	string testString_2 = "(()(())())";
	std::cout << "Test string 1: " << testString_2 << std::endl;
	std::cout << "Test result: " << solution(testString_2) << std::endl;;
	string testString_3 = "())";
	std::cout << "Test string 1: " << testString_3 << std::endl;
	std::cout << "Test result: " << solution(testString_3) << std::endl;;
}
*/

//--------------------------------------------------------------------------------------------------

//StoneWall
/*
int solutionStoneWall(std::vector<int> &H)
{
	std::stack<int> brickHeight;
	int currentBrickTotalHeight = 0;
	size_t numberofBricks = 0;
	for (auto itHeight = H.cbegin(); itHeight != H.cend(); ++itHeight)
	{
		int currentWallHeight = *itHeight;
		if (brickHeight.size() == 0)
		{
			if (currentWallHeight > 0)
				brickHeight.push(currentWallHeight);
		}
		else if (currentWallHeight > currentBrickTotalHeight)
		{
			int newBrickHeight = currentWallHeight - currentBrickTotalHeight;
			if (newBrickHeight > 0)
				brickHeight.push(newBrickHeight);
		}
		else if (currentWallHeight < currentBrickTotalHeight)
		{
			while (currentBrickTotalHeight > currentWallHeight)
			{
				int topBrickHeight = brickHeight.top();
				currentBrickTotalHeight -= topBrickHeight;
				brickHeight.pop();
				++numberofBricks;
			}
			int newBrickHeight = currentWallHeight - currentBrickTotalHeight;
			if (newBrickHeight > 0)
				brickHeight.push(newBrickHeight);
		}
		currentBrickTotalHeight = currentWallHeight;
	}
	while (brickHeight.size() > 0)
	{
		brickHeight.pop();
		++numberofBricks;
	}

	return numberofBricks;

}

void Lesson5_StoneWallTest()
{
	std::cout << std::string(__FUNCTION__) << std::endl;

	std::vector<int> testArray1 = { 8, 8, 5, 7, 9, 8, 7, 4, 8 };
	std::cout << "Test vector 1: ";
	std::for_each(testArray1.cbegin(), testArray1.cend(), [](int number) { std::cout << number << " "; });
	std::cout << std::endl;
	std::cout << "Result: " << solutionStoneWall(testArray1) << std::endl;


	std::vector<int> testArray2 = { 8, 8, 8, 8, 8, 8 };
	std::cout << "Test vector 2: ";
	std::for_each(testArray2.cbegin(), testArray2.cend(), [](int number) { std::cout << number << " "; });
	std::cout << std::endl;
	std::cout << "Result: " << solutionStoneWall(testArray2) << std::endl;

	std::vector<int> testArray3 = { 0, 0, 0, 0, 0, 0 };
	std::cout << "Test vector 2: ";
	std::for_each(testArray3.cbegin(), testArray3.cend(), [](int number) { std::cout << number << " "; });
	std::cout << std::endl;
	std::cout << "Result: " << solutionStoneWall(testArray3) << std::endl;

	std::vector<int> testArray4 = { 1, 2, 3, 4, 5, 6 };
	std::cout << "Test vector 4: ";
	std::for_each(testArray4.cbegin(), testArray4.cend(), [](int number) { std::cout << number << " "; });
	std::cout << std::endl;
	std::cout << "Result: " << solutionStoneWall(testArray4) << std::endl;
}

*/

//--------------------------------------------------------------------------------------------------

// Brackets
/*
//not
#include <string>

//yes
#include <stack>
using namespace std;

int solution(string &S)
{
	write your code in C++11
		stack<char> brackets;
	for (auto element = S.cbegin(); element != S.cend(); ++element)
	{
		bool isPop = false;
		if (*element == '(' || *element == '{' || *element == '[')
		{
			brackets.push(*element);
		}
		else
		{
			if (brackets.size() > 0)
			{
				if (*element == ')')
				{
					if (brackets.top() != '(')
						return 0;
				}
				else if (*element == '}')
				{
					if (brackets.top() != '{')
						return 0;
				}
				else if (*element == ']')
				{
					if (brackets.top() != '[')
						return 0;
				}
				brackets.pop();
			}
			else
				return 0;
		}
	};

	if (brackets.size() > 0)
		return 0;
	else
		return 1;

}

void Lesson5_BracketsTest()
{
	std::string test1 = "{[()()]}";
	std::cout << test1 << " : " << solution(test1) << std::endl;

	std::string test2 = "([)()]";
	std::cout << test2 << " : " << solution(test2) << std::endl;

	std::string test3 = "((())";
	std::cout << test3 << " : " << solution(test3) << std::endl;

	std::string test4 = "((())))";
	std::cout << test4 << " : " << solution(test4) << std::endl;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
*/

//--------------------------------------------------------------------------------------------------

// Fish
/*
//not
#include <vector>

//yes
#include <stack>

using namespace std;
int solutionFish(vector<int> &A, vector<int> &B)
{
	// write your code in C++11
	if (A.size() != B.size())
		throw std::runtime_error("The length of vector A and B should be the same.");
	int numberOfFish = A.size();
	stack<int> moveUp, moveDown;
	for (size_t indexFish = 0; indexFish < B.size(); ++indexFish)
	{
		if (B[indexFish] == 1)
		{
			moveUp.push(A[indexFish]);
		}
		else
		{
			while (moveUp.size() > 0)
			{
				--numberOfFish;
				if (A[indexFish] > moveUp.top())
				{
					moveUp.pop();
				}
				else
				{
					break;
				}
			}
		}
	}
	return numberOfFish;

}


void Lesson5_FishTest()
{
	vector<int> A1 = { 4, 3, 2, 1, 5 };
	vector<int> B1 = { 0, 1, 0, 0, 0 };
	std::cout << "A1 : ";
	for (auto it = A1.cbegin(); it < A1.cend(); ++it)
	{
		std::cout << *it;
	}
	std::cout << std::endl;

	std::cout << "B1 : ";
	for (auto it = B1.cbegin(); it < B1.cend(); ++it)
	{
		std::cout << *it;
	}
	std::cout << std::endl;
	std::cout << "result: " << solutionFish(A1, B1) << std::endl;


	vector<int> A2 = { 5, 4, 3, 2, 1 };
	vector<int> B2 = { 1, 0, 0, 0, 0 };
	std::cout << "A2 : ";
	for (auto it = A2.cbegin(); it < A2.cend(); ++it)
	{
		std::cout << *it;
	}
	std::cout << std::endl;

	std::cout << "B2 : ";
	for (auto it = B2.cbegin(); it < B2.cend(); ++it)
	{
		std::cout << *it;
	}
	std::cout << std::endl;
	std::cout << "result: " << solutionFish(A2, B2) << std::endl;


	vector<int> A3 = { 1, 2, 3, 4, 5 };
	vector<int> B3 = { 1, 1, 1, 1, 0 };
	std::cout << "A3 : ";
	for (auto it = A3.cbegin(); it < A3.cend(); ++it)
	{
		std::cout << *it;
	}
	std::cout << std::endl;

	std::cout << "B3 : ";
	for (auto it = B3.cbegin(); it < B3.cend(); ++it)
	{
		std::cout << *it;
	}
	std::cout << std::endl;
	std::cout << "result: " << solutionFish(A3, B3) << std::endl;
}
*/

//--------------------------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////////////////////////
//	Lesson 3
// https://codility.com/programmers/lessons/3
////////////////////////////////////////////////////////////////////////////////////////////////////

//CountDiv
/*
Write a function:

    int solution(int A, int B, int K);

that, given three integers A, B and K, returns the number of integers within the range [A..B] that are divisible by K, i.e.:

    { i : A ≤ i ≤ B, i mod K = 0 }

For example, for A = 6, B = 11 and K = 2, your function should return 3, because there are three numbers divisible by 2 within the range [6..11], namely 6, 8 and 10.

Assume that:

        A and B are integers within the range [0..2,000,000,000];
        K is an integer within the range [1..2,000,000,000];
        A ≤ B.

Complexity:

        expected worst-case time complexity is O(1);
        expected worst-case space complexity is O(1).

*/
/*
//no

//yes

int solutionCountDiv(int A, int B, int K)
{
	// write your code in C++11

	//version1
	//int counter = 0;
	//for (int it = A; it <= B; ++it)
	//{
	//	if (it%K == 0)
	//		++counter;
	//}
	//return counter;

	//version 2
	return B / K - A / K + (A%K == 0 ? 1 : 0);
}

void Lesson3_CountDiv()
{
	int A1 = 6, B1 = 11, K1 = 2;
	std::cout << solutionCountDiv(A1, B1, K1) << std::endl;
}
*/

//--------------------------------------------------------------------------------------------------

//PassingCars
/*
A non-empty zero-indexed array A consisting of N integers is given. The consecutive elements of array A represent consecutive cars on a road.

Array A contains only 0s and/or 1s:

        0 represents a car traveling east,
        1 represents a car traveling west.

The goal is to count passing cars. We say that a pair of cars (P, Q), where 0 ≤ P < Q < N, is passing when P is traveling to the east and Q is traveling to the west.

For example, consider array A such that:

  A[0] = 0
  A[1] = 1
  A[2] = 0
  A[3] = 1
  A[4] = 1

We have five pairs of passing cars: (0, 1), (0, 3), (0, 4), (2, 3), (2, 4).

Write a function:

    int solution(int A[], int N);

that, given a non-empty zero-indexed array A of N integers, returns the number of pairs of passing cars.

The function should return −1 if the number of pairs of passing cars exceeds 1,000,000,000.

For example, given:

  A[0] = 0
  A[1] = 1
  A[2] = 0
  A[3] = 1
  A[4] = 1

the function should return 5, as explained above.

Assume that:

        N is an integer within the range [1..100,000];
        each element of array A is an integer that can have one of the following values: 0, 1.

Complexity:

        expected worst-case time complexity is O(N);
        expected worst-case space complexity is O(1), beyond input storage (not counting the storage required for input arguments).

Elements of input arrays can be modified.
*/
/*
//no
#include <vector>

//yes

using namespace std;
int solution(vector<int> &A)
{
	// write your code in C++11
	return 0;
}

void testSolution()
{

}
*/

//--------------------------------------------------------------------------------------------------

//MinAvgTwoSlice
/*
A non-empty zero-indexed array A consisting of N integers is given. A pair of integers (P, Q), such that 0 ≤ P < Q < N, is called a slice of array A (notice that the slice contains at least two elements). The average of a slice (P, Q) is the sum of A[P] + A[P + 1] + ... + A[Q] divided by the length of the slice. To be precise, the average equals (A[P] + A[P + 1] + ... + A[Q]) / (Q − P + 1).

For example, array A such that:

    A[0] = 4
    A[1] = 2
    A[2] = 2
    A[3] = 5
    A[4] = 1
    A[5] = 5
    A[6] = 8

contains the following example slices:

        slice (1, 2), whose average is (2 + 2) / 2 = 2;
        slice (3, 4), whose average is (5 + 1) / 2 = 3;
        slice (1, 4), whose average is (2 + 2 + 5 + 1) / 4 = 2.5.

The goal is to find the starting position of a slice whose average is minimal.

Write a function:

    int solution(int A[], int N);

that, given a non-empty zero-indexed array A consisting of N integers, returns the starting position of the slice with the minimal average. If there is more than one slice with a minimal average, you should return the smallest starting position of such a slice.

For example, given array A such that:

    A[0] = 4
    A[1] = 2
    A[2] = 2
    A[3] = 5
    A[4] = 1
    A[5] = 5
    A[6] = 8

the function should return 1, as explained above.

Assume that:

        N is an integer within the range [2..100,000];
        each element of array A is an integer within the range [−10,000..10,000].

Complexity:

        expected worst-case time complexity is O(N);
        expected worst-case space complexity is O(N), beyond input storage (not counting the storage required for input arguments).

Elements of input arrays can be modified.

*/
/*
//no
#include <vector>

//yes
#include <algorithm>
#include <numeric>

using namespace std;
int solution(vector<int> &A)
{
	int currentMinimunPosition = 0;
	double minAverage = std::numeric_limits<int>::max();
	for (size_t index = 0; index < A.size() - 2; ++index)
	{
		double average2 = A[index] + A[index + 1];
		double average3 = average2 + A[index + 2];
		double currentMin = average2 / 2.0 < average3 / 3.0 ? average2 / 2.0 : average3 / 3.0;
		if (currentMin < minAverage)
		{
			minAverage = currentMin;
			currentMinimunPosition = index;
		}
	}

	if ((A[A.size() - 1] + A[A.size() - 2]) / 2 < minAverage)
		currentMinimunPosition = A.size() - 2;
		

	return currentMinimunPosition;
}

void testSolution()
{
	std::vector<int> A1 = { 4, 2, 2, 5, 1, 5, 8};
	int R1 = solution(A1);
	PRINT_VECTOR(A1);
	PRINT_POD(R1);

	std::vector<int> A2 = { 2, 2, 2, 2, 2, 2, 2};
	int R2 = solution(A2);
	PRINT_VECTOR(A2);
	PRINT_POD(R2);

	std::vector<int> A3 = { 1, 1};
	int R3 = solution(A3);
	PRINT_VECTOR(A3);
	PRINT_POD(R3);

	std::vector<int> A4(100000, 2);
	A4[10] = 0;
	int R4 = solution(A4);
	PRINT_VARIABLE(std::vector<int> A4(100000, 2)); std::cout << std::endl;
	PRINT_POD(R4);

	std::vector<int> A5(100000, 2);
	A5[10] = 0;
	A5[11] = 0;
	int R5 = solution(A5);
	PRINT_VARIABLE(std::vector<int> A5(100000, 2)); std::cout << std::endl;
	PRINT_POD(R5);


	std::vector<int> A6 = {-10000, -10000, -10000};
	int R6 = solution(A6);
	PRINT_VARIABLE(std::vector<int> A6(100000, 2)); std::cout << std::endl;
	PRINT_POD(R6);


	std::vector<int> A7;
	A7.reserve(100);
	for (auto index = 0; index < 100; ++index)
	{
		if (index < 50)
			A7.emplace_back(index);
		else
			A7.emplace_back(A7[index - 1] + (50 - index));
	}
	int R7 = solution(A7);
	PRINT_VECTOR(A7);
	PRINT_POD(R7);
	
	// 90%
	//https://codility.com/demo/results/demoXBR627-KCN/
	// 100%
	// https://codility.com/demo/results/demo7ZUM68-NQB/
	// 100%
	//http://codility-lessons.blogspot.com/2014/07/lesson-3-minavgtwoslice.html
}
*/

//--------------------------------------------------------------------------------------------------

//GenomicRangeQuery
/*
A DNA sequence can be represented as a string consisting of the letters A, C, G and T, which correspond to the types of successive nucleotides in the sequence. Each nucleotide has an impact factor, which is an integer. Nucleotides of types A, C, G and T have impact factors of 1, 2, 3 and 4, respectively. You are going to answer several queries of the form: What is the minimal impact factor of nucleotides contained in a particular part of the given DNA sequence?

The DNA sequence is given as a non-empty string S = S[0]S[1]...S[N-1] consisting of N characters. There are M queries, which are given in non-empty arrays P and Q, each consisting of M integers. The K-th query (0 ≤ K < M) requires you to find the minimal impact factor of nucleotides contained in the DNA sequence between positions P[K] and Q[K] (inclusive).

For example, consider string S = CAGCCTA and arrays P, Q such that:

    P[0] = 2    Q[0] = 4
    P[1] = 5    Q[1] = 5
    P[2] = 0    Q[2] = 6

The answers to these M = 3 queries are as follows:

        The part of the DNA between positions 2 and 4 contains nucleotides G and C (twice), whose impact factors are 3 and 2 respectively, so the answer is 2.
        The part between positions 5 and 5 contains a single nucleotide T, whose impact factor is 4, so the answer is 4.
        The part between positions 0 and 6 (the whole string) contains all nucleotides, in particular nucleotide A whose impact factor is 1, so the answer is 1.

Assume that the following declarations are given:

    struct Results { int * A; int M; };

Write a function:

    struct Results solution(char *S, int P[], int Q[], int M);

that, given a non-empty zero-indexed string S consisting of N characters and two non-empty zero-indexed arrays P and Q consisting of M integers, returns an array consisting of M integers specifying the consecutive answers to all queries.

The sequence should be returned as:

        a Results structure (in C), or
        a vector of integers (in C++), or
        a Results record (in Pascal), or
        an array of integers (in any other programming language).

For example, given the string S = CAGCCTA and arrays P, Q such that:

    P[0] = 2    Q[0] = 4
    P[1] = 5    Q[1] = 5
    P[2] = 0    Q[2] = 6

the function should return the values [2, 4, 1], as explained above.

Assume that:

        N is an integer within the range [1..100,000];
        M is an integer within the range [1..50,000];
        each element of arrays P, Q is an integer within the range [0..N − 1];
        P[K] ≤ Q[K], where 0 ≤ K < M;
        string S consists only of upper-case English letters A, C, G, T.

Complexity:

        expected worst-case time complexity is O(N+M);
        expected worst-case space complexity is O(N), beyond input storage (not counting the storage required for input arguments).

Elements of input arrays can be modified.
*/
/*
//no
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>

//yes
#include <unordered_map>


using namespace std;
vector<int> solution(string &S, vector<int> &P, vector<int> &Q)
{
	// write your code in C++11
	unordered_map<char, char> nucleotides = { { 'A', 1 }, { 'C', 2 }, { 'G', 3 }, {'T', 4} };

	vector<vector<int>> nucleotidesPosition(4, vector<int>(S.length(), -1));
	nucleotidesPosition[nucleotides[S.back()] - 1][S.length() - 1] = S.length() - 1;
	for (int index = S.length() - 2; index > -1; --index)
	{
		for (unsigned char i = 0; i < nucleotidesPosition.size(); ++i)
		{
			nucleotidesPosition[i][index] = nucleotidesPosition[i][index + 1];
		}
		nucleotidesPosition[nucleotides[S[index]] - 1][index] =  index;
	}

	size_t queryLength = P.size();
	vector<int> result(queryLength, -1);
	for (size_t index = 0; index < queryLength; ++index)
	{
		if (nucleotidesPosition[nucleotides['A'] - 1][P[index]] != -1 && nucleotidesPosition[nucleotides['A'] - 1][P[index]] <= Q[index])
			result[index] = 1;
		else if (nucleotidesPosition[nucleotides['C'] - 1][P[index]] != -1 && nucleotidesPosition[nucleotides['C'] - 1][P[index]] <= Q[index])
			result[index] = 2;
		else if (nucleotidesPosition[nucleotides['G'] - 1][P[index]] != -1 && nucleotidesPosition[nucleotides['G'] - 1][P[index]] <= Q[index])
			result[index] = 3;
		else if (nucleotidesPosition[nucleotides['T'] - 1][P[index]] != -1 && nucleotidesPosition[nucleotides['T'] - 1][P[index]] <= Q[index])
			result[index] = 4;
	}

	return result;
}

std::string generateDNASequence(size_t length)
{
	std::string dnaSequence(length, 'A');
	srand(time(NULL));
	for (size_t i = 0; i < length; ++i)
	{
		unsigned char a = rand() % 4 + 1;
		switch (a)
		{
			case 2:
				dnaSequence[i] = 'C';
				break;
			case 3:
				dnaSequence[i] = 'G';
				break;
			case 4:
				dnaSequence[i] = 'T';
				break;
			default:
				break;
		}
	}
	return dnaSequence;
}


void testSolution()
{
	std::string S1 = "CAGCCTA";
	vector<int> P1 = { 2, 5, 0 };
	vector<int> Q1 = { 4, 5, 6 };
	vector<int> R1 = solution(S1, P1, Q1);
	PRINT_POD(S1);
	PRINT_VECTOR(P1);
	PRINT_VECTOR(Q1);
	PRINT_VECTOR(R1);

	std::string S2(100000, 'T');
	S2[100] = 'A';
	S2[200] = 'C';
	S2[300] = 'G';
	vector<int> P2 = { 90, 200, 300, 0, 0};
	vector<int> Q2 = { 110, 201, 99999, 80, 99999};
	vector<int> R2 = solution(S2, P2, Q2);
	PRINT_VECTOR(P2);
	PRINT_VECTOR(Q2);
	std::cout << "Expected : 1, 2, 3, 4, 1" << std::endl;
	PRINT_VECTOR(R2);

	std::string S3 = "A";
	vector<int> P3 = { 0 };
	vector<int> Q3 = { 0 };
	vector<int> R3 = solution(S3, P3, Q3);
	PRINT_POD(S3);
	PRINT_VECTOR(P3);
	PRINT_VECTOR(Q3);
	PRINT_VECTOR(R3);

}
*/

//--------------------------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////////////////////////
//	Lesson 4
// https://codility.com/programmers/lessons/4
////////////////////////////////////////////////////////////////////////////////////////////////////

// MaxProductOfThree
/*
A non-empty zero-indexed array A consisting of N integers is given. The product of triplet (P, Q, R) equates to A[P] * A[Q] * A[R] (0 ≤ P < Q < R < N).

For example, array A such that:

  A[0] = -3
  A[1] = 1
  A[2] = 2
  A[3] = -2
  A[4] = 5
  A[5] = 6

contains the following example triplets:

        (0, 1, 2), product is −3 * 1 * 2 = −6
        (1, 2, 4), product is 1 * 2 * 5 = 10
        (2, 4, 5), product is 2 * 5 * 6 = 60

Your goal is to find the maximal product of any triplet.

Write a function:

    int solution(int A[], int N);

that, given a non-empty zero-indexed array A, returns the value of the maximal product of any triplet.

For example, given array A such that:

  A[0] = -3
  A[1] = 1
  A[2] = 2
  A[3] = -2
  A[4] = 5
  A[5] = 6

the function should return 60, as the product of triplet (2, 4, 5) is maximal.

Assume that:

        N is an integer within the range [3..100,000];
        each element of array A is an integer within the range [−1,000..1,000].

Complexity:

        expected worst-case time complexity is O(N*log(N));
        expected worst-case space complexity is O(1), beyond input storage (not counting the storage required for input arguments).

Elements of input arrays can be modified.
*/
/*
//not
#include <vector>

//yes
#include <algorithm>
#include <numeric>

using namespace std;
int solution(vector<int> & A)
{
	////solution 1
	////result: https://codility.com/demo/results/demoZZ464D-5XZ/ 
	//std::sort(A.begin(), A.end());
	//std::vector<int> maxThreeElements(A.cend() - 3, A.cend());
	//std::vector<int> minTwoElements(A.cbegin(), A.cend());

	//int productThreeMax = *(A.cend() - 1) * *(A.cend() - 2) * *(A.cend() - 3);

	//int productTwoMinOneMax = *(A.cbegin()) * *(A.cbegin() + 1) * *(A.cend() - 1);

	//return productThreeMax > productTwoMinOneMax ? productThreeMax : productTwoMinOneMax;

	//////////////////////////////////////////////////////////////////////////////////////////

	////solution 2
	////result: https://codility.com/demo/results/demoKDRUCF-7PG/ 
	unsigned char N = 3, M = 2;
	std::vector<int> maxNElements(N, std::numeric_limits<int>::min());
	std::vector<int> minMElements(M, std::numeric_limits<int>::max());

	for (auto it = A.cbegin(); it != A.cend(); ++it)
	{
		if (*it > maxNElements[2])
		{
			maxNElements[0] = maxNElements[1];
			maxNElements[1] = maxNElements[2];
			maxNElements[2] = *it;
		} 
		else if (*it > maxNElements[1])
		{
			maxNElements[0] = maxNElements[1];
			maxNElements[1] = *it;
		}
		else if (*it > maxNElements[0])
		{
			maxNElements[0] = *it;
		}

		//for (int i = maxNElements.size() - 1; i > -1; --i)
		//	if (*it > maxNElements[i])
		//	{
		//		for (int j = 0; j < i; ++j)
		//			maxNElements[j] = maxNElements[j + 1];
		//		maxNElements[i] = *it;
		//		break;
		//	}

		if (*it < minMElements[0])
		{
			minMElements[1] = minMElements[0];
			minMElements[0] = *it;
		}
		else if (*it < minMElements[1])
		{
			minMElements[1] = *it;
		}

		//for (int i = 0; i < minMElements.size(); ++i)
		//	if (*it < minMElements[i])
		//	{
		//		for (int j = minMElements.size() - 1; j > 0; --j)
		//			minMElements[j] = minMElements[j - 1];
		//		minMElements[i] = *it;
		//		break;
		//	}

	}

	int productThreeMax = maxNElements[0] * maxNElements[1] * maxNElements[2];
	int productTwoMinOneMax = minMElements[0] * minMElements[1] * maxNElements[2];

	int maxProduct = productThreeMax;
	if (productTwoMinOneMax > productThreeMax)
		maxProduct = productTwoMinOneMax;

	return maxProduct;

	//////////////////////////////////////////////////////////////////////////////////////////

	////solution 3
	////result: https://codility.com/demo/results/demoWK5NQR-KC5/ 
	//unsigned char N = 3, M = 2;
	//std::vector<int> maxNElements(N + 1, std::numeric_limits<int>::min());
	//std::vector<int> minMElements(M + 1, std::numeric_limits<int>::max());

	//for (auto it = A.cbegin(); it != A.cend(); ++it)
	//{
	//	*maxNElements.begin() = *it;
	//	for (auto itMaxN = maxNElements.begin(); itMaxN < maxNElements.end() - 1; ++itMaxN)
	//	{
	//		if (*itMaxN > *(itMaxN + 1))
	//			std::swap(*itMaxN, *(itMaxN + 1));
	//		else
	//			break;
	//	}

	//	*minMElements.begin() = *it;
	//	for (auto itMinM = minMElements.begin(); itMinM < minMElements.end() - 1; ++itMinM)
	//		if (*itMinM < *(itMinM + 1))
	//			std::swap(*itMinM, *(itMinM + 1));
	//		else
	//			break;
	//}

	//int productThreeMax = maxNElements[1] * maxNElements[2] * maxNElements[3];
	//int productTwoMinOneMax = minMElements[1] * minMElements[2] * maxNElements[3];

	//int maxProduct = productThreeMax;
	//if (productTwoMinOneMax > productThreeMax)
	//	maxProduct = productTwoMinOneMax;

	//return maxProduct;
}

void testSolution()
{
	std::vector<int> A1 = { -3, 1, 2, -2, 5, 6 };
	int R1 = solution(A1);
	PRINT_VECTOR(A1);
	PRINT_POD(R1);

	std::vector<int> A2 = { -1000, -999, -1, 1, 1000 };
	int R2 = solution(A2);
	PRINT_VECTOR(A2);
	PRINT_POD(R2);

	std::vector<int> A3 = { -2, 0, 2, 1, -1 };
	int R3 = solution(A3);
	PRINT_VECTOR(A3);
	PRINT_POD(R3);

	std::vector<int> A4 = { 0, 2, 1, -1 };
	int R4 = solution(A4);
	PRINT_VECTOR(A4);
	PRINT_POD(R4);
}
*/

//--------------------------------------------------------------------------------------------------

//Distinct
/*
Write a function

    int solution(int A[], int N);

that, given a zero-indexed array A consisting of N integers, returns the number of distinct values in array A.

Assume that:

        N is an integer within the range [0..100,000];
        each element of array A is an integer within the range [−1,000,000..1,000,000].

For example, given array A consisting of six elements such that:

    A[0] = 2    A[1] = 1    A[2] = 1
    A[3] = 2    A[4] = 3    A[5] = 1

the function should return 3, because there are 3 distinct values appearing in array A, namely 1, 2 and 3.

Complexity:

        expected worst-case time complexity is O(N*log(N));
        expected worst-case space complexity is O(N), beyond input storage (not counting the storage required for input arguments).

Elements of input arrays can be modified.
*/
/*
//no
#include <vector>

//yes
#include <algorithm>

int solution(std::vector<int> &A)
{
	//result: https://codility.com/demo/results/demoARCCNF-SMB/
	if (A.size() == 0) return 0;
	std::sort(A.begin(), A.end());
	size_t counter = 1;
	for (auto it = A.cbegin() + 1; it != A.cend(); ++it)
	{
		if (*it != *(it - 1))
			++counter;
	}
	return counter;
}

void testSolution()
{
	std::vector<int> A1 = { 2, 1, 1, 2, 3, 1 };
	int R1 = solution(A1);
	PRINT_VECTOR(A1);
	PRINT_POD(R1);

	std::vector<int> A2 = {};
	int R2 = solution(A2);
	PRINT_VECTOR(A2);
	PRINT_POD(R2);

	std::vector<int> A3(100000, -1000000);
	std::fill(A3.begin() + 10000, A3.begin() + 20000, 1000000);
	std::fill(A3.begin() + 50000, A3.begin() + 60000, 0);
	int R3 = solution(A3);
	PRINT_POD(R3);

}
*/

//--------------------------------------------------------------------------------------------------

//NumberOfDiscIntersections
/*
We draw N discs on a plane. The discs are numbered from 0 to N − 1. A zero-indexed array A of N non-negative integers, specifying the radiuses of the discs, is given. The J-th disc is drawn with its center at (J, 0) and radius A[J].

We say that the J-th disc and K-th disc intersect if J ≠ K and the J-th and K-th discs have at least one common point (assuming that the discs contain their borders).

The figure below shows discs drawn for N = 6 and A as follows:

  A[0] = 1
  A[1] = 5
  A[2] = 2
  A[3] = 1
  A[4] = 4
  A[5] = 0

There are eleven (unordered) pairs of discs that intersect, namely:

        discs 1 and 4 intersect, and both intersect with all the other discs;
        disc 2 also intersects with discs 0 and 3.

Write a function:

    int solution(int A[], int N);

that, given an array A describing N discs as explained above, returns the number of (unordered) pairs of intersecting discs. The function should return −1 if the number of intersecting pairs exceeds 10,000,000.

Given array A shown above, the function should return 11, as explained above.

Assume that:

        N is an integer within the range [0..100,000];
        each element of array A is an integer within the range [0..2,147,483,647].

Complexity:

        expected worst-case time complexity is O(N*log(N));
        expected worst-case space complexity is O(N), beyond input storage (not counting the storage required for input arguments).

Elements of input arrays can be modified.
*/
/*
// no
#include <vector>

// yes
#include <algorithm>
#include <functional>

int solution(std::vector<int> &A)
{
	//result: https://codility.com/demo/results/demoNEMX4H-2PP/
	std::vector<long> rightBound(A.cbegin(), A.cend());
	std::vector<long> leftBound(A.cbegin(), A.cend());

	for(auto itRadius = leftBound.begin(); itRadius != leftBound.end(); ++itRadius)
	{
		*itRadius = std::distance(leftBound.begin(), itRadius) - *itRadius;
	};

	for(auto itRadius = rightBound.begin(); itRadius != rightBound.end(); ++itRadius)
	{
		*itRadius = std::distance(rightBound.begin(), itRadius) + *itRadius;
	};

	std::sort(rightBound.begin(), rightBound.end());
	std::sort(leftBound.begin(), leftBound.end());

	size_t distinctNumber = 0;
	size_t indexLeftBound = 0;
	for (size_t indexRightBound = 0; indexRightBound < rightBound.size(); ++indexRightBound)
	{
		while (indexLeftBound < leftBound.size() && leftBound[indexLeftBound] <= rightBound[indexRightBound])
			++indexLeftBound;

		distinctNumber += (indexLeftBound -indexRightBound - 1);
	}
	if (distinctNumber > 10000000)
		return -1;
	return static_cast<int>(distinctNumber);

}

void testSolution()
{
	std::vector<int> A1 = { 1, 5, 2, 1, 4, 0 };
	int R1 = solution(A1);
	PRINT_VECTOR(A1);
	PRINT_POD(R1);
}
*/

////////////////////////////////////////////////////////////////////////////////////////////////////
void test()
{
	testSolution();
}