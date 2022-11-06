#include "solution.h"

#include <functional>
#include <unordered_map>

#include "fraction.h"

namespace solve
{
std::vector<std::function<solve::fraction(solve::solution&, solve::fraction a, solve::fraction b)>> ops{
    [](solution& s, solve::fraction a, solve::fraction b) -> solve::fraction { return a + b; },
    [](solution& s, solve::fraction a, solve::fraction b) -> solve::fraction { return a * b; },
    [](solution& s, solve::fraction a, solve::fraction b) -> solve::fraction { return a - b; },
    [](solution& s, solve::fraction a, solve::fraction b) -> solve::fraction { return b - a; },
    [](solution& s, solve::fraction a, solve::fraction b) -> solve::fraction { return a / b; },
    [](solution& s, solve::fraction a, solve::fraction b) -> solve::fraction { return b / a; },
};

solution::solution(const std::vector<solve::fraction>& input, int target) : m_input(input), m_target(target)
{}

solution::solution(std::vector<solve::fraction>&& input, int target)
    : m_input(std::move(input)), m_target(target)
{}

solve::fraction solution::backtrace(int left, int right, int val)
{
    for (int i = left; i < right - 1; ++i)
    {
        for (int j = left + 1; j < right; ++j)
        {
            std::swap(m_input[i], m_input[left]);
            std::swap(m_input[j], m_input[left + 1]);

            for (auto op : ops)
            {
                try
                {
                    auto ret = op(*this, m_input[left], m_input[left + 1]);
                    if (right - left > 2)
                    {
                        auto ori = m_input[left + 1];
                        m_input[left + 1] = ret;
                        ret = backtrace(left + 1, right, val);
                        m_input[left + 1] = ori;
                    }
                    if (ret == val)
                    {
                        std::swap(m_input[j], m_input[left + 1]);
                        std::swap(m_input[i], m_input[left]);
                        m_result = ret.to_string();
                        return ret;
                    }
                } catch (const std::overflow_error& e)
                {}
            }
            std::swap(m_input[j], m_input[left + 1]);
            std::swap(m_input[i], m_input[left]);
        }
    }

    return 0;
}

bool solution::judge()
{
    if (!valid_input()) { return false; }

    return backtrace(0, m_input.size(), m_target) == m_target;
}

bool solution::valid_input()
{
    if (m_input.size() != 4) { return false; }
    if (m_target != 24) { return false; }
    return true;
}

}  // namespace solve