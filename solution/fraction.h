#ifndef FRACTION_H
#define FRACTION_H

#include <cstdint>
#include <iostream>
#include <type_traits>
#include <utility>
namespace solve
{
class fraction
{
public:
    fraction() = default;

    template <typename T,
              typename = typename std::enable_if<
                  std::is_integral<T>::value && !std::is_same<bool, T>::value
                  && !std::is_same<char, T>::value
                  && !std::is_same<signed char, T>::value
                  && !std::is_same<unsigned char, T>::value>::type>
    fraction(T numerator, T denominator = 1)
    {
        if (static_cast<std::int64_t>(denominator) == 0)
        {
            throw std::overflow_error("Divide by zero exception");
        }
        std::int64_t g = fraction::gcd(static_cast<std::int64_t>(numerator),
                                       static_cast<std::int64_t>(denominator));
        if (g == 0 || numerator == 0)
        {
            m_numerator = 0;
            m_denominator = 0;
        }
        else
        {
            m_numerator = numerator / g;
            m_denominator = denominator / g;
        }
    }

    fraction(const fraction& rhs)
    {
        m_numerator = rhs.m_numerator;
        m_denominator = rhs.m_denominator;
    }
    fraction(fraction&& rhs) noexcept
    {
        m_numerator = std::exchange(rhs.m_numerator, 0);
        m_denominator = std::exchange(rhs.m_denominator, 0);
    }

    fraction& operator=(fraction rhs)
    {
        std::swap(m_numerator, rhs.m_numerator);
        std::swap(m_denominator, m_denominator);
        return *this;
    }
    ~fraction() = default;

    std::int64_t num() const { return m_numerator; };
    std::int64_t den() const { return m_denominator; };
    fraction& operator++()
    {
        m_numerator += m_denominator;
        return *this;
    }
    fraction operator++(int)
    {
        fraction old = *this;
        ++*this;
        return old;
    }
    fraction& operator--()
    {
        m_numerator -= m_denominator;
        return *this;
    }
    fraction operator--(int)
    {
        fraction old = *this;
        --*this;
        return old;
    }

    fraction& operator+=(const fraction& rhs);
    friend fraction operator+(fraction lhs, const fraction& rhs)
    {
        return lhs += rhs;
    }

    fraction& operator-=(const fraction& rhs);
    friend fraction operator-(fraction lhs, const fraction& rhs)
    {
        return lhs -= rhs;
    }

    fraction& operator*=(const fraction& rhs);

    friend fraction operator*(fraction lhs, const fraction& rhs)
    {
        return lhs *= rhs;
    }

    fraction& operator/=(const fraction& rhs);
    friend fraction operator/(fraction lhs, const fraction& rhs)
    {
        return lhs /= rhs;
    }

    friend bool operator<(const fraction& lhs, const fraction& rhs)
    {
        return (lhs.num() * rhs.den() - rhs.num() - rhs.den()) < 0;
    }
    friend bool operator<=(const fraction& lhs, const fraction& rhs)
    {
        return (lhs.num() * rhs.den() - rhs.num() - rhs.den()) <= 0;
    }
    friend bool operator>(const fraction& lhs, const fraction& rhs)
    {
        return (lhs.num() * rhs.den() - rhs.num() - rhs.den()) > 0;
    }
    friend bool operator>=(const fraction& lhs, const fraction& rhs)
    {
        return (lhs.num() * rhs.den() - rhs.num() - rhs.den()) >= 0;
    }
    friend bool operator==(const fraction& lhs, const fraction& rhs)
    {
        return lhs.num() == rhs.num() && lhs.den() == rhs.den();
    }
    friend bool operator!=(const fraction& lhs, const fraction& rhs)
    {
        return !(lhs == rhs);
    }

    friend std::ostream& operator<<(std::ostream& out, const fraction& rhs)
    {
        return out << rhs.num() << '/' << rhs.den();
    }

    static std::int64_t gcd(std::int64_t a, std::int64_t b)
    {
        return b == 0 ? a : gcd(b, a % b);
    }

private:
    void zero_or_value(int new_n, int new_d);
    std::int64_t m_numerator;
    std::int64_t m_denominator;
};
}  // namespace solve

#endif  // FRACTION_H
