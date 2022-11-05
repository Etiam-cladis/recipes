#include "solution.h"

#include "fraction.h"

namespace solve
{

static constexpr int ADD = 0, MULTIPLY = 1, SUBTRACT = 2, DIVIDE = 3;

solution::solution(const std::vector<solve::fraction>& input, int target)
    : m_input(input), m_target(target)
{}

solution::solution(std::vector<solve::fraction>&& input, int target)
    : m_input(std::move(input)), m_target(target)
{}

bool solution::backtrace(std::vector<solve::fraction>& input)
{
    if (input.size() == 0) { return false; }
    if (input.size() == 1) { return input[0] == 24; }

    int size = input.size();
    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            if (i != j)
            {
                std::vector<solve::fraction> temp =
                    std::vector<solve::fraction>();
                for (int k = 0; k < size; ++k)
                {
                    if (k != i && k != j) { temp.emplace_back(input[k]); }
                }

                for (int op = 0; op < 4; ++op)
                {
                    if (op < 2 && i > j) { continue; }
                    if (op == ADD) { temp.emplace_back(input[i] + input[j]); }
                    else if (op == MULTIPLY)
                    {
                        temp.emplace_back(input[i] * input[j]);
                    }
                    else if (op == SUBTRACT)
                    {
                        temp.emplace_back(input[i] - input[j]);
                    }
                    else if (op == DIVIDE)
                    {
                        if (input[j] == 0) { continue; }
                        temp.emplace_back(input[i] / input[j]);
                    }
                    if (backtrace(temp)) { return true; }
                    temp.pop_back();
                }
            }
        }
    }
    return false;
}
// std::string solution::get_result() { return m_result; }

bool solution::judge()
{
    if (!valid_input()) { return false; }

    std::vector<solve::fraction> input(m_input);
    return backtrace(input);
}

bool solution::valid_input()
{
    if (m_input.size() != 4) { return false; }
    if (m_target != 24) { return false; }
    return true;
}

}  // namespace solve