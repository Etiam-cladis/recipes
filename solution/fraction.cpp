#include "fraction.h"

namespace solve
{

void fraction::zero_or_value(int new_n, int new_d)
{
    std::int64_t g = fraction::gcd(new_n, new_d);
    if (new_n == 0)
    {
        m_numerator = 0;
        m_denominator = 0;
    }
    else
    {
        m_numerator = new_n / g;
        m_denominator = new_d / g;
    }
}
fraction& fraction::operator+=(const fraction& rhs)
{
    std::int64_t new_n =
        m_numerator * rhs.m_denominator + rhs.m_numerator * m_denominator;
    std::int64_t new_d = m_denominator * rhs.m_denominator;

    zero_or_value(new_n, new_d);

    return *this;
}

fraction& fraction::operator-=(const fraction& rhs)
{
    std::int64_t new_n =
        m_numerator * rhs.m_denominator - rhs.m_numerator * m_denominator;
    std::int64_t new_d = m_denominator * rhs.m_denominator;

    zero_or_value(new_n, new_d);

    return *this;
}
fraction& fraction::operator*=(const fraction& rhs)
{
    std::int64_t new_n = m_numerator * rhs.m_numerator;
    std::int64_t new_d = m_denominator * rhs.m_denominator;

    zero_or_value(new_n, new_d);

    return *this;
}

fraction& fraction::operator/=(const fraction& rhs)
{
    if (*this == 0)
    {
        m_numerator = 0;
        m_denominator = 0;
    }
    else
    {
        std::int64_t g = fraction::gcd(m_numerator * rhs.m_denominator,
                                       m_denominator * rhs.m_numerator);
        if (g == 0) { throw std::overflow_error("Divide by zero exception"); }
        else
        {
            m_numerator = m_numerator * rhs.m_denominator / g;
            m_denominator = m_denominator * rhs.m_numerator / g;
        }
    }

    return *this;
}

}  // namespace solve