#include "fraction.h"

namespace solve
{

void fraction::set_value(std::int64_t new_n, std::int64_t new_d, std::int64_t g, std::string&& s)
{
    m_numerator = new_n / g;
    m_denominator = new_d / g;
    if (!s.empty()) { m_str = std::move(s); }
    else
    {
        m_str = std::to_string(m_numerator);
        if (m_denominator != 1)
        {
            m_str += '/';
            m_str += std::to_string(m_denominator);
        }
    }
}
fraction& fraction::operator+=(const fraction& rhs)
{
    std::int64_t new_n = m_numerator * rhs.m_denominator + rhs.m_numerator * m_denominator;
    std::int64_t new_d = m_denominator * rhs.m_denominator;
    std::int64_t g = fraction::gcd(new_n, new_d);
    set_value(new_n, new_d, g, '(' + m_str + '+' + rhs.m_str + ')');

    return *this;
}

fraction& fraction::operator-=(const fraction& rhs)
{
    std::int64_t new_n = m_numerator * rhs.m_denominator - rhs.m_numerator * m_denominator;
    std::int64_t new_d = m_denominator * rhs.m_denominator;
    std::int64_t g = fraction::gcd(new_n, new_d);
    set_value(new_n, new_d, g, '(' + m_str + '-' + rhs.m_str + ')');

    return *this;
}
fraction& fraction::operator*=(const fraction& rhs)
{
    std::int64_t new_n = m_numerator * rhs.m_numerator;
    std::int64_t new_d = m_denominator * rhs.m_denominator;

    std::int64_t g = fraction::gcd(new_n, new_d);
    set_value(new_n, new_d, g, '(' + m_str + '*' + rhs.m_str + ')');

    return *this;
}

fraction& fraction::operator/=(const fraction& rhs)
{
    std::int64_t new_n = m_numerator * rhs.m_denominator;
    std::int64_t new_d = m_denominator * rhs.m_numerator;
    if (new_d == 0) { throw std::overflow_error("Divide by zero exception"); }

    std::int64_t g = fraction::gcd(new_n, new_d);
    set_value(new_n, new_d, g, '(' + m_str + '/' + rhs.m_str + ')');

    return *this;
}

}  // namespace solve