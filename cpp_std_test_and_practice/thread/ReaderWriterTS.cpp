#include <unordered_map>
#include <map>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <memory>
#include <boost\thread\thread.hpp>
#include <boost\lexical_cast.hpp>
#include <boost\asio.hpp>
#include <Windows.h>

#include "ReaderWriter.h"

#include "ReaderWriterTS.h"


using namespace boost::unit_test_framework;

namespace CPP_STD_TEST_AND_PRACTIVE_TS {

	void WriteData() {
		::srand(::time(NULL));

		int num_vector_size = 300;

		std::map<int, std::shared_ptr<ReaderWriter::Writer>> writers;
		for (auto id = 0; id < num_vector_size; ++id) {
			std::shared_ptr<ReaderWriter::Writer> p_writer = std::make_shared<ReaderWriter::Writer>(boost::lexical_cast<std::string>(id));
			writers.insert(std::pair<int, std::shared_ptr<ReaderWriter::Writer> >(id, p_writer));
		}

		//std::cout << "======================== initialize SharedData ========================" << std::endl;

		for (size_t i = 0; i < 1000; ++i){
			for (size_t writer_counter = 0; writer_counter < writers.size(); ++writer_counter) {
				double value = ::rand() % 10 + 100 * (i + 1);
				//std::cout << "Write [" << writer_counter << "]:" << value << std::endl;
				writers[writer_counter]->write(value);
			}
			Sleep(75); 
		}
	}

	void WriteDataWrapper() {
		boost::thread trd(WriteData);
	}
//
//	void ReaderWriterTS::first_test() {
//
//		::srand(::time(NULL));
//
//		int num_vector_size = 100;
//
//		std::map<int, std::shared_ptr<ReaderWriter::Writer>> writers;
//		for (auto id = 0; id < num_vector_size; ++id) {
//			std::shared_ptr<ReaderWriter::Writer> p_writer = std::make_shared<ReaderWriter::Writer>(id);
//			writers.insert(std::pair<int, std::shared_ptr<ReaderWriter::Writer>>(id, p_writer));
//		}
//
//		std::map<int, ReaderWriter::Reader*> readers;
//		for (auto id = 0; id < num_vector_size; ++id) {
//			ReaderWriter::Reader* p_reader = new ReaderWriter::Reader(id);
//			readers.insert(std::pair<int, ReaderWriter::Reader*>(id, p_reader));
//		}
//		
//		std::cout << "number of system thread:" << boost::thread::hardware_concurrency() <<std::endl;
//
//		std::cout << "======================== initialize SharedData ========================" << std::endl;
//
//		std::shared_ptr<ReaderWriter::SharedData> p_shared_data = std::make_shared<ReaderWriter::SharedData>();
//		for (auto it_writer = writers.begin(); it_writer != writers.end(); ++it_writer)
//			it_writer->second->write(p_shared_data);
//
//		std::cout << "======================== start read/write async ========================" << std::endl;
//
//		boost::thread_group o_thread_group;
//		for (int counter = 0; counter < num_vector_size; ++counter) {
//			std::shared_ptr<ReaderWriter::Writer> p_writer = writers[counter];
//			boost::thread* writer_thread = new boost::thread(std::bind(&ReaderWriter::Writer::write, p_writer, p_shared_data, double(::rand() % 100 + 100)));
//			o_thread_group.add_thread(writer_thread);
//			boost::thread* reader_thread = new boost::thread(&ReaderWriter::Reader::read, readers[counter], std::cref(p_shared_data));
//			o_thread_group.add_thread(reader_thread);
//		}
//
//		o_thread_group.join_all();
//
//		for (auto id = 0; id < num_vector_size; ++id) {
//			delete readers[id];
//		}
//
//		BOOST_CHECK(true);
//	}
	void ReaderWriterTS::TestUpdateRouter() {
		std::cout << "Thread number: " << boost::thread::hardware_concurrency() << std::endl;
		WriteDataWrapper();

		ReaderWriter::CachePtr cache = std::make_shared<ReaderWriter::Cache>();
		for (size_t counter = 0; counter < 300; ++counter) {
			ReaderWriter::DataPtr data = std::make_shared<double>(0);
			std::string szChannel = boost::lexical_cast<std::string>(counter);
			(*cache)[szChannel] = data;
		}

		ReaderWriter::UpdateRouter router;
		for (size_t counter = 0; counter < 1000; ++counter) {
			std::cout << "new round:" << std::endl;
			if (!router.update(cache))
				std::cout << "data not ready" << std::endl;
			Sleep(123);
			for (auto it = cache->begin(); it != cache->end(); ++it) {
				std::cout <<"Read [" << it->first <<"]: " << *(it->second) << std::endl;
			}
		}
	}

	test_suite* ReaderWriterTS::suite()
	{
		test_suite* suite = BOOST_TEST_SUITE("ReaderWriterTS");
		//suite->add(BOOST_TEST_CASE(&first_test));
		suite->add(BOOST_TEST_CASE(&TestUpdateRouter));
		return suite;
	}
}