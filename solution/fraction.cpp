#include "fraction.h"

namespace solve
{

std::string fraction::to_string() const
{
    std::int64_t g = fraction::gcd(m_numerator, m_denominator);
    std::string ret{};
    ret += std::to_string(m_numerator / g);
    if (m_denominator != 1 && m_numerator != 0)
    {
        ret += '/';
        ret += std::to_string(m_denominator / g);
    }
    return ret;
}

fraction& fraction::operator+=(const fraction& rhs)
{
    m_numerator =
        m_numerator * rhs.m_denominator + rhs.m_numerator * m_denominator;

    m_denominator = m_denominator * rhs.m_denominator;

    return *this;
}

fraction& fraction::operator-=(const fraction& rhs)
{
    m_numerator =
        m_numerator * rhs.m_denominator - rhs.m_numerator * m_denominator;
    m_denominator = m_denominator * rhs.m_denominator;

    return *this;
}
fraction& fraction::operator*=(const fraction& rhs)
{
    m_numerator = m_numerator * rhs.m_numerator;
    m_denominator = m_denominator * rhs.m_denominator;

    return *this;
}

fraction& fraction::operator/=(const fraction& rhs)
{
    std::int64_t new_n = m_numerator * rhs.m_denominator;
    std::int64_t new_d = m_denominator * rhs.m_numerator;
    if (new_d == 0) { throw std::overflow_error("Divide by zero exception"); }

    m_numerator = new_n;
    m_denominator = new_d;

    return *this;
}

}  // namespace solve