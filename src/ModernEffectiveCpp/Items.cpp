#include "Items.h"
#include "Utilities.h"

#include <iostream>
#include <memory>

#define RUN_ITEM(num) item##num::run()
#define RUN_ITEM_CASE(num) case num: \
                               RUN_ITEM(num); \
                               break

#define TEST_FUNC_DECL(func) void func() \
                             { \
                                 PRINT_FUNCTION_NAME;

namespace Utils
{
    class EmptyObject
    {
    };
}

namespace EMCPP
{
    void runItem(unsigned int item)
    {
        PRINT_LINE("Running item " << item << " ...");
        switch (item)
        {
        RUN_ITEM_CASE(1);
        RUN_ITEM_CASE(18);
        RUN_ITEM_CASE(19);
        default:
            PRINT_LINE("Please select an item number.");
        }
    }

	namespace item1
	{
		namespace
		{
			template <class T>
			std::string type_name()
			{
				typedef typename std::remove_reference<T>::type TR;
				std::unique_ptr<char, void(*)(void*)> own
					(
#ifndef _MSC_VER
						abi::__cxa_demangle(typeid(TR).name(), nullptr,
							nullptr, nullptr),
#else
						nullptr,
#endif
						std::free
						);
				std::string r = own != nullptr ? own.get() : typeid(TR).name();
				if (std::is_const<TR>::value)
					r += " const";
				if (std::is_volatile<TR>::value)
					r += " volatile";
				if (std::is_lvalue_reference<T>::value)
					r += "&";
				else if (std::is_rvalue_reference<T>::value)
					r += "&&";
				return r;
			}

			template<typename T>
			void f_1(T& param) // param is a reference
			{
				using value_type = T;
				T a = param;
				PRINT_LINE("Type of T: " << type_name<decltype(a)>().c_str());
				PRINT_LINE("Type of T: " << type_name<decltype(param)>().c_str());
			}

			void case_1()
			{
				const int a = 1;
				int x = 27; 
				PRINT_LINE("x is an int");
				PRINT_POD(x);
				f_1(x);

				const int cx = x; 
				PRINT_LINE("cx is a const int");
				PRINT_POD(cx);
				f_1(cx);

				const int& rx = x; 
				PRINT_LINE("rx is a reference to x as a const int");
				PRINT_POD(rx);
				f_1(rx);
			}
		}

		void templateTypeDeduction()
		{
			PRINT_FUNCTION_NAME;
			case_1();
		}

		void run()
		{
			templateTypeDeduction();
		}
	}

    //tem 18: Use std::unique_ptr for exclusive-ownership resource management.
    namespace item18
    {
		TEST_FUNC_DECL(initialiseUniquePtr)

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

				struct D { // deleter
					D() {};
					D(const D&) { std::cout << "D copy ctor\n"; }
					D(D&) { std::cout << "D non-const copy ctor\n"; }
					D(D&&) { std::cout << "D move ctor \n"; }
					void operator()(Foo* p) const {
						std::cout << "D is deleting a Foo\n";
						delete p;
					};
				};

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

        void run()
        {
            initialiseUniquePtr();
        }
    } //namespace Item18

    //Item 19: Use std::shared_ptr for shared-ownership resource management.
    namespace item19
    {

        void run()
        {

        }
    }//namespace Item19

} //namespace EMCPP