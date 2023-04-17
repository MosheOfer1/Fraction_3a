#include "Fraction.hpp"
#include <stdexcept>
#include <cmath>

#define EPSILON 0.001
using namespace std;

int gcd(int a, int b)
{
    if (b == 0)
    {
        return a;
    }
    return gcd(b, a % b);
}

int least_common_multiple(int a, int b)
{
    return (a * b) / gcd(a, b);
}

namespace ariel
{
    // Constructors
    Fraction::Fraction() : m_numerator(0), m_denominator(1) {}
    // Copy constructor
    Fraction::Fraction(const Fraction &other)
        : m_numerator(other.m_numerator), m_denominator(other.m_denominator){}

    Fraction::Fraction(int numerator, int denominator)
    {
        if (denominator == 0)
        {
            throw invalid_argument("Denominator cannot be zero!");
        }
        m_numerator = numerator;
        m_denominator = denominator;
        this->reduce();
    }

    Fraction::Fraction(float value)
    {
        if (value < 0.001)
        {
            throw invalid_argument("Denominator cannot be zero!");
        }
        // Multiply the float by 1000 to get 3 decimal places
        int multiplier = 1000;
        int numerator = static_cast<int>(value * multiplier);
        int denominator = multiplier;

        m_numerator = numerator;
        m_denominator = denominator;
        this->reduce();
    }

    Fraction::~Fraction() {}

    // Private methods

    void Fraction::reduce()
    {
        int gcd_res = gcd(m_numerator, m_denominator);
        m_numerator /= gcd_res;
        m_denominator /= gcd_res;

        if (m_denominator < 0)
        {
            m_numerator = -m_numerator;
            m_denominator = -m_denominator;
        }
    }

    // Public methods
    Fraction Fraction::operator+(const Fraction &other) const
    {
        int new_numerator = m_numerator * other.m_denominator + other.m_numerator * m_denominator;
        int new_denominator = m_denominator * other.m_denominator;
        return Fraction(new_numerator, new_denominator);
    }

    Fraction Fraction::operator-(const Fraction &other) const
    {
        int new_numerator = m_numerator * other.m_denominator - other.m_numerator * m_denominator;
        int new_denominator = m_denominator * other.m_denominator;
        return Fraction(new_numerator, new_denominator);
    }

    Fraction Fraction::operator*(const Fraction &other) const
    {
        int new_numerator = m_numerator * other.m_numerator;
        int new_denominator = m_denominator * other.m_denominator;
        return Fraction(new_numerator, new_denominator);
    }

    Fraction Fraction::operator/(const Fraction &other) const
    {
        if (other.m_numerator == 0)
        {
            throw invalid_argument("Cannot divide by zero!");
        }

        int new_numerator = m_numerator * other.m_denominator;
        int new_denominator = m_denominator * other.m_numerator;
        return Fraction(new_numerator, new_denominator);
    }

    Fraction operator+(const Fraction &fraction, const float &float_val)
    {
        return fraction + Fraction(float_val);
    }

    Fraction operator-(const Fraction &fraction, const float &float_val)
    {
        return fraction - Fraction(float_val);
    }

    Fraction operator*(const Fraction &fraction, const float &float_val)
    {
        return fraction * Fraction(float_val);
    }

    Fraction operator/(const Fraction &fraction, const float &float_val)
    {
        return fraction / Fraction(float_val);
    }

    Fraction operator+(const float &float_val, const Fraction &fraction)
    {
        return Fraction(float_val) + fraction;
    }

    Fraction operator-(const float &float_val, const Fraction &fraction)
    {
        return Fraction(float_val) - fraction;
    }

    Fraction operator*(const float &float_val, const Fraction &fraction)
    {
        return Fraction(float_val) * fraction;
    }

    Fraction operator/(const float &float_val, const Fraction &fraction)
    {
        return Fraction(float_val) / fraction;
    }

    Fraction &Fraction::operator++()
    {
        m_numerator += m_denominator;
        return *this;
    }

