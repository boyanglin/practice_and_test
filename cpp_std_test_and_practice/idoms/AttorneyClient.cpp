#include "AttorneyClient.h"

namespace Idioms
{
	long substractFunc(long arg1, long arg2)
	{
		BaseClass aObject;
		return Attorney::callPrivateFunc(aObject, arg1, arg2);
	}

	long substractFunc_NotWorking(long arg1, long arg2)
	{
		////****this function doesn't work because substractFunc_NotWorking doesn't have access to the protected function of Attorney
		//BaseClass aObject;
		//return Attorney::callPrivateFunc(aObject, arg1, arg2); 
		return 0;
	}

}