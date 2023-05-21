/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Concepts des langages de programmation - TP n°2
 *
 * TestNumber.cpp
 * c++ -std=c++20 -o TestNumber Number.cpp TestNumber.cpp -lgtest -lpthread
 */

#include <exception>
#include <sstream>
#include <utility>

#include <gtest/gtest.h>

#include "Number.hpp"

 
TEST( TestNumber, TestNumber0 )
{
    Number n{ 0 };
    std::ostringstream os;
    os << n;
    EXPECT_EQ( os.str(), "0" );
}
 
TEST( TestNumber, TestNumber12345678 )
{
    Number n{ 12345678 };
    std::ostringstream os;
    os << n;
    EXPECT_EQ( os.str(), "12345678" );
}
 
TEST( TestNumber, TestNumberBig )
{
    Number n{ 12345123451234512345UL };
    std::ostringstream os;
    os << n;
    EXPECT_EQ( os.str(), "12345123451234512345" );
}

TEST( TestNumber, TestCopy )
{
    Number *n_1 = new Number(12345);
    Number *n_2 = new Number(*n_1);
    delete n_1;

    std::ostringstream os;
    os << *n_2;
    EXPECT_EQ( os.str(), "12345" );
}

TEST( TestNumber, TestAssignment )
{
    Number *n_1 = new Number(12345);
    Number *n_2 = new Number(123456);
    *n_2 = *n_1;
    delete n_1;


    std::ostringstream os;
    os << *n_2;
    EXPECT_EQ( os.str(), "12345" );
}

TEST( TestNumber, TestAdd )
{
    Number n_1(1234);
    int n_2 = 67859;
    n_1.add(n_2);

    std::ostringstream os;
    os << n_1;
    EXPECT_EQ( os.str(), "69093" );
}

TEST( TestNumber, TestMultiply )
{
    Number n_1(3722);
    int n_2 = 1246;
    n_1.multiply(n_2);

    std::ostringstream os;
    os << n_1;
    EXPECT_EQ( os.str(), "4637612" );
}

TEST( TestNumber, TestFactorial123 )
{
    std::ostringstream os;
    os << factorial( 123 );
    EXPECT_EQ( os.str(), "121463043670253296757662432418812958554542170884833823153289181618292"
                         "358923621676688311569606126402021707358352212940477825910915704116514"
                         "72186029519906261646730733907419814952960000000000000000000000000000" );
}

TEST( TestNumber, TestString )
{
    Number n{ "1234" };
    std::ostringstream os;
    os << n;
    EXPECT_EQ( os.str(), "1234" );
}

TEST( TestNumber, TestRead )
{
    Number n{ "1" };
    std::istringstream in{"1234"};
    std::ostringstream os;

    in >> n;
    os << n;
    EXPECT_EQ( os.str(), "1234" );
}

TEST( TestNumber, TestOperators )
{
    std::ostringstream os;
    Number n_1{ 200 };
    Number n_2{ 300 };

    unsigned int k = 10;
    
    Number sum = n_1 + k;
    Number mult = n_1*k;

    n_1 += k;
    n_2 *= k;

    os << sum << ", " << mult << ", " << n_1 << ", " << n_2;
    EXPECT_EQ( os.str(), "210, 2000, 210, 3000" );
}

int main( int argc, char * argv[] )
{
    ::testing::InitGoogleTest( &argc, argv );
    return RUN_ALL_TESTS();
}
