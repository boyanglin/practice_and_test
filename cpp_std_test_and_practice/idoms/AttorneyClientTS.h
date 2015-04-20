#ifndef ATTORNEY_CLIENT_TS_H_
#define ATTORNEY_CLIENT_TS_H_

#include <boost/test/unit_test.hpp>

namespace Idioms_TS
{

    class AttorneyClientTS
    {
      public:
		static void testAttorney();
        static  boost::unit_test_framework::test_suite* suite();
    };


} //namespace Idioms_TS


#endif