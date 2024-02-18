#include <boost/test/unit_test.hpp>

#include "../src/vm/CSTyp.hpp"
#include <boost/multiprecision/cpp_int.hpp>

#ifdef STAND_ALONE
#   define BOOST_TEST_MODULE DemoTests
#endif

using CSTypes::CSInteger;
using CSTypes::CSString;
using CSTypes::CSDouble;
using boost::multiprecision::cpp_int;

BOOST_AUTO_TEST_SUITE(cstypes)

    BOOST_AUTO_TEST_CASE(cs_int_add)
    {
        auto bi_1 = cpp_int("556151316116651651161561615611");
        auto bi_2 = cpp_int("1");

        auto a = CSInteger(bi_1);
        auto b = CSInteger(bi_2);

        auto c = a + b;
        BOOST_CHECK_EQUAL(c.toString(), "556151316116651651161561615612");

    }

    BOOST_AUTO_TEST_CASE(cs_int_sub)
    {
        auto bi_1 = cpp_int("556151316116651651161561615611");
        auto bi_2 = cpp_int("1");

        auto a = CSInteger(bi_1);
        auto b = CSInteger(bi_2);

        auto c = a - b;
        BOOST_CHECK_EQUAL(c.toString(), "556151316116651651161561615610");

    }

    BOOST_AUTO_TEST_CASE(cs_int_neg)
    {
        auto bi_1 = cpp_int("556151316116651651161561615611");
        auto bi_2 = cpp_int("-556151316116651651161561615612");

        auto a = CSInteger(bi_1);
        auto b = CSInteger(bi_2);

        auto c = a + b;
        BOOST_CHECK_EQUAL(c.toString(), "-1");

    }

    BOOST_AUTO_TEST_CASE(cs_int_eq)
    {
        auto bi_1 = cpp_int("556151316116651651161561615611");
        auto bi_2 = cpp_int("556151316116651651161561615611");

        auto a = CSInteger(bi_1);
        auto b = CSInteger(bi_2);

        BOOST_ASSERT(a == b);
    }
    BOOST_AUTO_TEST_CASE(cs_string_concat)
    {

        auto a = CSString("Hallo ");
        auto b = CSString("Welt!");
        BOOST_CHECK_EQUAL((a+b).getValue(),"Hallo Welt!");

    }


BOOST_AUTO_TEST_SUITE_END()