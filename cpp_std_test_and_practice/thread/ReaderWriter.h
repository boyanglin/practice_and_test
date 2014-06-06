#ifndef READER_WRITER_H_
#define READER_WRITER_H_

#include <memory>
#include <vector>
#include <unordered_map>
#include <map>

namespace ReaderWriter {

	class SharedData{
	public:
		SharedData();
		~SharedData();

		double read(std::string index) const;
		void write(std::string index, double value);

	private:
		class SharedDataImp;
		SharedDataImp* sharedDataImp_;
	};

	class Writer {
	public:
		Writer(const std::string& id);
		~Writer();

		void write();
		void write(double value);
	private:
		class WriterImp;
		WriterImp* writerImp_;
	};

	//class Reader {
	//public:
	//	typedef std::shared_ptr<Reader> Ptr;

	//	Reader(int id);
	//	~Reader();

	//	void read(const std::shared_ptr<SharedData> shared_data) const;
	//private:
	//	class ReaderImp;
	//	ReaderImp* readerImp_;
	//};

	typedef std::shared_ptr<double> DataPtr;
	typedef std::map< std::string, DataPtr> Cache;
	typedef std::shared_ptr<Cache> CachePtr;

	class FobusClient {
	public:
		typedef std::shared_ptr<FobusClient> Ptr;
		double getData(const std::string& szChannel);
	private:

	};

	class UpdateRouter {
	public:
		UpdateRouter();
		~UpdateRouter();
		bool update(CachePtr cache);
	private:
		std::vector<FobusClient::Ptr> myReaders;
		class ThreadPool;
		ThreadPool* mypThreadPool;
	};
}
#endif