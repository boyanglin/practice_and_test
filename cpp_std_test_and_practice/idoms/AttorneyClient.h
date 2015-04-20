#ifndef ATTORNEY_CLIENT_H_
#define ATTORNEY_CLIENT_H_

namespace Idioms
{
    class BaseClass
    {
	public:
		double getNumber()
		{
			return m_number;
		}
	private:
        long privateFunc(long arg1, long arg2)
        {
            return arg1 - arg2;
        }
        double m_number;

        friend class Attorney;
    };

    class DerivClass : public BaseClass
    {
      public:

      private:
    };

    class Attorney
    {
      protected:
        static long callPrivateFunc(BaseClass &object, long arg1, long arg2)
        {
            return object.privateFunc(arg1, arg2);
        }

		static void setNumber(BaseClass &object, double number)
		{
			object.m_number = number; 
		}

        friend long substractFunc(long, long);
    };

    class Modifier : public Attorney
    {
      public:
		  long CallPrivateFunc(long arg1, long arg2)
		  {
			  BaseClass aObject;
			  return Attorney::callPrivateFunc(aObject, arg1, arg2);
		  }

		  void setNumberInBaseClass(BaseClass &object, double number)
		  {
			  Attorney::setNumber(object, number);
		  }
    };

    long substractFunc(long arg1, long arg2);
    long substractFunc_NotWorking(long arg1, long arg2);
}

#endif  //ATTORNEY_CLIENT_H_