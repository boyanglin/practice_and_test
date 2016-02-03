#include "Items.h"
#include "Exception.h"
#include "Utilities.h"

#include <functional>
#include <iomanip>  
#include <iostream>
#include <memory>
#include <map>

#define RUN_ITEM(num) item##num::run()
#define RUN_ITEM_CASE(num) case num: \
                               RUN_ITEM(num); \
                               break


#define REGISTER_ITEM_FUN(item_num, item_run) \
static Utils::ItemRunRegister item_run_register(item_num, item_run);

#define RUN_FUNCTION_DECL(item_num) void run() \
{ \
	const unsigned long ITEM_NUM = item_num;\
	PRINT_FUNCTION_NAME;

#define RUN_FUNCTION_END(item_num)\
	static_assert(ITEM_NUM == item_num, "The item number doesn't."); \
} \
REGISTER_ITEM_FUN(item_num, run)

namespace Utils
{
    class EmptyObject
    {
    };
	class  ItemRunFunctions
	{
		friend struct ItemRunRegister;

		std::map<unsigned long, std::function<void()>> item_runners_;

		void register_run_function(unsigned long item_num, std::function<void()> item_run_func)
		{
			auto result = item_runners_.insert(std::make_pair(item_num, item_run_func));
			if (!result.second)
			{
				ERROR("Item " << item_num << " has registered the run function.");
			}
		}

	public:

		void run(unsigned long item_num) const
		{
			PRINT_LINE("Running item " << item_num << " ...");
			item_runners_.at(item_num)();
		}
	};

	ItemRunFunctions& getItemRunFunctions()
	{
		static std::unique_ptr<ItemRunFunctions> item_run_functions = std::make_unique<ItemRunFunctions>();
		return *item_run_functions;
	}

	struct ItemRunRegister
	{
		ItemRunRegister(unsigned long item_num, std::function<void()> item_run_func)
		{
			getItemRunFunctions().register_run_function(item_num, item_run_func);
		}
	};

}

namespace EMCPP
{

    void runItem(unsigned long item_num)
    {
		Utils::getItemRunFunctions().run(item_num);
    }

	namespace item1
	{
		namespace case_1
		{
			template<typename T>
			void f_1_1(T& param) // param is a reference
			{
				PRINT_FUNCTION_NAME;
				using value_type = T;
				T a = param;
				PRINT_MSG("Type of T: " << type_name<decltype(a)>().c_str());
				PRINT_MSG("Type of param: " << type_name<decltype(param)>().c_str());
			}

			template<typename T>
			void f_1_2(const T& param) // param is now a ref-to-const
			{
				PRINT_FUNCTION_NAME;
				using value_type = T;
				T a = param;
				PRINT_MSG("Type of T: " << type_name<decltype(a)>().c_str());
				PRINT_MSG("Type of param: " << type_name<decltype(param)>().c_str());
			}

			void example()
			{
				PRINT_FUNCTION_NAME;

				PRINT_AND_RUN_CODE(int x = 27);
				PRINT_AND_RUN_CODE(f_1_1(x));
				PRINT_AND_RUN_CODE(f_1_2(x)); 
				PRINT_LINE("");

				PRINT_AND_RUN_CODE(const int cx = x); 
				PRINT_AND_RUN_CODE(f_1_1(cx));
				PRINT_AND_RUN_CODE(f_1_2(cx)); 
				PRINT_LINE("");

				PRINT_AND_RUN_CODE(const int& rx = x); 
				PRINT_AND_RUN_CODE(f_1_1(rx));
				PRINT_AND_RUN_CODE(f_1_2(rx));
				PRINT_LINE("");
			}
		}

		void templateTypeDeduction()
		{
			PRINT_FUNCTION_NAME;
			PRINT_LINE(std::setfill('=') << std::setw(50) << "" << std::setfill(' '));
			case_1::example();
			PRINT_LINE(std::setfill('=') << std::setw(50) << "" << std::setfill(' '));
		}

		RUN_FUNCTION_DECL(1)
			templateTypeDeduction();
		RUN_FUNCTION_END(1)
	}

