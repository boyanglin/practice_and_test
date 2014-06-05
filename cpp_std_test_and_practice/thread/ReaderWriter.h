#ifndef READER_WRITER_H_
#define READER_WRITER_H_


namespace ReaderWriter {
	class SharedData{
	public:
		SharedData();
		~SharedData();

		double read(int index) const;
		void write(int index, double value);

	private:
		class SharedDataImp;
		SharedDataImp* sharedDataImp_;
	};

	class Writer {
	public:
		Writer(int id);
		~Writer();

		void write(std::shared_ptr<SharedData> shared_data);
		void write(std::shared_ptr<SharedData> shared_data, double value);
	private:
		class WriterImp;
		WriterImp* writerImp_;
	};

	class Reader {
	public:
		Reader(int id);
		~Reader();

		void read(const std::shared_ptr<SharedData> shared_data) const;
	private:
		class ReaderImp;
		ReaderImp* readerImp_;
	};

}
#endif