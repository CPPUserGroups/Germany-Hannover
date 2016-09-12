#include "incl.hpp"

#define BOOST_TEST_MODULE
#include <boost/test/included/unit_test.hpp>

const double test_tolerance = 0.0001;

BOOST_AUTO_TEST_CASE( empty_expression )
{
    BOOST_CHECK_THROW(
        calc_express( "" ),
        std::runtime_error );
}

BOOST_AUTO_TEST_CASE( empty_expression_with_whitespaces )
{
    BOOST_CHECK_THROW(
        calc_express( " " ),
        std::runtime_error );

    BOOST_CHECK_THROW(
        calc_express( "\t" ),
        std::runtime_error );
}

BOOST_AUTO_TEST_CASE( simple_integer )
{
    BOOST_CHECK_CLOSE(
        calc_express( "0" ),
        0.0,
        test_tolerance );

    BOOST_CHECK_CLOSE(
        calc_express( "31" ),
        31.0,
        test_tolerance );

    BOOST_CHECK_CLOSE(
        calc_express( "123" ),
        123.0,
        test_tolerance );
}

BOOST_AUTO_TEST_CASE( invalid_characters )
{
    BOOST_CHECK_THROW(
        calc_express( "x" ),
        std::runtime_error);

    BOOST_CHECK_THROW(
        calc_express( "d" ),
        std::runtime_error);
}

BOOST_AUTO_TEST_CASE( garbage_after_number )
{
    BOOST_CHECK_THROW(
        calc_express( "123abc" ),
        std::runtime_error);
}

BOOST_AUTO_TEST_CASE( unary_simple_integer )
{
    BOOST_CHECK_CLOSE(
        calc_express( "+1" ),
        1.0,
        test_tolerance );

    BOOST_CHECK_CLOSE(
        calc_express( "-1" ),
        -1.0,
        test_tolerance );
}

BOOST_AUTO_TEST_CASE( simple_binary_op )
{
    BOOST_CHECK_CLOSE(
        calc_express( "2+3" ),
        5.0,
        test_tolerance );
    BOOST_CHECK_CLOSE(
        calc_express( "2-3" ),
        -1.0,
        test_tolerance );
    BOOST_CHECK_CLOSE(
        calc_express( "2*3" ),
        6.0,
        test_tolerance );
    BOOST_CHECK_CLOSE(
        calc_express( "2/3" ),
        2.0/3.0,
        test_tolerance );
}

BOOST_AUTO_TEST_CASE( operator_precedence )
{
    BOOST_CHECK_CLOSE(
        calc_express( "2+3*4" ),
        14.0,
        test_tolerance );
    BOOST_CHECK_CLOSE(
        calc_express( "2*3+4" ),
        10.0,
        test_tolerance );
}
/*
BOOST_FIXTURE_TEST_CASE( test2, std::string )
{

}
*/