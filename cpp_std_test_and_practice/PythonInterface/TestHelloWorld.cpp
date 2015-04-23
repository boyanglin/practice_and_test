#define BOOST_PYTHON_STATIC_LIB    
#include <boost/python.hpp>
using namespace boost::python;


struct World
{
	void set(std::string msg) { this->msg = msg; }
	std::string greet() { return msg; }
	std::string msg;
};


// the module name should be the same with the pyd name
BOOST_PYTHON_MODULE(PythonInterface)
{
	class_<World>("World")
		.def("greet", &World::greet)
		.def("set", &World::set);
}