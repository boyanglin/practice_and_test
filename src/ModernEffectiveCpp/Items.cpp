#include "Items.h"
#include "Exception.h"
#include "Utilities.h"

#include <functional>
#include <iomanip>  
#include <iostream>
#include <memory>
#include <map>
#include <stdio.h>


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

//

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
		// ParamType is a Reference or Pointer, but not a Universal Reference
		namespace case_1 
		{
			template<typename T>
			void f_1(T& param) // param is a reference
			{
				PRINT_CALL_FUNCTION_INDENT(1);
				PRINT_CODE_INDENT(1, T a = param);
				PRINT_TYPE_INDENT(1, a);
				PRINT_TYPE_INDENT(1, param);
			}

			template<typename T>
			void f_2(const T& param) // param is now a ref-to-const
			{
				PRINT_CALL_FUNCTION_INDENT(1);
				PRINT_CODE_INDENT(1, T a = param);
				PRINT_TYPE_INDENT(1, a);
				PRINT_TYPE_INDENT(1, param);
			}

			void example()
			{
				PRINT_FUNCTION_NAME;

				PRINT_EMPTY_LINE;
				PRINT_LINE("f_1 function signature:");
				PRINT_LINE("template<typename T>");
				PRINT_LINE("void f_1(T& param)");
				PRINT_EMPTY_LINE;

				PRINT_EMPTY_LINE;
				PRINT_LINE("f_2 function signature:");
				PRINT_LINE("template<typename T>");
				PRINT_LINE("void f_2(const T& param)");
				PRINT_EMPTY_LINE;

				PRINT_CODE(int x = 27);
				PRINT_CODE(f_1(x));
				PRINT_CODE(f_2(x)); 
				PRINT_EMPTY_LINE;

				PRINT_CODE(const int cx = x); 
				PRINT_CODE(f_1(cx));
				PRINT_CODE(f_2(cx)); 
				PRINT_EMPTY_LINE;

				PRINT_CODE(const int& rx = x); 
				PRINT_CODE(f_1(rx));
				PRINT_CODE(f_2(rx));
				PRINT_EMPTY_LINE;
			}
		}

		// ParamType is a Universal Reference
		namespace case_2
		{
			template<typename T>
			void f_1(T&& param) // param is a universal reference
			{
				PRINT_CALL_FUNCTION_INDENT(1);
				PRINT_CODE_INDENT(1, T a = param);
				PRINT_TYPE_INDENT(1, a);
				PRINT_TYPE_INDENT(1, param);
			}

			void example()
			{
				PRINT_FUNCTION_NAME;
				PRINT_EMPTY_LINE;

				PRINT_LINE("f_1 function signature:");
				PRINT_LINE("template<typename T>");
				PRINT_LINE("void f_1(T&& param)");
				PRINT_EMPTY_LINE;

				PRINT_CODE(int x = 27); 
				PRINT_CODE(f_1(x));
				PRINT_EMPTY_LINE;

				PRINT_CODE(const int cx = x); 
				PRINT_CODE(f_1(cx));
				PRINT_EMPTY_LINE;

				PRINT_CODE(const int& rx = x); 
				PRINT_CODE(f_1(rx));
				PRINT_EMPTY_LINE;

				PRINT_CODE(f_1(27));
				PRINT_EMPTY_LINE;

			}
		}

		//ParamType is Neither a Pointer nor a Reference
		namespace case_3
		{
			template<typename T>
			void f_1(T param) // param is passed by value
			{
				PRINT_CALL_FUNCTION_INDENT(1);
				PRINT_CODE_INDENT(1, T a = param);
				PRINT_TYPE_INDENT(1, a);
				PRINT_TYPE_INDENT(1, param);
			}

			void example()
			{
				PRINT_FUNCTION_NAME;

				PRINT_EMPTY_LINE;
				PRINT_LINE("f_1 function signature:");
				PRINT_LINE("template<typename T>");
				PRINT_LINE("void f_1(T param)");
				PRINT_EMPTY_LINE;

				PRINT_CODE(int x = 27);
				PRINT_CODE(f_1(x));
				PRINT_EMPTY_LINE;

				PRINT_CODE(const int cx = x);
				PRINT_CODE(f_1(cx));
				PRINT_EMPTY_LINE;

				PRINT_CODE(const int& rx = x);
				PRINT_CODE(f_1(rx));
				PRINT_EMPTY_LINE;

				PRINT_CODE(const char* const ptr = "Fun with pointers");// ptr is const pointer to const object
				PRINT_CODE(f_1(ptr)); // pass arg of type const char * const
				PRINT_EMPTY_LINE;
			}
		}

		namespace ArrayArguments
		{
			template<typename T>
			void f_1(T param)
			{
				PRINT_CALL_FUNCTION_INDENT(1);
				PRINT_CODE_INDENT(1, T a = param);
				PRINT_TYPE_INDENT(1, a);
				PRINT_TYPE_INDENT(1, param);
			}

			template<typename T>
			void f_2(T& param)
			{
				PRINT_CALL_FUNCTION_INDENT(1);
				PRINT_CODE_INDENT(1, T a = "");
				PRINT_TYPE_INDENT(1, a);
				PRINT_TYPE_INDENT(1, param);
			}

			template<typename T, std::size_t N> 
			constexpr std::size_t arraySize(T(&param)[N]) noexcept 
			{ // constexpr
#ifdef _MSC_VER
#pragma message("Call " __FUNCTION__)
#endif
				PRINT_VALUE("Call "); PRINT_FUNCTION_NAME;
				PRINT_TYPE_INDENT(1, param);
				return N; 
			}

#pragma warning(disable:4101)
			void example()
			{
				PRINT_FUNCTION_NAME;
				
				PRINT_CODE(const char name[] = "A name");
				PRINT_CODE(const char * ptrToName = name);
				PRINT_EMPTY_LINE;

				PRINT_LINE("f_1 function signature:");
				PRINT_LINE("template<typename T>");
				PRINT_LINE("void f_1(T param)");
				PRINT_EMPTY_LINE;

				PRINT_CODE(f_1(name));
				PRINT_EMPTY_LINE;

				PRINT_CODE(f_1(ptrToName));
				PRINT_EMPTY_LINE;

				PRINT_LINE("f_2 function signature:");
				PRINT_LINE("template<typename T>");
				PRINT_LINE("void f_2(T& param)");
				PRINT_EMPTY_LINE;

				PRINT_CODE(f_2(name));
				PRINT_EMPTY_LINE;

				PRINT_CODE(f_2(ptrToName));
				PRINT_EMPTY_LINE;

				PRINT_LINE("template<typename T, std::size_t N>");
				PRINT_LINE("constexpr std::size_t arraySize(T(&)[N]) noexcept");
				PRINT_EMPTY_LINE;

				PRINT_CODE(char mappedVals[arraySize(name)]);
				PRINT_CODE(const auto sizeOfName = sizeof(name) / sizeof(char));
				PRINT_CODE(const auto sizeOfMappedVals = sizeof(mappedVals) / sizeof(char));
#ifdef _MSC_VER
                //TODO: figure out why it doesn't work on mac.
				static_assert(sizeOfName == sizeOfMappedVals, "size of two arrays are different.");
#endif
#pragma warning(default:4101)

				PRINT_POD(sizeOfName);
				PRINT_POD(sizeOfMappedVals);
				PRINT_EMPTY_LINE;
			}
		}

		namespace FunctionArguments
		{
			void func(int, double)
			{}

			template<class T>
			void f_1(T param)
			{
				PRINT_CALL_FUNCTION_INDENT(1);
				PRINT_CODE_INDENT(1, T a = param);
				PRINT_TYPE_INDENT(1, a);
				PRINT_TYPE_INDENT(1, param);
			}

			template<class T>
			void f_2(T& param)
			{
				PRINT_CALL_FUNCTION_INDENT(1);
				PRINT_CODE_INDENT(1, T *a = param);
				PRINT_TYPE_INDENT(1, a);
				PRINT_TYPE_INDENT(1, param);
			}

			void example()
			{
				PRINT_FUNCTION_NAME;
				PRINT_EMPTY_LINE;

				PRINT_CODE(auto func1 = func);
				PRINT_TYPE(func1);
				PRINT_EMPTY_LINE;

				PRINT_CODE(auto& func2 = func);
				PRINT_TYPE(func2);
				PRINT_EMPTY_LINE;

				PRINT_CODE(auto func3 = &func);
				PRINT_TYPE(func3);
				PRINT_EMPTY_LINE;

				PRINT_CODE(auto* func4 = &func);
				PRINT_TYPE(func4);
				PRINT_EMPTY_LINE;

				PRINT_LINE("f_1 function signature:");
				PRINT_LINE("template<typename T>");
				PRINT_LINE("void f_1(T param)");
				PRINT_EMPTY_LINE;

				PRINT_CODE(f_1(func));
				PRINT_EMPTY_LINE;

				PRINT_LINE("f_2 function signature:");
				PRINT_LINE("template<typename T>");
				PRINT_LINE("void f_2(T& param)");
				PRINT_EMPTY_LINE;

				PRINT_CODE(f_2(func));
				PRINT_EMPTY_LINE;
			}
		}

		void templateTypeDeduction()
		{
			PRINT_FUNCTION_NAME;
			PRINT_SEPERATOR_LINE;
			case_1::example();
			PRINT_SEPERATOR_LINE;
			case_2::example();
			PRINT_SEPERATOR_LINE;
			case_3::example();
			PRINT_SEPERATOR_LINE;
			ArrayArguments::example();
			PRINT_SEPERATOR_LINE;
			FunctionArguments::example();
			PRINT_SEPERATOR_LINE;

		}

		RUN_FUNCTION_DECL(1)
			templateTypeDeduction();
		RUN_FUNCTION_END(1)
	}

	namespace item2 //item2: Understand auto type deduction
	{
		//ParamType is a Reference or Pointer, but not a Universal Reference
		namespace Case1And3
		{
			template<typename T> // conceptual template for deducing type of auto x 
			std::string func_for_x(T param)
			{
				PRINT_CALL_FUNCTION_INDENT(1);
				PRINT_CODE_INDENT(1, T a = param);
				PRINT_TYPE_INDENT(1, a);
				PRINT_TYPE_INDENT(1, param);
				return TYPE_NAME(param);
			}

			template<typename T> // conceptual template for deducing type of auto& x 
			std::string func_for_rx(T& param)
			{
				PRINT_CALL_FUNCTION_INDENT(1);
				PRINT_CODE_INDENT(1, T a = param);
				PRINT_TYPE_INDENT(1, a);
				PRINT_TYPE_INDENT(1, param);
				return TYPE_NAME(param);
			}

			template<typename T> // conceptual template for deducing type of const auto
			std::string func_for_cx(const T param)
			{
				PRINT_CALL_FUNCTION_INDENT(1);
				PRINT_CODE_INDENT(1, T a = param);
				PRINT_TYPE_INDENT(1, a);
				PRINT_TYPE_INDENT(1, param);
				return TYPE_NAME(param);
			}

			template<typename T> // conceptual template for deducing type of const auto &
			std::string func_for_crx(const T& param)
			{
				PRINT_CALL_FUNCTION_INDENT(1);
				PRINT_CODE_INDENT(1, T a = param);
				PRINT_TYPE_INDENT(1, a);
				PRINT_TYPE_INDENT(1, param);
				return TYPE_NAME(param);
			}
		
			void example()
			{
				PRINT_FUNCTION_NAME;
				PRINT_EMPTY_LINE;

				PRINT_LINE("Function Signature:");
				PRINT_LINE("template<typename T>");
				PRINT_LINE("void func_for_x(T param)");
				PRINT_EMPTY_LINE;

				PRINT_CODE(auto x = 27);
				PRINT_TYPE(x);
				PRINT_CODE(std::string xType = Case1And3::func_for_x(27)); 
				ASSERT(xType == TYPE_NAME(x), "Type doesn't match.");
				PRINT_EMPTY_LINE;

				PRINT_LINE("Function Signature:");
				PRINT_LINE("template<typename T>");
				PRINT_LINE("void func_for_rx(T& param)");
				PRINT_EMPTY_LINE;

				PRINT_CODE(auto& rx = x);
				PRINT_TYPE(rx);
				PRINT_CODE(std::string rxType = Case1And3::func_for_rx(x)); 
				ASSERT(rxType == TYPE_NAME(rx), "Type doesn't match.");
				PRINT_EMPTY_LINE;


				PRINT_LINE("Function Signature:");
				PRINT_LINE("template<typename T>");
				PRINT_LINE("void func_for_cx(const T param)");
				PRINT_EMPTY_LINE;

				PRINT_CODE(const auto cx = x);	
				PRINT_TYPE(cx);
				PRINT_CODE(std::string cxType = Case1And3::func_for_cx(x)); 
				ASSERT(cxType == TYPE_NAME(cx), "Type doesn't match.");
				PRINT_EMPTY_LINE;

				PRINT_CODE(const auto& crx = x);
				PRINT_TYPE(crx);
				PRINT_CODE(std::string crxType = Case1And3::func_for_crx(x));
				ASSERT(crxType == TYPE_NAME(crx), "Type doesn't match.");
				PRINT_EMPTY_LINE;
			}
		}



		void autoTypeDeduction()
		{
			PRINT_FUNCTION_NAME;
			PRINT_SEPERATOR_LINE;
			Case1And3::example();
			PRINT_SEPERATOR_LINE;
		}
		RUN_FUNCTION_DECL(2)
			autoTypeDeduction();
		RUN_FUNCTION_END(2)
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