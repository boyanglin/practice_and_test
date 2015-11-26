#ifndef POLYMORPHISM_H_
#define POLYMORPHISM_H_

#include "Common.h"

namespace Polymorphism
{
	class Base
	{
	public:
		Base()
			:mPublicMemer("private member"), mProtectedMember("protected member"), mPrivateMember("private member")
		{
		}

		virtual ~Base() = 0;

		virtual void myVirtualFunc_1() const = 0;

		virtual void myVirtualFunc_2() const = 0;

		std::string mPublicMemer;
	protected:
		std::string mProtectedMember;
	private:
		std::string mPrivateMember;

	};

	inline Base::~Base() {}
	// ******NOTE****** we got the following linking error if we don't define destructor here
	//  PolymorphismTS.obj : error LNK2019 : unresolved external symbol "public: virtual __thiscall
	//	Polymorphism::Base::~Base(void)" (??1Base@Polymorphism@@UAE@XZ) referenced in function "public: virtual __thiscall
	//	Polymorphism::Deriv1::~Deriv1(void)" (??1Deriv1@Polymorphism@@UAE@XZ) (Local CPU 1, 0:01.15 at +0:13)
	//	C : \WorkArea\practice_and_test\cpp_std_test_and_practice\Debug\cpp11.exe : fatal error LNK1120 : 1 unresolved externals


	// ******NOTE****** we test different inheritance mode
	// http://stackoverflow.com/questions/860339/difference-between-private-public-and-protected-inheritance

	class Deriv1_Public_1 : public Base
	{
	public:
		virtual void myVirtualFunc_1() const
		{
			SHOW_FUNCTION_NAME;
		}
		// ******NOTE****** we got the following compiler error if we don't define myVirtualFunc_1() here
		//	c : \workarea\practice_and_test\cpp_std_test_and_practice\cpp11\polymorphismts.cpp(18) : error C2259 :
		//	'Polymorphism::Deriv1' : cannot instantiate abstract class
		//	due to following members :
		//	'void Polymorphism::Base::myVirtualFunc_1(void)' : is abstract
		//	c : \workarea\practice_and_test\cpp_std_test_and_practice\cpp11\polymorphism.h(12) : see declaration of
		//	'Polymorphism::Base::myVirtualFunc_1'

		// ******NOTE****** we don't have to define the virtual destructor here
		//virtual ~Deriv1() {}

	protected:
		virtual void myVirtualFunc_2() const
		{
			SHOW_FUNCTION_NAME;
		}
		// ******NOTE****** we change the scope of myVirtualFunc_2 in derive class
		//http://stackoverflow.com/questions/2141188/changing-function-access-mode-in-derived-class
	private:
	};

	// ******NOTE******
	// we don't have to define the pure virtual function in the following cases
	// ****************
	class Deriv1_Protected : protected Base
	{
	public:
	protected:
	private:
	};

	class Deriv1_Private : private Base
	{
	public:
	protected:
	private:
	};

	class Deriv2_Public : public Deriv1_Public_1
	{
	public:
		void showMembers() const
		{
			COUT_LINE(mPublicMemer.c_str());
			COUT_LINE(mProtectedMember.c_str());

			//COUT_LINE(mPrivateMember);
			// ******NOTE****** derived class doesn't have access to private member
		}
	protected:
	private:
	};

	class Deriv2_Protected : public Deriv1_Protected
	{
	public:
		void showMembers() const
		{
			COUT_LINE(mPublicMemer.c_str());
			COUT_LINE(mProtectedMember.c_str());

			//COUT_LINE(mPrivateMember);
			// ******NOTE****** derived class doesn't have access to private member
		}
	protected:
	private:
	};

	class Deriv2_Private : public Deriv1_Private
	{
	public:
		void showMembers() const
		{
			//COUT_LINE(mPublicMemer.c_str());
			//c:\workarea\practice_and_test\cpp_std_test_and_practice\cpp11\polymorphism.h(118) : error C2247 :
			//'Polymorphism::Base::mPublicMemer' not accessible because 'Polymorphism::Deriv1_Private' uses 'private' to inherit from
			//	'Polymorphism::Base'
			//c:\workarea\practice_and_test\cpp_std_test_and_practice\cpp11\polymorphism.h(118) : error C2247 :
			//'Polymorphism::Base::mPublicMemer' not accessible because 'Polymorphism::Deriv1_Private' uses 'private' to inherit from
			//	'Polymorphism::Base'

			//COUT_LINE(mProtectedMember.c_str());
			//c:\workarea\practice_and_test\cpp_std_test_and_practice\cpp11\polymorphism.h(119) : error C2248 :
			//'Polymorphism::Base::mProtectedMember' : cannot access inaccessible member declared in class 'Polymorphism::Base'
			//c:\workarea\practice_and_test\cpp_std_test_and_practice\cpp11\polymorphism.h(119) : error C2248 :
			//'Polymorphism::Base::mProtectedMember' : cannot access inaccessible member declared in class 'Polymorphism::Base'

			//COUT_LINE(mPrivateMember);
			// ******NOTE****** derived class doesn't have access to private member
		}
	protected:
	private:
	};
}


#endif //POLYMORPHISM_H_