    //tem 18: Use std::unique_ptr for exclusive-ownership resource management.
    namespace item18
    {
		void initialiseUniquePtr()
		{
			PRINT_FUNCTION_NAME;

			//http://www.cplusplus.com/reference/memory/unique_ptr/unique_ptr/

			std::unique_ptr<Utils::EmptyObject> a(new Utils::EmptyObject);

			// ******** Copying a std::unique_ptr isn’t allowed ****/
			// ==========================================================================================
			// Notes:
			// The copy constructor and assignment operator have been delete in the <memory.h> (shown as following)
			// unique_ptr(const _Myt&) = delete;
			// _Myt& operator=(const _Myt&) = delete;
			// ==========================================================================================
			// code: the following code doesn't compile
			// std::unique_ptr<Utils::EmptyObject> b = a;
			// std::unique_ptr<Utils::EmptyObject> c = nullptr;
			// c = a;
			// ==========================================================================================

			// ******** std::unique_ptr is thus a move-only type ****/
			std::unique_ptr<Utils::EmptyObject> d = std::move(a);
			ASSERT((a == nullptr), "Cannot move a to d.");

			//copied from:
			//http://en.cppreference.com/w/cpp/memory/unique_ptr/unique_ptr
			{
				struct Foo { // object to manage
					Foo() { std::cout << "Foo ctor\n"; }
					Foo(const Foo&) { std::cout << "Foo copy ctor\n"; }
					Foo(Foo&&) { std::cout << "Foo move ctor\n"; }
					~Foo() { std::cout << "~Foo dtor\n"; }
				};

#pragma warning ( disable : 4521 ) //warning C4521: 'EMCPP::item18::initialiseUniquePtr::D': multiple copy constructors specified
				struct D { // deleter
					D() {};
					D(const D&) { std::cout << "D copy ctor\n"; }
					D(D&) { std::cout << "D non-const copy ctor\n"; } // C4521
					D(D&&) { std::cout << "D move ctor \n"; }
					void operator()(Foo* p) const {
						std::cout << "D is deleting a Foo\n";
						delete p;
					};
				};
#pragma warning ( default : 4521)

				std::cout << "Example constructor(1)...\n";
				std::unique_ptr<Foo> up1;  // up1 is empty
				std::unique_ptr<Foo> up1b(nullptr);  // up1b is empty

				std::cout << "Example constructor(2)...\n";
				{
					std::unique_ptr<Foo> up2(new Foo); //up2 now owns a Foo
				} // Foo deleted

				std::cout << "Example constructor(3)...\n";
				D d;
				{  // deleter type is not a reference
					std::unique_ptr<Foo, D> up3(new Foo, d); // deleter copied
				}

				{  // deleter type is a reference 
					std::unique_ptr<Foo, D&> up3b(new Foo, d); // up3b holds a reference to d
				}

				std::cout << "Example constructor(4)...\n";
				{  // deleter is not a reference 
					std::unique_ptr<Foo, D> up4(new Foo, D()); // deleter moved
				}

				std::cout << "Example constructor(5)...\n";
				{
					std::unique_ptr<Foo> up5a(new Foo);
					std::unique_ptr<Foo> up5b(std::move(up5a)); // ownership transfer
				}

				std::cout << "Example constructor(6)...\n";
				{
					std::unique_ptr<Foo, D> up6a(new Foo, d); // D is copied
					std::unique_ptr<Foo, D> up6b(std::move(up6a)); // D is moved

					std::unique_ptr<Foo, D&> up6c(new Foo, d); // D is a reference
					std::unique_ptr<Foo, D> up6d(std::move(up6c)); // D is copied
				}

				std::cout << "Example constructor(7)...\n";
				{
					std::auto_ptr<Foo> up7a(new Foo);
					std::unique_ptr<Foo> up7b(std::move(up7a)); // ownership transfer
				}
			}
        }

		RUN_FUNCTION_DECL(18)
            initialiseUniquePtr();
		RUN_FUNCTION_END(18)
    } //namespace Item18

    //Item 19: Use std::shared_ptr for shared-ownership resource management.
    namespace item19
    {
		RUN_FUNCTION_DECL(19);
		RUN_FUNCTION_END(19);
    }//namespace Item19

} //namespace EMCPP