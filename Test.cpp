#include "doctest.h"
#include "sources/Fraction.hpp"
#include <stdexcept>
#include <iostream>
#include <sstream>

using namespace ariel;
using namespace std;

TEST_CASE("plus operation 1/2 + 1/4 = 3/4")
{
    // 1/2 + 1/4 should return the reduced form 0.75 or 3/4
    Fraction a(8, 16), b(3, 12);
    Fraction c = a + b;
    Fraction d(3, 4);

    CHECK(c == 0.75);
    CHECK(c == d);

    // fraction plus float
    c = a + 0.25;
    CHECK(c == 0.75);

    // float plus fraction
    c = 0.25 + a;
    CHECK(c == 0.75);
}

TEST_CASE("minus operation 1/2 - 1/4 = 1/4")
{
    // 1/2 + 1/4 should return the reduced form 0.25 or 1/4
    Fraction a(8, 16), b(3, 12);
    Fraction c = a - b;
    Fraction d(1, 4);

    CHECK(c == 0.25);
    CHECK(c == d);

    // fraction minus float
    c = a - 0.25;
    CHECK(c == 0.25);

    // float minus fraction
    c = 0.5 - b;
    CHECK(c == d);
}

TEST_CASE("Divide by zero throws an exception")
{
    Fraction f(3, 9);
    CHECK_THROWS(f / 0);
}

TEST_CASE("Constructors cannot gat zero as Denominator")
{
    CHECK_THROWS(Fraction(3, 0));
    CHECK_THROWS(Fraction(0.0009));
}

TEST_CASE("Fraction constructor with negative denominator sets numerator and denominator correctly")
{
    Fraction f1(1, -2);
    ostringstream stream;
    stream << f1;
    CHECK(stream.str() == "-1/2");

    Fraction f2(-1, -2);
    ostringstream stream2;
    stream2 << f2;
    CHECK(stream2.str() == "1/2");
}

TEST_CASE("multiplication and division operations")
{
    // 1/2 * 1/4 should return the reduced form 0.125 or 1/8
    Fraction a(8, 16), b(3, 12);
    Fraction c = a * b;
    Fraction d(1, 8);

    CHECK(c == 0.125);
    CHECK(c == d);

    // fraction times float
    c = a * 1.5;
    CHECK(c == 0.75);

    // float times fraction
    c = 2.0 * b;
    CHECK(c == 0.5);

    // 1/2 / 1/4 should return the reduced form 2 or 2/1
    a = Fraction(1, 2);
    b = Fraction(1, 4);
    c = a / b;
    d = Fraction(2, 1);

    CHECK(c == 2);
    CHECK(c == d);

    // fraction divided by float
    c = a / 0.25;
    CHECK(c == 2);

    // float divided by fraction
    c = 1.5 / b;
    CHECK(c == 6);
}

TEST_CASE("comparison operations between float and Fraction and the other way")
{
    // 1/2 < 0.75 Fraction from the right
    Fraction a(1, 2);
    float b = 0.75;
    bool result = a < b;
    CHECK(result == true);
    // 0.75 > 1/2 Fraction from the Left
    result = b > a;
    CHECK(result == true);

    // 2.5 > 1/3 Fraction from the right
    Fraction c(1, 3);
    float d = 2.5;
    result = d > c;
    CHECK(result == true);
    // 1/3 < 2.5 Fraction from the Left
    result = c < d;
    CHECK(result == true);

    // 1/4 <= 0.5 Fraction from the right
    Fraction e(1, 4);
    float f = 0.5;
    result = e <= f;
    CHECK(result == true);
    // 0.5 >= 1/4 Fraction from the Left
    result = f >= e;
    CHECK(result == true);

    // 0.2 >= 1/6 Fraction from the right
    Fraction g(1, 6);
    float h = 0.2;
    result = h >= g;
    CHECK(result == true);
    // 2/9 <= 0.2 Fraction from the Left
    result = g <= h;
    CHECK(result == true);

    // This case checks that on a float var you need to use up to 3 digits beyond the decimal point for accuracy
    // 1/4 == 0.333 Fraction from the right
    Fraction i(1, 3);
    float j = 0.333;
    result = i == j;
    CHECK(result == true);
    // 0.333 == 1/3 Fraction from the Left
    result = j == i;
    CHECK(result == true);

    // 0.75 != 3/4 Fraction from the right
    Fraction k(3, 4);
    float l = 0.75;
    result = l != k;
    CHECK(result == false);
    // 3/4 != 0.75 Fraction from the Left
    result = k != l;
    CHECK(result == false);
}

TEST_CASE("comparison operations between Fraction objects")
{
    // 1/2 == 2/4
    Fraction a(1, 2);
    Fraction b(2, 4);
    bool result = a == b;
    CHECK(result == true);

    // 1/3 < 2/5
    Fraction c(1, 3);
    Fraction d(2, 5);
    result = c < d;
    CHECK(result == true);

    // 3/4 > 1/3
    Fraction e(3, 4);
    Fraction f(1, 3);
    result = e > f;
    CHECK(result == true);

    // 2/9 <= 3/9
    Fraction g(2, 9);
    Fraction h(3, 9);
    result = g <= h;
    CHECK(result == true);

    // 2/7 >= 1/2
    Fraction i(2, 7);
    Fraction j(1, 2);
    result = i >= j;
    CHECK(result == false);

    // 1/5 != 2/5
    Fraction k(1, 5);
    Fraction l(2, 5);
    result = k != l;
    CHECK(result == true);
}

TEST_CASE("increment ++ and decrement -- operations")
{
    // pre-increment
    Fraction a(3, 4);
    Fraction b = ++a;
    Fraction c(7, 4);
    CHECK(b == c);

    // post-increment
    Fraction d(1, 2);
    Fraction e = d++;
    Fraction f(3, 2);
    CHECK(e == 0.5);
    CHECK(d == f);

    // pre-decrement
    Fraction g(5, 6);
    Fraction h = --g;
    Fraction i(-1, 6);
    CHECK(h == i);

    // post-decrement
    Fraction j(2, 3);
    Fraction k = j--;
    Fraction l(-1, 3);
    CHECK(k == 0.666);
    CHECK(j == l);
}

TEST_CASE("<< operator prints fraction in correct format")
{
    Fraction a(4, 6);
    std::stringstream ss;
    ss << a;
    CHECK(ss.str() == "2/3");
}

TEST_CASE(">> operator reads fraction from input stream")
{
    std::stringstream ss("4/5");
    Fraction a;
    ss >> a;
    Fraction b(4, 5);
    CHECK(a == b);
}
