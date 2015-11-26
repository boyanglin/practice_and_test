#ifndef FUNCTION_NUMBER_H_
#define	FUNCTION_NUMBER_H_

#define GET_FUNC_PROFILE_NAME(functionName) KFUNC_PROFILE_##functionName
#define DEF_FUNCTION_NUMBER_CONST(functionName, functionNum) const unsigned short GET_FUNC_PROFILE_NAME(functionName) = functionNum

#define MAX_KFUNC_NUMBER 500

DEF_FUNCTION_NUMBER_CONST(VectorWrapperTestFunction, 10);
DEF_FUNCTION_NUMBER_CONST(TestAssignmentOperator, 11);
DEF_FUNCTION_NUMBER_CONST(TestVectorReference, 12);

const unsigned short FID_TestVectorReference = 0;
const unsigned short FID_TestVectorReference2 = 1;



#endif  //FUNCTION_NUMBER_H_