    Fraction &Fraction::operator--()
    {
        m_numerator -= m_denominator;
        return *this;
    }
    // postfix increment operator
    Fraction Fraction::operator++(int dummy_flag_for_postfix_increment)
    {
        Fraction temp(*this);
        ++(*this);
        return temp;
    }

    // postfix decrement operator
    Fraction Fraction::operator--(int dummy_flag_for_postfix_increment)
    {
        Fraction temp(*this);
        --(*this);
        return temp;
    }

    // comparison operators
    bool operator==(const Fraction &fraction1, const Fraction &fraction2)
    {
        return (fraction1.m_numerator == fraction2.m_numerator && fraction1.m_denominator == fraction2.m_denominator);
    }

    bool operator!=(const Fraction &fraction1, const Fraction &fraction2)
    {
        return !(fraction1 == fraction2);
    }

    bool operator<(const Fraction &fraction1, const Fraction &fraction2)
    {
        int lcm = least_common_multiple(fraction1.m_denominator, fraction2.m_denominator);
        int fraction1_numerator = fraction1.m_numerator * (lcm / fraction1.m_denominator);
        int fraction2_numerator = fraction2.m_numerator * (lcm / fraction2.m_denominator);
        return (fraction1_numerator < fraction2_numerator);
    }

    bool operator>(const Fraction &fraction1, const Fraction &fraction2)
    {
        return (fraction2 < fraction1);
    }

    bool operator<=(const Fraction &fraction1, const Fraction &fraction2)
    {
        return !(fraction1 > fraction2);
    }

    bool operator>=(const Fraction &fraction1, const Fraction &fraction2)
    {
        return !(fraction1 < fraction2);
    }

    bool operator==(const float &fraction1, const Fraction &fraction2)
    {
        return (fabs(fraction1 - ((float)fraction2.m_numerator / (float)fraction2.m_denominator)) < EPSILON);
    }

    bool operator!=(const float &fraction1, const Fraction &fraction2)
    {
        return !(fraction1 == fraction2);
    }

    bool operator<(const Fraction &fraction, const float &float_val)
    {
        return (fraction < Fraction(float_val));
    }

    bool operator<(const float &float_val, const Fraction &fraction)
    {
        return (Fraction(float_val) < fraction);
    }

    bool operator<=(const Fraction &fraction, const float &float_val)
    {
        return !(fraction > float_val);
    }

    bool operator<=(const float &float_val, const Fraction &fraction)
    {
        return !(Fraction(float_val) > fraction);
    }

    bool operator==(const Fraction &fraction1, const float &fraction2)
    {
        return (fabs(((float)fraction1.m_numerator / (float)fraction1.m_denominator) - fraction2) < EPSILON);
    }

    bool operator!=(const Fraction &fraction1, const float &fraction2)
    {
        return !(fraction1 == fraction2);
    }

    bool operator>(const Fraction &fraction, const float &float_val)
    {
        return (fraction > Fraction(float_val));
    }

    bool operator>(const float &float_val, const Fraction &fraction)
    {
        return (Fraction(float_val) > fraction);
    }

    bool operator>=(const Fraction &fraction, const float &float_val)
    {
        return !(fraction < float_val);
    }

    bool operator>=(const float &float_val, const Fraction &fraction)
    {
        return !(float_val < fraction);
    }

    ostream &operator<<(ostream &output, const Fraction &float_val)
    {
        output << float_val.m_numerator << "/" << float_val.m_denominator;
        return output;
    }

    istream &operator>>(istream &input, Fraction &float_val)
    {
        int numerator, denominator;
        char slash;

        // Read numerator
        input >> numerator;

        // Read slash
        input >> slash;

        if (slash != '/')
        {
            input.setstate(ios::failbit);
            return input;
        }

        // Read denominator
        input >> denominator;

        if (denominator == 0)
        {
            input.setstate(ios::failbit);
            return input;
        }

        // Set the fraction object
        float_val.m_numerator = numerator;
        float_val.m_denominator = denominator;

        return input;
    }

}
