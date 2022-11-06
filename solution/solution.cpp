#include "solution.h"

#include <functional>
#include <unordered_map>

#include "fraction.h"

namespace solve
{
enum OP
{
    ADD = 0,
    MULTIPLY,
    SUBTRACT,
    DIVIDE
};

std::unordered_map<OP, char> op_to_char{
    {     OP::ADD, '+'},
    {OP::MULTIPLY, '*'},
    {OP::SUBTRACT, '-'},
    {  OP::DIVIDE, '/'}
};

void make_result(solve::solution& s, const solve::fraction& a, const solve::fraction& b, OP op)
{
    if (!s.get_result().empty())
    {
        s.set_result() = '(' + s.get_result() + op_to_char[op] + b.to_string() + ')';
    }
    else { s.set_result() = '(' + a.to_string() + op_to_char[op] + b.to_string() + ')'; }
}

std::vector<std::function<solve::fraction(solve::solution&, solve::fraction a, solve::fraction b)>> ops{
    [](solution& s, solve::fraction a, solve::fraction b) -> solve::fraction {
        make_result(s, a, b, OP::ADD);
        return a + b;
    },
    [](solution& s, solve::fraction a, solve::fraction b) -> solve::fraction {
        make_result(s, a, b, OP::MULTIPLY);
        return a * b;
    },
    [](solution& s, solve::fraction a, solve::fraction b) -> solve::fraction {
        make_result(s, a, b, OP::SUBTRACT);
        return a - b;
    },
    [](solution& s, solve::fraction a, solve::fraction b) -> solve::fraction {
        make_result(s, b, a, OP::SUBTRACT);
        return b - a;
    },
    [](solution& s, solve::fraction a, solve::fraction b) -> solve::fraction {
        make_result(s, a, b, OP::DIVIDE);
        return a / b;
    },
    [](solution& s, solve::fraction a, solve::fraction b) -> solve::fraction {
        make_result(s, b, a, OP::DIVIDE);
        return b / a;
    },
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
            std::string old = m_result;
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
                        return ret;
                    }
                    m_result = old;
                } catch (const std::overflow_error& e)
                {
                    m_result = old;
                }
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