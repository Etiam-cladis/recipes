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
                  && !std::is_same<unsigned char, T>::value
                  && !std::is_same<wchar_t, T>::value>::type>
    fraction(T numerator, T denominator = 1)
    {
        if (static_cast<std::int64_t>(denominator) == 0)
        {
            throw std::overflow_error("Denominator cannot be zero");
        }

        m_numerator = numerator;
        m_denominator = denominator;
    }

    fraction(const fraction& rhs)
    {
        m_numerator = rhs.m_numerator;
        m_denominator = rhs.m_denominator;
    }
    fraction(fraction&& rhs) noexcept
    {
        m_numerator = std::exchange(rhs.m_numerator, 0);
        m_denominator = std::exchange(rhs.m_denominator, 1);
    }

    fraction& operator=(fraction rhs)
    {
        m_numerator = rhs.m_numerator;
        m_denominator = rhs.m_denominator;
        return *this;
    }
    ~fraction() = default;

    std::int64_t num() const { return m_numerator; };
    std::int64_t den() const { return m_denominator; };

    std::string to_string() const;
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
        return (lhs.num() * rhs.den() - rhs.num() * lhs.den()) < 0;
    }
    friend bool operator<=(const fraction& lhs, const fraction& rhs)
    {
        return (lhs.num() * rhs.den() - rhs.num() * lhs.den()) <= 0;
    }
    friend bool operator>(const fraction& lhs, const fraction& rhs)
    {
        return (lhs.num() * rhs.den() - rhs.num() * lhs.den()) > 0;
    }
    friend bool operator>=(const fraction& lhs, const fraction& rhs)
    {
        return (lhs.num() * rhs.den() - rhs.num() * lhs.den()) >= 0;
    }
    friend bool operator==(const fraction& lhs, const fraction& rhs)
    {
        std::int64_t gcd_lhs =
            fraction::gcd(lhs.m_numerator, lhs.m_denominator);
        std::int64_t gcd_rhs =
            fraction::gcd(rhs.m_numerator, rhs.m_denominator);
        return lhs.m_numerator / gcd_lhs == rhs.m_numerator / gcd_rhs
               && lhs.m_denominator / gcd_lhs == rhs.m_denominator / gcd_rhs;
    }
    friend bool operator!=(const fraction& lhs, const fraction& rhs)
    {
        return !(lhs == rhs);
    }

    friend std::ostream& operator<<(std::ostream& out, const fraction& rhs)
    {
        return out << rhs.to_string();
    }

    static std::int64_t gcd(std::int64_t a, std::int64_t b)
    {
        return b == 0 ? a : gcd(b, a % b);
    }

private:
    std::int64_t m_numerator;
    std::int64_t m_denominator;
};
}  // namespace solve

#endif  // FRACTION_H
