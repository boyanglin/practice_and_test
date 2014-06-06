#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <unordered_map>
#include <cmath>

#include <boost\thread\mutex.hpp>
#include <boost\thread\shared_mutex.hpp>
#include <boost\asio.hpp>
#include <boost\thread\thread.hpp>
#include <boost\thread\future.hpp>

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
	static SharedData sharedData;

	class SharedData::SharedDataImp {
	public:
		double get(std::string szChannelName) const;
		void insert(std::string szChannelName, double value);
		void update(std::string szChannelName, double value);
		bool indexExists(std::string szChannelName) const {
			return (cache_.find(szChannelName) != cache_.end());
		}
	private:
		mutable boost::shared_mutex mutex_;
		std::unordered_map<std::string, double> cache_;
	};

	double SharedData::SharedDataImp::get(std::string szChannelName) const {
		boost::shared_lock<boost::shared_mutex> lock(mutex_);
		if (!indexExists(szChannelName))
			return 0;
		else
			return cache_.at(szChannelName);
	}

	void SharedData::SharedDataImp::insert(std::string szChannelName, double value) {
		boost::unique_lock<boost::shared_mutex> lock(mutex_);
		cache_[szChannelName] = value;
	}

	void SharedData::SharedDataImp::update(std::string szChannelName, double value) {
		boost::unique_lock<boost::shared_mutex> lock(mutex_);
		cache_[szChannelName] = value;
	}

	SharedData::SharedData() {
		sharedDataImp_ = new SharedDataImp();
	}

	SharedData::~SharedData() {
		if (sharedDataImp_) delete sharedDataImp_;
	}

	double SharedData::read(std::string szChannelName) const {
		return sharedDataImp_->get(szChannelName);
	}

	void SharedData::write(std::string szChannelName, double value) {
		if (sharedDataImp_->indexExists(szChannelName))
			sharedDataImp_->update(szChannelName, value);
		else
			sharedDataImp_->insert(szChannelName, value);
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////

	class Writer::WriterImp {
	public:
		WriterImp(std::string id) : id_(id) {}
		void write() {
			double value = static_rand_initializer.getValueRnd();
			write(value);
		}

		void write(double value) {
			sharedData.write(id_, value);
			std::cout << "Writer [" << id_ << "] - value: " << value << std::endl;
		}
	private:
		std::string id_;
	};

	void Writer::write(double value) {
		writerImp_->write(value);
	}

	void Writer::write() {
		writerImp_->write();
	}

	Writer::Writer(const std::string& id) {
		writerImp_ = new WriterImp(id);
	}

	Writer::~Writer() {
		if (writerImp_) delete writerImp_;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*class Reader::ReaderImp {
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
*/
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////
	double FobusClient::getData(const std::string& szChannel) {
		for (int i = 0; i < 1000000; ++i)
			std::sqrt(123456789123.00);
		return sharedData.read(szChannel);
	}
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////

	class UpdateRouter::ThreadPool {
	public:
		ThreadPool() : myWork(myService) {
			size_t nThreads = boost::thread::hardware_concurrency();
			if (nThreads == 0) nThreads = 4;
			initThreadPool(nThreads);
		}

		ThreadPool(size_t nThreads) : myWork(myService){
			initThreadPool(nThreads);
		};

		~ThreadPool();

		template<class Task>
		void runTask(Task task) {
			myService.post(task);
		}

		void joinAll() {
			myTrds.join_all();
		}

	private:
		boost::asio::io_service myService;
		boost::asio::io_service::work myWork;
		boost::thread_group myTrds;

		void initThreadPool(size_t nTrds);
	};

	void UpdateRouter::ThreadPool::initThreadPool(size_t nTrds) {
		for (size_t counter = 0; counter < nTrds; ++counter)
			myTrds.create_thread(std::bind(&boost::asio::io_service::run, &myService));
	}

	UpdateRouter::ThreadPool::~ThreadPool() {
		myService.stop();
		try {
			myTrds.join_all();
		}
		catch (...) {}
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	class UpdateWorker {
	public:
		typedef std::shared_ptr<UpdateWorker> Ptr;

		UpdateWorker(const FobusClient::Ptr& fobusClient, const std::string& szChannelName, DataPtr& pData)
			: myChannelName(szChannelName), myData(pData), myFobusClient(fobusClient), myReady(new bool(false)){}
		void operator()() {
			*myData = myFobusClient->getData(myChannelName);
			*myReady = true;
		}

		bool isReady() { return *myReady; }
	private:
		const std::string& myChannelName;
		DataPtr& myData;
		const FobusClient::Ptr& myFobusClient;
		std::shared_ptr<bool> myReady;
	};

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////
	bool UpdateRouter::update(CachePtr cache) {
		// make sure we have enough fobus clients
		int nDiff = myReaders.size() - cache->size();
		if (nDiff < 0) {
			for (size_t counter = 0; counter < abs(nDiff); ++counter) {
				myReaders.emplace_back(FobusClient::Ptr(new FobusClient()));
			}
		}

		//distribute workers
		std::vector<UpdateWorker> vUpdateWorkers;
		size_t counter = 0;
		for (auto itCache = cache->begin(); itCache != cache->end(); ++itCache, ++counter) {
			vUpdateWorkers.emplace_back(UpdateWorker(myReaders[counter], itCache->first, itCache->second));
			mypThreadPool->runTask(vUpdateWorkers.back());
		}

		for (auto itUpdateWorker = vUpdateWorkers.begin(); itUpdateWorker != vUpdateWorkers.end(); ++itUpdateWorker){
			while (!(itUpdateWorker->isReady())) {}
		}
		return true;
	}

	UpdateRouter::UpdateRouter() : mypThreadPool(new ThreadPool(100)) {}
	UpdateRouter::~UpdateRouter(){
		if (mypThreadPool)
			delete mypThreadPool;
	}
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////
}
