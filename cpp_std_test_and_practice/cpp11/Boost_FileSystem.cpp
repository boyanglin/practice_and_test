#include "Boost_FileSystem.h"

#include "Common.h"

#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/progress.hpp>
#include <boost/algorithm/string.hpp>

#include <iostream>

namespace Boost_Example
{
	std::vector<std::string> listFiles(const std::string & dir, const std::string & extension = "")
	{
		std::vector<std::string> aFiles;
		boost::filesystem::path aDir = dir;
		ASSERT(boost::filesystem::exists(aDir), "The target directory does not exist. \n Director: " + aDir.string());

		bool aIsCheckExtension = extension.length() > 0;
		std::string aExtension = "." + extension;
		boost::filesystem::directory_iterator end_iter;
		for (boost::filesystem::directory_iterator it(aDir); it != end_iter; ++it)
		{
			if (boost::filesystem::is_regular_file(it->status()))
			{
				if (aIsCheckExtension && !boost::iequals(it->path().filename().extension().string(), aExtension))
						continue;
				aFiles.push_back(it->path().filename().string());
			}
		}
		return aFiles;
	}

	namespace fs = boost::filesystem;
	int Boost_FileSystem_ExampleFunc1()
	{
		boost::progress_timer t(std::clog);

		fs::path full_path("c:\\Temp");

		unsigned long file_count = 0;
		unsigned long dir_count = 0;
		unsigned long other_count = 0;
		unsigned long err_count = 0;

		if (!fs::exists(full_path))
		{
			std::cout << "\nNot found: " << full_path.string() << std::endl;
			return 1;
		}

		if (fs::is_directory(full_path))
		{
			std::cout << "\nIn directory: "
				<< full_path.string() << "\n\n";
			fs::directory_iterator end_iter;
			for (fs::directory_iterator dir_itr(full_path);
				 dir_itr != end_iter;
				 ++dir_itr)
			{
				try
				{
					if (fs::is_directory(dir_itr->status()))
					{
						++dir_count;
						std::cout << dir_itr->path().filename() << " [directory]\n";
					}
					else if (fs::is_regular_file(dir_itr->status()))
					{
						++file_count;
						std::cout << dir_itr->path().filename() << "\n";
					}
					else
					{
						++other_count;
						std::cout << dir_itr->path().filename() << " [other]\n";
					}

				}
				catch (const std::exception & ex)
				{
					++err_count;
					std::cout << dir_itr->path().filename() << " " << ex.what() << std::endl;
				}
			}
			std::cout << "\n" << file_count << " files\n"
				<< dir_count << " directories\n"
				<< other_count << " others\n"
				<< err_count << " errors\n";
		}
		else // must be a file
		{
			std::cout << "\nFound: " << full_path.string() << "\n";
		}
		return 0;
	}
}

namespace CPP_STD_TEST_AND_PRACTIVE_TS
{

	namespace
	{
		void listFilesTS()
		{
			std::cout << "********* list all files ********\n";
			std::string aDir = "C:\\Temp\\";
			std::vector<std::string> aFiles1 = Boost_Example::listFiles(aDir);
			for (auto & file : aFiles1)
			{
				std::cout << file << std::endl;
			}


			std::cout << "********* list only xml files ********\n";
			std::string aExtension = "xml";
			std::vector<std::string> aFiles2 = Boost_Example::listFiles(aDir, aExtension);
			for (auto & file : aFiles2)
			{
				std::cout << file << std::endl;
			}

		}
	}

	using namespace boost::unit_test_framework;

	test_suite* Boost_FileSystemTS::suite()
	{
		test_suite* suite = BOOST_TEST_SUITE("Boost_FileSystemTS");
		suite->add(BOOST_TEST_CASE(&Boost_Example::Boost_FileSystem_ExampleFunc1));
		suite->add(BOOST_TEST_CASE(&listFilesTS));
		return suite;
	}
} //namespace CPP_STD_TEST_AND_PRACTIVE_TS