#include <vector>
#include <iostream>
#include <unordered_map>

#include <boost\thread\thread.hpp>
#include <boost\thread\mutex.hpp>
#include <boost\thread\future.hpp>

#include "funcs.h"


namespace TestFuncs{
	///////////////////////////////////////////////////////////////////
	namespace {
		void call_from_thread(int tid) {
			std::cout << "Launched by thread " << tid << std::endl;
		}
	}

	static const int num_threads = 10;

	void simple_thread_example() {
		boost::thread t[num_threads];

		//Launch a group of threads
		for (int i = 0; i < num_threads; ++i) {
			t[i] = boost::thread(call_from_thread, i);
		}

		std::cout << "Launched from the main\n";

		//Join the threads with the main thread
		for (int i = 0; i < num_threads; ++i) {
			t[i].join();
		}
	}

///////////////////////////////////////////////////////////////////

	int accum;

	boost::mutex accum_mutex;

	void square(int x) {
		accum_mutex.lock();
		accum += x * x;
		accum_mutex.unlock();
		std::cout << "accum (" << x << "): " << accum << std::endl;
		
	}

	long sum_square(int max_num){
		accum = 0;
		std::vector<boost::thread> ths;
		for (int i = 1; i <= max_num; i++) {
			ths.push_back(boost::thread(&square, i));
		}

		for (auto ths_it = ths.begin(); ths_it != ths.end(); ++ths_it) {
			ths_it->join();
		}

		return accum;
	}
///////////////////////////////////////////////////////////////////

	namespace {
		void factorial(int x) {
			long long result = 1;
			for (int counter = 1; counter < 100000; ++counter){
				for (int i = 1; i <= x; ++i) {
					result = result * i;
				}
			}
			std::cout << "factorial of " << x << ": " << result << std::endl;
		}
	}

	void multiple_factorial(int number, int times) {
		std::vector<boost::thread> ths;
		for (int i = 1; i <= times; i++) {
			ths.push_back(boost::thread(&factorial, number));
		}

		for (auto ths_it = ths.begin(); ths_it != ths.end(); ++ths_it) {
			ths_it->join();
		}
	}
///////////////////////////////////////////////////////////////////



} //namespace TestFuncs