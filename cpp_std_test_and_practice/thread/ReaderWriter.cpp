#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <unordered_map>


#include <boost\thread\mutex.hpp>
#include <boost\thread\shared_mutex.hpp>
#include <boost\lexical_cast.hpp>

#include "ReaderWriter.h"


namespace ReaderWriter {

	class RandInit {
	public:
		int getIndexRnd() {
			return ::rand() % 10;
		}
		
		double getValueRnd() {
			return ::rand() % 100;
		}

		RandInit() {
			::srand(::time(NULL));
		}
	};

	static RandInit static_rand_initializer;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////
	class Writer::WriterImp {
	public:
		WriterImp(int id) : id_(id) {}
		void write(SharedData& shared_data) {
			double value = static_rand_initializer.getValueRnd();
			write(shared_data, value);
		}

		void write(SharedData& shared_data, double value) {
			shared_data.write(id_, value);
			std::cout << "Writer [" << id_ << "] - value: " << value << std::endl;
		}
	private:
		int id_;
	};

	void Writer::write(std::shared_ptr<SharedData> shared_data, double value) {
		writerImp_->write(*shared_data, value);
	}

	void Writer::write(std::shared_ptr<SharedData> shared_data) {
		writerImp_->write(*shared_data);
	}

	Writer::Writer(int id) {
		writerImp_ = new WriterImp(id);
	}

	Writer::~Writer() {
		if (writerImp_) delete writerImp_;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////

	class Reader::ReaderImp {
	public:
		ReaderImp(int id) : id_(id) {}
		void read(const SharedData& shared_data) {
			std::cout << "Reader [" << id_ << "] - value: " << shared_data.read(id_) << std::endl;
		}
	private:
		int id_;
	};

	void Reader::read(const std::shared_ptr<SharedData> shared_data) const {
		readerImp_->read(*shared_data);
	}

	Reader::Reader(int id) {
		readerImp_ = new ReaderImp(id);
	}

	Reader::~Reader() {
		if (readerImp_) delete readerImp_;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////
	class SharedData::SharedDataImp {
	public:
		double get(int index) const;
		void insert(int index, double value);
		void update(int index, double value);
		bool indexExists(int index) const {
			return !(cache_.find(index) == cache_.end());
		}
	private:
		mutable boost::shared_mutex mutex_;
		std::unordered_map<int, double> cache_;
	};

	double SharedData::SharedDataImp::get(int index) const {
		boost::shared_lock<boost::shared_mutex> lock(mutex_);
		if (!indexExists(index))
			throw std::runtime_error("can't find " + boost::lexical_cast<std::string>(index));
		else
			return cache_.at(index);
	}

	void SharedData::SharedDataImp::insert(int index, double value) {
		boost::unique_lock<boost::shared_mutex> lock(mutex_);
		cache_[index] = value;
	}

	void SharedData::SharedDataImp::update(int index, double value) {
		boost::unique_lock<boost::shared_mutex> lock(mutex_);
		cache_[index] = value;
	}

	SharedData::SharedData() {
		sharedDataImp_ = new SharedDataImp();
	}

	SharedData::~SharedData() {
		if (sharedDataImp_) delete sharedDataImp_;
	}

	double SharedData::read(int index) const {
		return sharedDataImp_->get(index);
	}

	void SharedData::write(int index, double value) {
		if (sharedDataImp_->indexExists(index))
			sharedDataImp_->update(index, value);
		else
			sharedDataImp_->insert(index, value);
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////

}